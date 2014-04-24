#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <omp.h>
#include "timers.h"
#include "exprtk.hpp"

using namespace std;

string FUN = "";
string FILEPATH = "";
int N = 0;
int X1 = 0;
int X2 = 0;
int P = 8;

template<typename T>
double f(T x)
{
    exprtk::symbol_table<T> symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    exprtk::expression<T> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<T> parser;
    parser.compile(FUN, expression);
    return expression.value();
}
void simpsonRule()
{
    ofstream outfile("pomiary/simpson.dat", ios::out | ios::app);
    double a = X1;
    double b = X2;
    double result = 0;
    double t = 0;
    double x = 0;
    double avgTime = 0;
    double h = (b - a) / N;
    pTimer zegar = newTimer();

    startTimer(zegar);
    for (int j = 0; j < 5; j++)
    {
        result = 0; t = 0;
        for (int i = 1; i <= N; i++)
        {
            x = a + i * h;
            t += f<double>(x - h / 2);
            if (i < N)
                result += f<double>(x);
        }
        result = h / 6 * (f<double>(a) + f<double>(b) + 2 * result + 4 * t);
        stopTimer(zegar);
        avgTime += getTime(zegar);
    }

    outfile << N << "\t" << result << "\t" << avgTime / 5 << "\n";
    outfile.close();
    freeTimer(zegar);
}
void simpsonPar()
{
    ofstream outfile("pomiary/simpsonPar.dat", ios::out | ios::app);
    double a = X1;
    double b = X2;
    double sumA = 0;
    double sumB = 0;
    double result = 0;
    double timer = 0;
    double h = (b - a) / N;
    int i;
    pTimer zegar = newTimer();

    startTimer(zegar);
    #pragma omp parallel for private(i) reduction(+:sumA)
    for (i = 1; i < N; i++)
        sumA += f(a + h * i);

    #pragma omp parallel for private(i) reduction(+:sumB)
    for (i = 1; i <= N; i++)
        sumB += f((a + h * i + a + h * (i - 1)) / 2);

    result = ((f(a) + f(b)) / 2 + sumA + 2 * sumB) * h / 3;
    stopTimer(zegar);
    timer = getTime(zegar);
    outfile << N << "\t" << P << "\t" << result << "\t" << timer << "\n";
    outfile.close();
    freeTimer(zegar);
}
void rectangleRule()
{
    ofstream outfile("pomiary/rectangle.dat", ios::out | ios::app);
    double a = X1;
    double b = X2;
    double h = (b - a) / N;
    double result = 0;
    double avgTime = 0;
    pTimer zegar = newTimer();

    for (int j = 0; j < 5; j++)
    {
        result = 0;
        startTimer(zegar);
        for (int i = 1; i <= N; i++)
            result += f<double>(a + i * h) * h;
        stopTimer(zegar);
        avgTime += getTime(zegar);
    }

    outfile << N << "\t" << result << "\t" << avgTime / 5 << "\n";
    outfile.close();
    freeTimer(zegar);
}
void trapezoidalRule()
{
    ofstream outfile("pomiary/trapez.dat", ios::out | ios::app);
    double a = X1;
    double b = X2;
    double h = (b - a) / N;
    double result = 0;
    double avgTime = 0;
    pTimer zegar = newTimer();

    for (int j = 0; j < 5; j++)
    {
        result = 0;
        startTimer(zegar);
        for (int i = 1; i < N; i++)
            result += f<double>(a + i * h);
        result += f<double>(a) / 2;
        result += f<double>(b) / 2;
        result *= h;
        stopTimer(zegar);
        avgTime += getTime(zegar);
    }

    outfile << N << "\t" << result << "\t " << avgTime / 5 << "\n";
    outfile.close();
    freeTimer(zegar);
}
void trapezPar()
{
    ofstream outfile("pomiary/trapezPar.dat", ios::out | ios::app);
    double integral = 0, sum = 0;
    double a = X1;
    double b = X2;
    double h = (b - a) / N;
    double x = 0;
    int i;

    pTimer zegar = newTimer();
    startTimer(zegar);
    #pragma omp parallel for private(x, i) reduction(+:sum)
    for (i = 1; i <= N - 1; i++)
    {
        x = a + i * h;
        sum = sum + f<double>(x);
    }
    integral = (sum + (f<double>(a) + f<double>(b)) / 2) * h;

    stopTimer(zegar);
    double time = getTime(zegar);
    outfile << N << "\t" << P << "\t" << integral << "\t" << time << "\n";
    outfile.close();
    freeTimer(zegar);
}
void rectanglePar()
{
    ofstream outfile("pomiary/rectanglePar.dat", ios::out | ios::app);
    double integral = 0, sum = 0;
    double a = X1;
    double b = X2;
    double h = (b - a) / N;
    double x = 0;
    int i;

    pTimer zegar = newTimer();
    startTimer(zegar);

    #pragma omp parallel for private(x, i) reduction(+:sum)
    for (i = 1; i < N; i++)
    {
        x = a + i * h;
        sum += f<double>(x) * h;
    }
    integral += (f<double>(a) + f<double>(b)) / 2 * h + sum;

    stopTimer(zegar);
    double time = getTime(zegar);
    outfile << N << "\t" << P << "\t" << integral << "\t" << time << "\n";
    outfile.close();
    freeTimer(zegar);
}
void readFile()
{
    ifstream infile(FILEPATH.c_str());
    string n, fun, x1, x2, p;
    getline(infile, x1);
    getline(infile, x2);
    getline(infile, n);
    getline(infile, p);
    getline(infile, fun);
    X1 = atoi(x1.c_str());
    X2 = atoi(x2.c_str());
    N = atoi(n.c_str());
    P = atoi(p.c_str());
    FUN = fun;
}
int main(int argc, char **argv)
{
    int i = 0;
    while (i < argc)
    {
        if (!strcmp(argv[i], "-fun")) FUN = argv[++i];
        if (!strcmp(argv[i], "-f")) FILEPATH = argv[++i];
        if (!strcmp(argv[i], "-n")) N = atoi(argv[++i]);
        if (!strcmp(argv[i], "-x1")) X1 = atoi(argv[++i]);
        if (!strcmp(argv[i], "-x2")) X2 = atoi(argv[++i]);
        if (!strcmp(argv[i], "-p")) P = atoi(argv[++i]);
        i++;
    }
    if (!FILEPATH.empty())
    {
        readFile();
    }
    omp_set_num_threads(P);

    rectangleRule();
    rectanglePar();
    trapezoidalRule();
    trapezPar();
    simpsonRule();
    simpsonPar();
    return 0;
}
