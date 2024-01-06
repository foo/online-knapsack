#include <iostream>
#include <cmath>
using namespace std;

//double g(double s) {
//  if(s > 0.33333)
//   return -18.0*s/25.0+9.0/25.0;
// else
//   return (-687.0/1480.0)*s+2033.0/7400.0;
//}

const double R = 1.0 / (log(2.0) + 1.0); 
const double real_fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
const double vfi = (R-2.0/3.0)/(real_fi-2.0/3.0);
const double fi = real_fi;

const double E = exp(1.0);

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double xs(double s) {
  return R * (log(2.0 * s) + 1.0);
}
double inv_f(double s) { return xs(s); }
double Fxs(double s) {
  return R * s;
}


double linear_fit(double x0, double y0, double x1, double y1, double x)
{
  return y0*(1.0 - (x - x0)/(x1-x0)) + y1*((x-x0)/(x1-x0));
}


double lower(double s) {
   if(s <= 0.33333)
     //return (R - R*(2.0/3.0)-(2.0/3.0)*(1.0-inv_f(2.0/3.0))) / s;
     return (R + (2.0/3.0)*(vfi - 1.0))/s; // to samo co wyzej
   else
     {
      return (R - R*(2.0*s) -2*s*(1.0-inv_f(2.0*s))) / s;
     }
   //;
}

/*
double g(double s) {
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
*/
double g(double s) {

  if(s > 1.0/3.0)
    {
      //return lower(1.0/3.0)*(1.0- (s-1.0/3.0)/(1.0/6.0));
      return -6.0*lower(1.0/3.0) * s + 3.0* lower(1.0/3.0);
      /*
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
      */
    }
  else
    {
      return lower(s);
    }
}
/*
double lower(double s) {
  if(s <= 0.33333)
    return (R - Fxs(2.0/3.0)-(2.0/3.0)*(1.0-xs(2.0/3.0))) / s;
    else
  return (R - Fxs(2.0*s) -2*s*(1.0-xs(2.0*s))) / s;
}
*/
/*const double g(double s) {
  if(s > 1.0/3.0)
    return -6.0*vfi*s+3.0*vfi;
    else
     {
       return vfi;
    }
    }*/

double upper(double s) {
  if(s < 1.0/3.0){
    return (3.0*R-2.0)/(3.0*s-2.0);
    
  }
    else
      return ((1.0-s)*xs(1.0-s)+Fxs(2.0*s)-Fxs(1.0-s) + 2.0*s*(1.0-xs(2.0*s))-R) / s;
}

double naive_upper(double s) {
  return ((1.0-s)*xs(1.0-s) + fi*(vfi + s - 0.5)+Fxs(2.0/3.0)-Fxs(1.0-s) + (2.0/3.0)*(1.0-xs(2.0/3.0))-R) / -(s-2.0/3.0 - (vfi + s -0.5));

}

double lowerB(double s) {
  return (R - (1.0-fi)*(R+1.0-inv_f(1.0-fi)))/s;

}

double upperB2(double s) {
  return (R - ((1.0-fi)*(1.0-inv_f(1.0-fi))
	       + R*(1.0-fi) - R*(1.0-s)
	       + (1.0-s) * inv_f(1.0-s)))/(s-1.0+fi);

}


int main() {
    cout << fi << endl;
  for(double x = 0.0; x <= 1.0;x += 0.00001)
    {
    cout << x << ' ' << lower(x) << ' ' << upper(x) << ' ' << g(x) << ' ' << g(x)*x << ' ' << lowerB(x) << ' ' << upperB2(x)  << '\n';
    }
  return 0;
}

