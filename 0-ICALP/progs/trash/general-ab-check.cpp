#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double n = 100;

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double inv_f(double s) {
  return R * (log(2.0 * s) + 1.0);
}

double Fxs(double s) {
  return R * s;
}

double g(double s) {
  return 0.5 - s;
  //return s/(-2.0*R)+0.5;
}

double inv_g(double s) {
  return 0.5-s;
  //return -2.0*R*s + R;
}

int main() {
  const double tol = 0.001;
  for(double a = 0.3333334; a <= 0.5; a += 0.00001) {
   for(double b = 0.3333334; b <= 0.5; b += 0.00001) {
      if(a > b && 1.0-a < 2.0*b)
	{
	  double gain_ab = (1.0 - a)*inv_f(1.0-a) + F(inv_f(2.0*b))-F(inv_f(1.0-a)) + a*inv_g(a)
	    + (1.0 - inv_f(2.0*b) - inv_g(a))*2.0*b;
	  double gain_ab_plus = gain_ab + (0.5 + b - (1.0-a))*(inv_g(b) - inv_g(a));
	  bool cond = gain_ab_plus >= R && gain_ab_plus <= 1.0;
	  if(!cond)
	    {
	      cout << a << ' ' << b << endl;
	      return 1;
	    }
	}
       }
      }

    cout << "ok\n";
  
  return 0;
}

