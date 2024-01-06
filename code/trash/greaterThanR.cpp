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
  return -9999999999;
  //return s/(-2.0*R)+0.5;
}

double inv_g(double s) {
  return -18.0*s/25.0+9.0/25.0;
  //return -2.0*R*s + R;
}

double G1(double s) {
  return s * (2.0 + 2.0*R - 2.0*inv_f(2.0*s)+inv_g(s));
}

double G2(double s) {
  return inv_f(1.0-s)*(1.0-s)+(1.0-inv_g(s) - inv_f(1.0-s))*2.0*s + inv_g(s)*s;
}

double G3(double s) {
  return inv_f(1.0-s)*(1.0-s)+R*(2.0*s)-R*(1.0-s)+inv_g(s)*s + (1.0-inv_f(2.0*s)-inv_g(s))*2.0*s;
}

double G4(double a, double b) {
  return inv_f(1.0-b)*(1.0-a)+(1.0-inv_g(a)-inv_f(1.0-b))*2.0*b + inv_g(a)*a + (inv_g(b) - inv_g(a))*(0.5+b-1.0+a);
}

double G5(double a, double b) {
  return (1.0 - a)*inv_f(1.0-a) + F(inv_f(2.0*b))-F(inv_f(1.0-a)) + a*inv_g(a) + (1.0 - inv_f(2.0*b) - inv_g(a))*2.0*b + (0.5 + b - (1.0-a))*(inv_g(b) - inv_g(a));
;
}

double G6(double s) {
  return s*R + (4.0/5.0)*(1.0 - R*(log(2.0*s)+1.0));
}

double G7(double s) {
  return (1.0-s)*inv_f(1.0-s)
    +R*4.0/5.0 - R*(1.0-s)
    +(4.0/5.0)*(1.0-inv_f(1.0-s)-inv_g(s))
    +s*inv_g(s);
}

int main() {
  for(double a = 0.25; a <= 0.5; a += 0.00001)
    {
      if(G7(a) < G6(4.0/5.0)){
	return 0;
	 cout << "fail" << endl;
      }

      cout << G7(a) << '\t' << G6(4.0/5.0) << endl;
    }
  return 0;

  
  for(double b = 0.3333334; b <= 0.5; b += 0.00001)
   for(double a = b; a <= 0.5; a += 0.00001)
     {
       if(!(G4(a,b) >= R && G4(a,b) <= 1.0))
       {
	 cout << "wrong G4 for a = " << a << ", b = " << b << endl;
	 return 1;
       }

       if(!(G5(a,b) >= R && G5(a,b) <= 1.0))
       {
	 cout << "wrong G5 for a = " << a << ", b = " << b << endl;
	 return 1;
       }
     }

  
  for(double s = 0.3333334; s <= 0.5; s += 0.00001)
    {
      if(!(G1(s) >= R && G1(s) <= 1.0))
	{
	 cout << "wrong G1 for s = " << s << endl;
	 return 1;
       }

      if(!(G2(s) >= R && G2(s) <= 1.0))
	{
	 cout << "wrong G2 for s = " << s << endl;
	 return 1;
       }

      if(!(G3(s) >= R && G3(s) <= 1.0))
	{
	 cout << "wrong G3 for s = " << s << endl;
	 return 1;
       }

      if(!(G6(s) >= R && G6(s) <= 1.0))
	{
	 cout << "wrong G6 for s = " << s << endl;
	 return 1;
       }

    }

    cout << "ok\n";
  
  return 0;
}

