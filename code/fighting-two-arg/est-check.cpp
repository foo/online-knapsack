#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double n = 10000;

// fi is the point at which g(s) boundaries cross
const double fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
// vfi is the value of the boundaries in the crossing case
const double vfi = (R-2.0/3.0)/(fi-2.0/3.0);

const double prec = 0.00001;
bool geq(double a, double b) { return a + prec > b; }
bool leq(double a, double b) { return a < b + prec; }
bool eq(double a, double b) { return geq(a, b) && leq(a, b); }

bool checkEst(double A, double B)
{
  double step = 0.00001;
  double g = 0.0372226;
  for(double a = 0.33334; a <= 0.5; a += step)
    for(double b = 0.33334; b < a; b += step)
      {
	bool succ = true;
	double expr =  -18.0*g*a*a + (-R + 18.0*g + 36.0*g*b + 9.0*g)*a + R/2.0
	  - 18.0*g*b - 18.0*g*b*b - 9.0*g*b + 2.0*b - 2.0*R*b*log(4.0 * b) - R;
	if(!geq(expr, 0.0))
	  {
	    return false;
	  }

	//double blogbEst = sqrt(0.75)*(b-1.0)*sqrt(b);
	//double blogbEst = -91.0*b/60.0 + 133.0/60.0;
	double blogbEst = A*b+B;
	double minus2RbLogEstimation = -2.0*R*b*log(4.0) - 2.0*R*blogbEst;
	//double minus2RbLogEstimation = -2.0*R*b*log(4.0*b);

	double est =  -18.0*g*a*a + (-R + 18.0*g + 36.0*g*b + 9.0*g)*a + R/2.0
	  - 18.0*g*b - 18.0*g*b*b - 9.0*g*b + 2.0*b + minus2RbLogEstimation - R;

	if(!geq(est, 0.0))
	  {
	    return false;
	  }
	if(!leq(est,expr))
	  {
	    return false;
	  }

      }
  return true;

}


int main() {
  /* double step = 0.001;
  for(double A = -5.0; A <= 5.0; A += step)
    for(double B = -5.0; B <= 5.0; B += step)
      {
	if(checkEst(A, B))
	  {
	    cout << A << ' ' << B << endl;
	  }
      }
  cout << "Fail\n";
  */
  cout << checkEst(0.0, -log(2.0)/2.0);
  cout << checkEst(0.0, -9.0/26.0);
   return 0;
}
