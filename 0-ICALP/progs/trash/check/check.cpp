#include <iostream>
#include <math.h>
using namespace std;

const double e = M_E;
const double R = 1.0/(log(2.0*e));
const double R2 = (4.0/5.0)*(1.0-R*log(8.0/5.0));

double g(double x) { return (-18.0/25.0)*x+(9.0/25.0); }
//double g(double x) { return (-25.0/18.0)*x+0.5; }
double f(double x) { return R*(log(2.0*x)+1.0); }
double inv_f(double x) { return R*(log(2.0*x)+1.0); }

double stack(double s) {
  double acc = 0.0;
  while(acc + s <= 1.0)
    acc += s;
  return acc;
  //nreturn 2.0/5.0+s;
}


int main() {
  cout << e << endl;
  cout << R << endl;
  cout << log(e) << endl;
  double minG = 1;
  
  const double step = 0.0001;
  for(double a = 0.5; a >= 0.33; a -= step)
    for(double b = 0.33; b <= 0.5; b += step)
      if(a > b)
	{
	  //  const double G = max(0.0, (b+a-0.5))*max(0.0, (g(b)-g(a)))+
	  //	    g(a)*(a-stack(b))
	  //	    + (1.0-a)*(f(1.0-a)-R)+stack(b)*(R+1.0-f(stack(b)));
	  //
	  //	  const double sta = stack(a);
	  //	  const double stb = stack(b);
	  //
	  //
	  //	  const double Gext = (1.0 - a)*inv_f(1.0-a) + R*stb-R*(1.0-a) + a*g(a) +
	  //	    (1.0 - inv_f(stb) - g(a))*stb
	  //	    + max(0.0, 0.5 + b - (1.0-a))*max(0.0,(g(b) - g(a)));
	  //
	  //	  cout << G << endl;
	  //	  cout << Gext << endl;
	  //	  cout << endl;
	  // if(G < R)
	  //	    {
	  //	  cout << a << endl;
	  //	  cout << b << endl;
	  //	  cout << G << endl;
	  //	  cout << endl;
	  //	    }
	  //  if(minG > G)
	  // minG = G;
                  //const double stb = (b < 3.0/8.0 && b > 1.0/3.0) ? 2.0/3.0 : 3.0/4.0;//(b < 3.0/8.0 && b > 1.0/3.0) ? 2.0/3.0 : 3.0/4.0;//stack(b);//min(stack(b), 3.0/4.0);//stack(b);
                  /*const double A = -18.0/25.0;
	  	  const double left = (b+a-0.5)*(b-a)+(a-0.5)*(a-stack(b));
	  	  const double left_estim = (b+a-0.5)*(b-a)+(a-0.5)*(a-stack(b));
	  	  const double right_estim = (R/2.0)*(1.0 -2.0*a)+stb*(R+1.0-f(stack(b)));
	  	  const double right = (1.0-a)*(f(1.0-a)-R)+stack(b)*(R+1.0-f(stack(b)));
	  	  //R-R*(1.0-a)*log(2.0-2.0*a)-2.0*b+2.0*b *R*log(4.0*b);
                        if(A*left_estim + right_estim > A*left + right)
                        {
                            cout << "estim bigger\n";
                            return 0;
                        }
                        
	  	  if (A*left + right < R)
                  {
                      
                      cout << "MEGAFAIL\n";
                      return 0;
                }
	  	  if (A*left_estim + right_estim < R)
	  	  //if(left >= 0)
	  	    {
                      cout << "FAIL\n";
	  	      cout << left << endl;
	  	      cout << right << endl;
	  	      cout << right_estim << endl;
	  	      cout << a << ' ' << b << endl;
                      cout << (A*left + right) << endl;
                      cout << (A*left + right_estim) << endl;
	  	      cout << endl;
                      return 0;
	  	    }*/
            const double expr = 
                (-A*2*b-R)*a +A()
                
            ;
	}
  cout << "SUCCESS\n" << endl;
  
  return 0;
}
