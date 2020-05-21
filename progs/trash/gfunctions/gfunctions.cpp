#include <iostream>
#include <cmath>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1); 
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
}

double inv_g(double s) {
  return 0.5-s;
}

double gain_g1(double x) {
  return x*(2.0+2.0*R-2.0*inv_f(2.0*x)+inv_g(x));
}
/*
double worse_gain_g2(double x, double y) {
  return inv_f(1.0-y)*(1.0-y)+(1.0-inv_g(y)-inv_f(1.0-y))*2.0*x + (inv_g(y))*y;
}


double gain_g2(double x, double y) {
  return inv_f(1.0-y)*(1.0-y)+(1.0-inv_g(y)-inv_f(1.0-y))*2.0*x + inv_g(x)*x + (inv_g(y)-inv_g(x))*y;
}
*/

double gain_g2(double y) {
  return inv_f(1.0-y)*(1.0-y)+(1.0-inv_g(y)-inv_f(1.0-y))*2.0*y+inv_g(y)*y;
}

double gain_g3(double s)
{
  return inv_f(1.0-s)*(1.0-s)+(F(inv_f(2.0*s))-F(inv_f(1.0-s)))+inv_g(s)*s+(1.0-inv_f(2.0*s)-inv_g(s))*2.0*s;
}

double better_gain_g3(double x, double y) {
  return inv_f(1.0-y)*(1.0-y) +
    (F(inv_f(2.0*x)) - F(inv_f(1.0 - y))) +
    (1.0 - inv_g(x) - inv_f(2.0*x))*2.0*x +
    inv_g(x)*x +
    (inv_g(x)-inv_g(y))*y;
}

/*
double gain_g3(double x, double y) {
  return inv_f(1.0-y)*(1.0-y) +
    (F(inv_f(2.0*x)) - F(inv_f(1.0 - y))) +
    (1.0 - inv_g(x) - inv_f(2.0*x))*2.0*x +
    inv_g(x)*y;
    }*/

//double gain_g2(double x, double y) {
//  return inv_f(1.0-y)+(1.0-inv_g(x)-inv_f(1.0-y))*2.0*x + inv_g(x)*x + (inv_g(x)-inv_g(y))*y;
//}

bool g2_check()
{
  cout << "Starting g2 check" << endl;
  for(double y = 0.3333334; y <= 0.5;y += 0.0001)
    {
      if(gain_g2(y) < R)
	{
	  cout << y << ' ' << gain_g2(y) << endl;
	  return false;
	}
    }
  return true;
}

bool g3_check() {
    for(double y = 0.3333334; y <= 0.5;y += 0.0001)
    {
      if(gain_g3(y) < R)
	{
	  cout <<  y << ' ' << gain_g3(y) << endl;
	  return false;
	}
      // cout << x << ' ' << y << ' ' << gain_g2(x,y) << endl;
    }
  return true;
}

int main() {
  if(g3_check())
    cout << "success" << endl;
  else
    cout << "fail" << endl;
  return 0;
}

