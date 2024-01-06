#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double prec = 0.00001;
bool geq(double a, double b) { return a + prec > b; }
bool leq(double a, double b) { return a < b + prec; }
bool eq(double a, double b) { return geq(a, b) && leq(a, b); }


const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double g = 0.0372226;

// fi is the point at which g(s) boundaries cross
const double fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
// vfi is the value of the boundaries in the crossing case
const double vfi = (R-2.0/3.0)/(fi-2.0/3.0);

double fun1(double a) {
  return (1.0 + R*log(1.0-a))/(36.0*g);
}

double fun2(double b) {
  return (R*log(2.0*b))/(18.0*g) + 1.25;
}

int main() {

  // test przeciecia kazdej funkcji z osobna z obramowaniem
  const double step = 0.00001;
  for(double a = 1.0/3.0; a <= 0.5; a += step)
      {
	double a_coord = a;
	double b_coord = fun1(a);

	if(
	   1.0/3.0 < a_coord && a_coord < 0.5 &&
	   1.0/3.0 < b_coord && b_coord < 0.5)
	  {
	  cout << "inside fun1\n";
	  break;
	  }
      }

  for(double b = 1.0/3.0; b <= 0.5; b += step)
      {
	double a_coord = fun2(b);
	double b_coord = b;

	if(
	   1.0/3.0 < a_coord && a_coord < 0.5 &&
	   1.0/3.0 < b_coord && b_coord < 0.5)
	  {
	  cout << "inside fun2\n";
	  break;
	  }
      }


  for(double a = 1.0/3.0; a <= 0.5; a += step)
    for(double b = 1.0/3.0; b <= 0.5; b += step)
      {
	double a_coord1 = a;
	double b_coord1 = fun1(a);

	double a_coord2 = fun2(b);
	double b_coord2 = b;

	if(eq(a_coord1, a_coord2) && eq(b_coord1, b_coord2))
	  cout << a << ' ' << b << endl;
      }
  return 0;
}

