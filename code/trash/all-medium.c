#include <stdio.h>
#include <math.h>
#include <assert.h>

double E = exp(1.0);
double R = 1.0 / (log(2.0) + 1.0); 
double n = 100;

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double inv_f(double s) {
  return R * (log(2.0 * s) + 1.0);
}

double Fxs(double s) {
  return R * s;
}

double stack(double s) {
  double acc = 0.0;
  while(acc + s <= 1.0)
    acc += s;
  return acc;
}

double min(double a, double b) {
  return (a > b) ? b : a;
}

double inv_g_lower(double s) {
  double stc = stack(s);

  return R * (1.0 - stc) + (1.0 - inv_f(stc))*stc;
}

// we set inv_g to its lower bound
double inv_g(double s) {
  return inv_g_lower(s);
}

double G2(double s) {
  return inv_f(1.0-s)*(1.0-s) + (1.0-inv_g(s) - inv_f(1.0-s))*stack(s) + inv_g(s)*s;
}

double G4(double a, double b) {
  assert(a >= b);

  return inv_f(1.0 - b)*(1.0-a) + (1.0-inv_g(a)-inv_f(1.0-b))*stack(b) + inv_g(a)*a
    + (inv_g(b) - inv_g(a)) * min(0.0, a+b-0.5);
}

double G3(double s) {
  double stc = stack(s);
  return inv_f(1.0-s)*(1.0 - s) + R*stc - R*(1.0-s) + inv_g(s)*s + (1.0 - inv_f(stc)) - inv_g(s)*stc;
}

double G5(double a, double b) {
  assert(a >= b);

  double stc = stack(b);

  return (1.0-a)*inv_f(1.0-a) + R*(stc) - R*(1.0-a) + a * inv_g(a)
    + (1.0 - inv_f(stc) - inv_g(a)) * stc
    + (inv_g(b) - inv_g(a)) * min(0.0, a+b-0.5);
}

double G6(double s) {
  return s*inv_g(s) + (1.0-s)*inv_f(1.0-s) + F(1.0 - inv_g(s)) - R*(1.0 - s);
}

int main() {

  printf("%f\n", R);
  for(double b = 0.3333334; b <= 0.5; b += 0.00001)
   for(double a = b; a <= 0.5; a += 0.00001)
     {
       if(!(G4(a,b) >= R && G4(a,b) <= 1.0))
       {
	 printf("wrong G4\n");
	 return 1;
       }

       if(!(G5(a,b) >= R && G5(a,b) <= 1.0))
       {
	 printf("wrong G5\n");
	 return 1;
       }
     }

  
  for(double s = 0.3333334; s <= 0.5; s += 0.00001)
    {
      if(!(G2(s) >= R && G2(s) <= 1.0))
	{
	 printf("wrong G2\n");
	 return 1;
       }

      if(!(G3(s) >= R && G3(s) <= 1.0))
	{
	 printf("wrong G3\n");
	 return 1;
       }

      if(!(G6(s) >= R && G6(s) <= 1.0))
	{
	 printf("wrong G6\n");
	 return 1;
       }

    }

  printf("ok\n");
  return 0;
}

