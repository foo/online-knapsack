#include <iostream>
#include <cmath>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1); 
const double n = 100;

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double xs(double s) {
  return R * (log(2.0 * s) + 1.0);
}

double Fxs(double s) {
  return R * s;
}

double lower(double s) {
  // return R/s - 2.0-Fxs(2.0*s)/s+2.0*xs(2.0*s);
  return R/s-2.0-2.0*R+2.0*xs(2.0*s);
}

double upper(double s) {
  return 1.0/s-1.0+(1.0-xs(1.0-s))*(3.0*s-1.0)/s-R/s;
}

double upper2(double s) {
  //return (1.0-s)*xs(1.0-s)/s+(Fxs(2.0*s)-Fxs(1.0-s))/s+(1.0-xs(2.0*s))*2.0-R/s;
  return (1.0-s)*xs(1.0-s)/s +3.0*R-2.0*R/s+2.0*(1.0-xs(2.0*s));
}

double diff(double s) {
  //return upper2(s) - lower(s);
  //return (1.0-s)*xs(1.0-s)/s + 5.0*R-3.0*R/s+4.0+4.0*(1.0-xs(2.0*s));
  return (1.0-s)*xs(1.0-s)/s +5.0*R-3.0*R/s+4.0-4.0*xs(2.0*s);
}


int main() {
  for(double x = 0.0; x <= 1.0;x += 0.0001)
    cout << x << ' ' << lower(x) << ' ' << upper(x) << ' ' << upper2(x) << ' ' << diff(x) << '\n';
  cout << 1.0 << ' ' << lower(1.0) << ' ' << upper(1.0) << ' ' << upper2(1.0) << ' ' << diff(1.0) << '\n';
  return 0;
}

