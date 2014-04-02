#include <iostream>
#include <string>
#include <math.h>
#include "timers.h"

using namespace std;

string FUN = "";
string FILEPATH = "";
int N = 500;


double f1(double x) { return cos(x); }

void rectangleRule() {
  double x1, x2, h, result;

  x1 = 0;
  x2 = 1;

  h = (x2 - x1) / (double)N;

  cout << "krok: h=" << h << endl;

  result = 0;
  pTimer zegar = newTimer(); // make new timer
  startTimer(zegar); // store first timestamp
  for (int i = 1; i <= N; i++)
    result += f1(x1 + i*h)*h;
  stopTimer(zegar);  // store second timestamp
  printTimer(zegar); // show time difference
  freeTimer(zegar);  // free occupied ram
  cout << endl << "Wynik calkowania metoda prostokatow: " << result << endl;
}

void trapezoidalRule(){
  double x1, x2, h, result;

  x1 = 0;
  x2 = 1;

  h = (x2 - x1) / (double)N;

  cout << "krok: h=" << h << endl;

  result = 0;
  pTimer zegar = newTimer(); // make new timer
  startTimer(zegar); // store first timestamp
  for (int i = 1; i<N; i++)
    {
      result += f1(x1 + i * h);
    }
  result += f1(x1) / 2;
  result += f1(x2) / 2;
  result *= h;
  stopTimer(zegar);  // store second timestamp
  printTimer(zegar); // show time difference
  freeTimer(zegar);  // free occupied ram
  cout << endl << "Wynik calkowania metoda trapezow: " << result << endl;
}

int main(int argc, char** argv){
  int i = 0;
  while (i < argc){
    if (!strcmp(argv[i], "-fun")) FUN = argv[++i];
    if (!strcmp(argv[i], "-f")) FILEPATH = argv[++i];
    if (!strcmp(argv[i], "-n")) N = atoi(argv[++i]);
    i++;
  }
  rectangleRule();
  trapezoidalRule();

  return 0;
}
