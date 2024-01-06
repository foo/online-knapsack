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
  if(s > 0.33333)
    return -18.0*s/25.0+9.0/25.0;
  else
    return (-687.0/1480.0)*s+2033.0/7400.0;
}

double area(double s) {
  return g(s) * s;
}

double case_no_m(double mst, double m_star_level) {
  assert(mst >= 0.2);
  assert(mst <= 0.5);
  assert(m_star_level <= 1);
  assert(m_star_level > 0.5);

  return Fxs(m_star_level) + m_star_level * (1.0 - inv_f(m_star_level)) + area(mst);
}

double case_some_m(double min, double x) {
  return (1.0-min)*inv_f(1.0-min)
    + Fxs(1.0-fi) - Fxs(1.0-min)
    + (1.0-fi)*(1.0- inv_f(1.0-fi) - g(x))
    + area(min);
    //+ max(area(x), area(min));
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
  const double step = 0.001;
  for(double min = fi; min < 0.333333; min += step)
    for(double x = 0.4; x < 2.0*fi; x += step)
      {
	double gain = case_some_m(min, x);
	    cout << gain << endl;
	    assert(gain <= 1.0);
	if(gain < R)
	  {
	  cout << "FAIL\n";
	  cout << min << endl;
	  cout << x << endl;
	  cout << gain << endl;
	  return 0;
	  }
      }
    cout << "ok\n";


     for(double x = 0.4; x < 2.0*fi; x += step)
      {
	
	assert(case_no_m(x, 1.0-fi) >= R);
      }

     cout << "ok\n";
  
  return 0;
}

