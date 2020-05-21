#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double inv_f(double s) {
  assert(s >= 0.5);
  return R * (log(2.0 * s) + 1.0);
}

double Fxs(double s) {
  return R * s;
}

double stack(double s) {
  //double acc = 0.0;
  //while(acc + s <= 1.0)
  // acc += s;
  //return acc;
  if(s >= 0.33333)
    return 2.0 * s;
  else
    return 1.0-s;
}

double inv_g (double s)
{
  const double join = 0.33333;
  const double z = 0.333333;
  
  if(s >= join)
    return 0.5 - s;
  else
    {
      return ((0.5 - join - z)/join)*s + z;
    }
}



double G2(double a, double b) {
  const double st = stack(b);
  return (1.0 - a)*inv_f(1.0-a) + R*st-R*(1.0-a) + a*inv_g(a) + (1.0 - inv_f(stack(b)) - inv_g(a))*st + max(0.0, 0.5 + b - (1.0-a))*max(0.0,(inv_g(b) - inv_g(a)));
;
}

int main()
{
  const double step = 0.001;

  const double b = 0.45;
  
  for(double a = 0.0001; a <= 0.5; a += step)
    //  for(double b = 0.0001; b <= 0.5; b += step)
      cout << a << ' ' << ' ' << G2(a,b) << endl;
  return 0;
}
