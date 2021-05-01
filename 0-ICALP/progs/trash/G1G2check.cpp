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

double G1(double x, int int_m) {
  float m = (float)int_m;
  assert(1.0/m <= x);
  assert(x < 1.0/(m-1.0));

  float M = (m-1.0)*x;

  return x*inv_g(x) + R*M + (1.0-inv_f(M))*M;
}


double G2(double y, int int_m) {
  float m = (float)int_m;
  assert(1.0/m <= y);
  assert(y < 1.0/(m-1.0));

  float M = (m-1.0)*y;

  return (1.0-y)*inv_f(1.0-y) + R*M - R*(1.0-y) + (1.0 - inv_f(1.0-y) - inv_g(y))*M + inv_g(y)*y;
}

int main() {
  const double tol = 0.001;
  for(double x = 0.0; x <= 1.0;x += 0.00001) {
    assert(abs(x - g(inv_g(x)) < tol));
    assert(abs(x - inv_g(g(x)) < tol));
  }

  for(int m = 3; m <= 1000000; ++m) {
    for(double x = 1.0/(double)m; x < 1.0/((double)m-1.0); x += 0.00001) {
    if(G1(x,m) >= R && G2(x,m) >= R)
      {}
    else {
      cout << "wrong " << m << endl;
      return 0;
    }

    }
  }
   
  return 0;
}

