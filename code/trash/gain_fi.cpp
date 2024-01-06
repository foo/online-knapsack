#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double n = 100;
const double fi = 0.21;

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
  return -18.0*s/25.0+9.0/25.0;
}

double area(double s) {
  return g(s) * s;
}

double case_some_m(double mst, double m_star_level) {
  assert(mst >= 0.2);
  assert(mst <= 0.5);
  assert(m_star_level <= 1);
  assert(m_star_level > 0.5);

  return Fxs(m_star_level) + m_star_level * (1.0 - inv_f(m_star_level)) + area(mst);
}

// double G1(double s) {
//   return s * (2.0 + 2.0*R - 2.0*inv_f(2.0*s)+inv_g(s));
// }

// double G2(double s) {
//   return inv_f(1.0-s)*(1.0-s)+(1.0-inv_g(s) - inv_f(1.0-s))*2.0*s + inv_g(s)*s;
// }

// double G3(double s) {
//   return inv_f(1.0-s)*(1.0-s)+R*(2.0*s)-R*(1.0-s)+inv_g(s)*s + (1.0-inv_f(2.0*s)-inv_g(s))*2.0*s;
// }

// double G4(double a, double b) {
//   return inv_f(1.0-b)*(1.0-a)+(1.0-inv_g(a)-inv_f(1.0-b))*2.0*b + inv_g(a)*a + (inv_g(b) - inv_g(a))*(0.5+b-1.0+a);
// }

// double G5(double a, double b) {
//   return (1.0 - a)*inv_f(1.0-a) + F(inv_f(2.0*b))-F(inv_f(1.0-a)) + a*inv_g(a) + (1.0 - inv_f(2.0*b) - inv_g(a))*2.0*b + (0.5 + b - (1.0-a))*(inv_g(b) - inv_g(a));
// ;
// }

// double G6(double s) {
//   return s*R + (4.0/5.0)*(1.0 - R*(log(2.0*s)+1.0));
// }

// double G7(double s) {
//   return (1.0-s)*inv_f(1.0-s)
//     +R*4.0/5.0 - R*(1.0-s)
//     +(4.0/5.0)*(1.0-inv_f(1.0-s)-inv_g(s))
//     +s*inv_g(s);
// }

int main() {
  cout << case_some_m(1.0*fi, 1.0 - fi) << endl;
    cout << "ok\n";
  
  return 0;
}

