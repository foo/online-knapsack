#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double tolerance = 0.000001;

bool geq_test(double a, double b)
{
  return a >= b - tolerance;
}

bool leq_test(double a, double b)
{
  return a <= b + tolerance;
}


bool eq_test(double a, double b)
{
  return geq_test(a,b) && leq_test(a,b);
}


double inv_f(double s) {
  return R * (log(2.0 * s) + 1.0);
}

double inv_g(double s) {
  return (-18.0/25.0)*s+9.0/25.0;
}

double before(double a, double b)
{
  assert(a <= b);
  return
    (0.5+a)*(inv_g(a)-inv_g(b))
    + (1.0-b)*(inv_f(1.0-b) - (inv_g(a)-inv_g(b)))
    + R*(2.0*a - 1.0 + b)
    + 2*a*(1.0-inv_f(2.0*a)-inv_g(b))
    + b*inv_g(b);
}

double after(double a, double b)
{
  /*
  return a*(82.0/50.0 - 2.0*R*log(4.0))
    + a*a*(-18.0/25.0)
    - a*log(a)*2.0*R
    + log(a)*R
    - b*log(a)*R
    - b*(R*log(4))
    + a*b * 36.0/25.0
    + R*log(4)

    + R*log(2.0-2.0*b) - R*log(4.0) - R*log(a) - b*R*log(2.0-2.0*b) + b*R*log(4.0) + b*R*log(a);*/
  return (82.0/50.0 -2.0*R*log(4))*a
    - 18.0/25.0*a*a
    - 2*R*a*log(a)
    + 36.0/25.0*a*b
    + R*log(2.0-2.0*b)
    - R*log(2.0-2.0*b)*b;
}

int main()
{
  const double step = 0.00001;
  for(double a = 1.0/3.0; a <= 0.5; a += step)
    for(double b = a + step; b <= 0.5; b += step)
      if(!(eq_test(before(a,b), after(a,b))))
	{
	  cout << "a: " << a << ", b: " << b << ", before(a,b): " << before(a,b) << ", after(a,b): " << after(a,b) << ", delta: " << before(a,b)-after(a,b) << endl;
	  
	}
  return 0;
}
