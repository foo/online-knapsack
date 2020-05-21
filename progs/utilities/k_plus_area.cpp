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

/*
const double g(double s) {
  if(s > 1.0/3.0)
    return -6.0*vfi*s+3.0*vfi;
    else
     {
       return vfi;
    }
}
*/

/*double g(double s) {
  if(s < 0.5 - vfi)
    return vfi;
  else
    return -s+1.0/2.0;
    }*/
/*double g(double s) {
  if(s > 1.0/3.0)
    return -s+1.0/2.0;
    else
     {
       const double y = -(1.0/3.0)+0.5;
       const double x = 1.0/3.0;
      const double A = (vfi - y)/(fi - x);
      const double B = y - x*A;
      return A*s+B;
    }
    }*/


const double prec = 0.0001;
bool geq(double a, double b) { return a + prec > b; }
bool leq(double a, double b) { return a < b + prec; }
bool eq(double a, double b) { return geq(a, b) && leq(a, b); }
void test_eq() {
  assert(geq(2.0, 1.0));
  assert(leq(1.0, 2.0));
  assert(eq(2.0+1.0, 4.0-1.0));
  assert(eq(prec/2.0, 0.0));
}

double F(double x) { return R * pow(2.0 * E, x - 1.0); }
double inv_f(double s) { return R * (log(2.0 * s) + 1.0); }
double F_inv_f(double s) { return R * s; }

struct gain {
  double width, area;
  gain(double w = 0.0, double a = 0.0) : width(w), area(a) {}
  static gain rect(double x, double y) { return gain(x, x * y); } 
  static gain rect_with_L(double x, double y) { return gain(0.0, x * y); } 
  static gain M(double s) { return gain(0.0, R * s * log(2.0 * s)); } 
  static gain F_to_level(double y) { return gain(inv_f(y), F_inv_f(y)); } 
  gain operator+(const gain& p) const { return gain(width+p.width, area+p.area); }
  gain operator-(const gain& p) const { return gain(width-p.width, area-p.area); }
  bool total_gain() const { return eq(width, 1.0) && leq(area, 1.0) && geq(area, 0.0); }
  bool nonnegative() const { return geq(area, 0.0) && geq(width, 0.0); }
  bool Rcompetitive() const { assert(total_gain()); return geq(area, R); }
  void print() const { cout << "  <" << setprecision(7) << width << "> " << setprecision(7) << area << '\n'; }
};
void gain_test() {
  {
    gain L = gain::F_to_level(0.8);
    gain Mstar = gain::rect(1.0 - inv_f(0.8), 0.8);
    gain total = L + Mstar;
    assert(total.total_gain());
    assert(!total.Rcompetitive());
  }


}

double stack(double s) {
  double acc = 0.0;
  while(acc + s <= 1.0)
    acc += s;
  return acc;
}

double K(double x) {
  return x - R*x*log(2.0*x);
}

double xs(double s) {
  return R * (log(2.0 * s) + 1.0);
}
double Fxs(double s) {
  return R * s;
}
/*
double lower(double s) {
  if(s <= 0.33333)
    return (R - R*(2.0/3.0)-(2.0/3.0)*(1.0-inv_f(2.0/3.0))) / s;
    else
  return (R - R*(2.0*s) -2*s*(1.0-inv_f(2.0*s))) / s;
}
*/
double linear_fit(double x0, double y0, double x1, double y1, double x)
{
  return y0*(1.0 - (x - x0)/(x1-x0)) + y1*((x-x0)/(x1-x0));
}


double lower(double s) {
  if(s <= 0.33333)
    return (R - R*(2.0/3.0)-(2.0/3.0)*(1.0-inv_f(2.0/3.0))) / s;
    else
  return (R - R*(2.0*s) -2*s*(1.0-inv_f(2.0*s))) / s;
}


double g(double s) {

  if(s > 1.0/3.0)
    {
  const double x1 = fi;
  const double y1 = vfi;

  const double x3 = 0.5;
  const double y3 = 0.0;

  const double x2 = 1.0/3.0;
  double y2 = lower(1.0/3.0);

  if(s < x2)
      return linear_fit(x1, y1, x2, y2, s);
  else
      return linear_fit(x2, y2, x3, y3, s);
    }
  else
    {
      return lower(s);
    }
}

double area_g(double s) { return g(s) * s; }


int main() {
  test_eq();
  gain_test();

  cout << (K(1.0-fi)+area_g(2.0*fi)) << endl;
  cout << lower(1.0/3.0) << endl;
  cout << (R + (2.0/3.0)*(vfi - 1.0)) << endl;

  cout << fi*vfi << endl;
  cout << lower(1.0/3.0)*(1.0/3.0) << endl;

  cout << " \n";

  double max = -1.0;
  for(double x = fi; x < 0.5; x+= 0.0001)
    if(max*g(max) <= x*g(x))
      max = x;
  cout << max << ' ' << max*g(max) << endl;
  return 0;
}

