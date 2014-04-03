#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "timers.h"
#include "exprtk.hpp"

using namespace std;

string FUN = "";
string FILEPATH = "";
int N = 500;

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
  double x1,x2,result,t,dx,x;
  x1 = 0; x2 = 1; 
  result = 0; t = 0;

  dx = (x2 - x1) / N;
  pTimer zegar = newTimer(); 
  startTimer(zegar); 
  for(int i = 1; i <= N; i++)
    {
      x = x1 + i * dx;
      t += f<double>(x - dx / 2);
      if(i < N) result += f<double>(x);
    }
  result = dx / 6 * (f<double>(x1) + f<double>(x2) + 2 * result + 4 * t);
  stopTimer(zegar);  
  
  cout << endl << "Wynik calkowania metoda Simpsona: " << result << endl << "czas: ";
  printTimer(zegar); 
  cout << endl;
  freeTimer(zegar);  
}
void rectangleRule() {
  double x1, x2, h, result;

  x1 = 0;
  x2 = 1;

  h = (x2 - x1) / (double)N;

  result = 0;
  pTimer zegar = newTimer(); 
  startTimer(zegar); 
  for (int i = 1; i <= N; i++)
    result += f<double>(x1 + i*h)*h;
  stopTimer(zegar);  
  cout << endl << "Wynik calkowania metoda prostokatow: " << result << endl << "czas: ";
  printTimer(zegar); 
  cout << endl;
  freeTimer(zegar); 
}
void trapezoidalRule(){
  double x1, x2, h, result;

  x1 = 0;
  x2 = 1;

  h = (x2 - x1) / (double)N;

  result = 0;
  pTimer zegar = newTimer(); 
  startTimer(zegar); 
  for (int i = 1; i<N; i++)
      result += f<double>(x1 + i * h);
  result += f<double>(x1) / 2;
  result += f<double>(x2) / 2;
  result *= h;
  stopTimer(zegar);  
  cout << endl << "Wynik calkowania metoda trapezow: " << result << endl << "czas: ";
  printTimer(zegar); 
  cout << endl;
  freeTimer(zegar); 
}
void readFile(){
  ifstream infile(FILEPATH.c_str());
  string n;
  string fun;
  getline(infile,n);
  getline(infile,fun);
  N = atoi(n.c_str());
  FUN = fun;
}

int main(int argc, char** argv){
  int i = 0;
  while (i < argc){
    if (!strcmp(argv[i], "-fun")) FUN = argv[++i];
    if (!strcmp(argv[i], "-f")) FILEPATH = argv[++i];
    if (!strcmp(argv[i], "-n")) N = atoi(argv[++i]);
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
