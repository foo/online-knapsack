#include <iostream>
#include <cmath>
using namespace std;

//double g(double s) {
//  if(s > 0.33333)
//   return -18.0*s/25.0+9.0/25.0;
// else
//   return (-687.0/1480.0)*s+2033.0/7400.0;
//}

/*double g(double s) {
  if(s > 1.0/4.0)
    return (-2.0/3.0)*s+1.0/3.0;
    else
     {
      const double A = (vfi - 1.0/6.0)/(fi - 1.0/4.0);
      const double B = 1.0/6.0 - (1.0/4.0)*A;
      cout << "A*s+B = "<< A*s+B << '\n';
      return A*s+B;
    }
    }*/

const double R = 1.0 / (log(2.0) + 1.0); 


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

double lower(double s) {
  if(s <= 0.33333)
    return (R - Fxs(2.0/3.0)-(2.0/3.0)*(1.0-xs(2.0/3.0))) / s;
    else
  return (R - Fxs(2.0*s) -2*s*(1.0-xs(2.0*s))) / s;
}

const double real_fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
const double vfi = (R-2.0/3.0)/(real_fi-2.0/3.0);
const double fi = real_fi;
double g(double s) {
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
}

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
  for(double x = 0.0; x <= 1.0;x += 0.00001)
    cout << x << ' ' << lower(x) << ' ' << upper(x) << ' ' << (lower(x) - upper(x)) << ' ' << g(x) << ' ' << lowerB(x) << ' ' << upperB2(x) << ' ' << naive_upper(x) << '\n';
  cout << 1.0 << ' ' << lower(1.0) << ' ' << upper(1.0) << ' ' << (lower(1.0) - upper(1.0)) << ' ' << g(1.0) << ' ' << lowerB(1.0) << ' ' << upperB2(1.0) << ' ' << naive_upper(1.0) << '\n';
  return 0;
}

