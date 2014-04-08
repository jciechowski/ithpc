#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "timers.h"
#include "exprtk.hpp"

using namespace std;

string FUN = "";
string FILEPATH = "";
int N = 0;
int X1 = 0;
int X2 = 0;

template<typename T>
double f(T x){
  exprtk::symbol_table<T> symbol_table;
  symbol_table.add_variable("x",x);
  symbol_table.add_constants();

  exprtk::expression<T> expression;
  expression.register_symbol_table(symbol_table);

  exprtk::parser<T> parser;
  parser.compile(FUN,expression);
  return expression.value();
}
void simpsonRule() {
  ofstream outfile("pomiary/simpson.dat", ios::out | ios::app);
  double x1,x2,result,t,h,x, avgTime;
  x1 = X1; x2 = X2;
  t = 0; avgTime = 0;
  pTimer zegar = newTimer(); 

  h = (x2 - x1) / N;
  startTimer(zegar); 
  for(int j = 0; j < 5; j++)
  {
    result = 0; t = 0;
    for(int i = 1; i <= N; i++)
      {
        x = x1 + i * h;
        t += f<double>(x - h / 2);
        if(i < N)
          result += f<double>(x);
      }
    result = h / 6 * (f<double>(x1) + f<double>(x2) + 2 * result + 4 * t);
    stopTimer(zegar);  
    avgTime += getTime(zegar);
  }
  
  outfile << N << ": " << result << " " << avgTime/5 << "\n";
  outfile.close(); 
  freeTimer(zegar);  
}
void rectangleRule() {
  ofstream outfile("pomiary/rectangle.dat", ios::out | ios::app);
  double x1, x2, h, result, avgTime;
  avgTime = 0;
  x1 = X1; x2 = X2;
  pTimer zegar = newTimer(); 

  h = (x2 - x1) / N;
  for(int j = 0; j < 5; j++)
  {
    result = 0;
    startTimer(zegar); 
    for (int i = 1; i <= N; i++)
      result += f<double>(x1 + i * h) * h;
    stopTimer(zegar); 
    avgTime += getTime(zegar);
  } 

  outfile << N << ": " << result << " " << avgTime/5 << "\n";
  outfile.close();
  freeTimer(zegar); 
}
void trapezoidalRule(){
  ofstream outfile("pomiary/trapez.dat", ios::out | ios::app);
  double x1, x2, h, result, avgTime;
  x1 = X1; x2 = X2;
  avgTime = 0;
  pTimer zegar = newTimer(); 

  h = (x2 - x1) / N;
  for(int j = 0; j < 5; j++)
  {
    result = 0;
    startTimer(zegar); 
    for (int i = 1; i < N; i++)
      result += f<double>(x1 + i * h);
    result += f<double>(x1) / 2;
    result += f<double>(x2) / 2;
    result *= h;
    stopTimer(zegar);  
    avgTime += getTime(zegar);
  }

  outfile << N << ": " << result << " " << avgTime/5 << "\n";
  outfile.close();
  freeTimer(zegar); 
}
void readFile(){
  ifstream infile(FILEPATH.c_str());
  string n,fun,x1,x2;
  getline(infile,x1);
  getline(infile,x2);
  getline(infile,n);
  getline(infile,fun);
  X1 = atoi(x1.c_str());
  X2 = atoi(x2.c_str());
  N = atoi(n.c_str());
  FUN = fun;
}

int main(int argc, char** argv){
  int i = 0;
  while (i < argc){
    if (!strcmp(argv[i], "-fun")) FUN = argv[++i];
    if (!strcmp(argv[i], "-f")) FILEPATH = argv[++i];
    if (!strcmp(argv[i], "-n")) N = atoi(argv[++i]);
    if (!strcmp(argv[i], "-x1")) X1 = atoi(argv[++i]);
    if (!strcmp(argv[i], "-x2")) X2 = atoi(argv[++i]);
    i++;
  }
  if(!FILEPATH.empty())
  {
    readFile();
  }
  rectangleRule();
  trapezoidalRule();
  simpsonRule();

  return 0;
}
