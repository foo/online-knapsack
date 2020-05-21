#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 

// fi is the point at which g(s) boundaries cross
const double fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
// vfi is the value of the boundaries in the crossing case
const double vfi = (R-2.0/3.0)/(fi-2.0/3.0);


// gamma
double y = 0.0372226;
double P(double s) { return s - R*s*log(2.0*s); }
double Q(double s) { return R*s*log(2.0*s); }

double g(double x) {
  if (x <= (1.0/3.0))
    return y/x;
  else
    return -18.0*y*x+9.0*y;
}


const double prec = 0.00001;
bool geq(double a, double b) { return a + prec > b; }
bool leq(double a, double b) { return a < b + prec; }
bool eq(double a, double b) { return geq(a, b) && leq(a, b); }

bool print = false;

bool checkEst(double A, double B)
{
  double step = 0.00001;
  for(double s = 0.33334; s <= 0.5; s += step)
      {
	// -R term added to check non-negativity
	double expr = 9.0*y*s*(1.0-2.0*s)+2.0*s*(1-R*log(4.0*s)) - R;

	if(!geq(expr, 0.0))
	  {
	    if(print)
	      cout << "FAIL0: for s = " << s << ", the expression has negative value " << expr << endl;
	    return false;
	  }

	double logEst = A*s+B;

	//double est =  9.0*y*s*(1.0-2.0*s)+2.0*s*(1-R*log(4.0*s)) - R; // original
	double est =  logEst - R;//9.0*y*s*(1.0-2.0*s)+2.0*s*(1-R*logEst) - R;
	
	if(!geq(est, 0.0))
	  {
	    if(print)
	      cout << "FAIL1: for s = " << s << ", the expression has value " << expr << " but the est has value " << est  << endl;
	    return false;
	  }
	if(!leq(est,expr))
	  {
	    if(print) 
	      cout << "FAIL2: for s = " << s << ", the expression has value " << expr << " but the est has value " << est << endl;
	    return false;
	  }

      }
  if(print)
    cout << "SUCCESS\n";
  return true;

}


int main() {
  const double fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);

  cout << "A\n";

  cout << (P(1.0-fi) + Q(1.0-2.0*fi)+g(2.0*fi)*(3.0*fi-1.0)) << endl;

  cout << "B\n";

  double ex =
    (1.0-fi) - R*(1.0 - fi)*log(2.0-2.0*fi)
    + R*(1.0-2.0*fi)*log(2.0-4.0*fi)
    + R*log(4.0/3.0)*2.0*fi
    - R*log(4.0/3.0)*(1.0-fi)-R;
  cout << ex << endl;

  double ex2 = P(1-fi) + Q(1.0-2.0*fi) + R*log(4.0/3.0) * (2.0*fi-1.0+fi)- R;
  cout << ex2 << endl;
  
  double step = 0.001;
  for(double A = -5.0; A <= 5.0; A += step)
    for(double B = -5.0; B <= 5.0; B += step)
      {
	if(checkEst(A, B))
	  {
	    cout << "FOUND LINEAR ESTIMATION OF LOG"<< endl;
	    cout << A << ' ' << B << endl;
	  }
      }
  cout << "END\n";
  
  // cout << checkEst(0.0, -log(2.0)/2.0);
  //cout << checkEst(0.0, -9.0/26.0);
   return 0;
}
