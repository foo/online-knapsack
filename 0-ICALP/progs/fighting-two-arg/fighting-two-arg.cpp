#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 
const double n = 10000;

// fi is the point at which g(s) boundaries cross
const double fi = (1.0 - log(9.0/4.0))/log(64.0 / 27.0);
// vfi is the value of the boundaries in the crossing case
const double vfi = (R-2.0/3.0)/(fi-2.0/3.0);

double g(double s) {
  if(s < 0.5 - vfi)
    return vfi;
  else
    return -s+1.0/2.0;
}
/*double g(double s) {
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
    }*/
double area_g(double s) { return g(s) * s; }


const double prec = 0.0001;
bool geq(double a, double b) { return a + prec > b; }
bool leq(double a, double b) { return a < b + prec; }
bool eq(double a, double b) { return geq(a, b) && leq(a, b); }
void test_eq() {
  assert(geq(2.0, 1.0));
  assert(leq(1.0, 2.0));
  assert(eq(2.0+1.0, 4.0-1.0));
  assert(eq(prec/2.0, 0.0));
}

double F(double x) { return R * pow(2.0 * E, x - 1.0); }
double inv_f(double s) { return R * (log(2.0 * s) + 1.0); }
double F_inv_f(double s) { return R * s; }

struct gain {
  double width, area;
  gain(double w = 0.0, double a = 0.0) : width(w), area(a) {}
  static gain rect(double x, double y) { return gain(x, x * y); } 
  static gain rect_with_L(double x, double y) { return gain(0.0, x * y); } 
  static gain M(double s) { return gain(0.0, R * s * log(2.0 * s)); } 
  static gain F_to_level(double y) { return gain(inv_f(y), F_inv_f(y)); } 
  gain operator+(const gain& p) const { return gain(width+p.width, area+p.area); }
  gain operator-(const gain& p) const { return gain(width-p.width, area-p.area); }
  bool total_gain() const { return eq(width, 1.0) && leq(area, 1.0) && geq(area, 0.0); }
  bool nonnegative() const { return geq(area, 0.0) && geq(width, 0.0); }
  bool Rcompetitive() const { assert(total_gain()); return geq(area, R); }
  void print() const { cout << "  <" << setprecision(7) << width << "> " << setprecision(7) << area << '\n'; }
};
void gain_test() {
  {
    gain L = gain::F_to_level(0.8);
    gain Mstar = gain::rect(1.0 - inv_f(0.8), 0.8);
    gain total = L + Mstar;
    assert(total.total_gain());
    assert(!total.Rcompetitive());
  }


}

double stack(double s) {
  double acc = 0.0;
  while(acc + s <= 1.0)
    acc += s;
  return acc;
}

const double step = 0.0001;

void case_m_geq_1_3() {
  // two parameters: m* and t*

  const double m_step = 0.001;
  for(double m = 1.0/3.0 + m_step; m < 1.0 / 2.0; m += m_step) {

    // for(double m = 1.0/3.0 + step; m < 1.0 / 2.0; m += step) {
    double minimum_t_arg;
    double minimum_val = 1.0; // which is the maximum possible value

    gain total_mt;
    gain total_mm;
    int where_min = 0;

    // Temporary: check just for t > 1/3
    for(double t = m; t > fi; t -= step) {
      double stack_t = stack(t);
      assert(stack_t <= 1.0);
      
      if(g(m) + inv_f(stack_t) < 1.0) { // there are some stacks
	{
	  gain L = gain::F_to_level(stack_t);
	  gain water = gain::M(1.0-m);
	  gain Mstar = gain::rect(1.0 - inv_f(stack_t) - g(m), stack_t);
	  assert(Mstar.nonnegative());

	  gain impr = gain::rect_with_L(g(t) - g(m), t - 0.5 + m);
	  assert(impr.nonnegative());
	  gain D = gain::rect(g(m), m);
	  assert(D.nonnegative());
	  total_mt = L + water + Mstar + D + impr;
	  assert(total_mt.total_gain());
	  assert(total_mt.Rcompetitive());
	}

	{
	  gain L = gain::F_to_level(2.0*m);
	  gain water = gain::M(1.0-m);
	  gain Mstar = gain::rect(1.0 - inv_f(2.0*m) - g(m), 2.0*m);
	  assert(Mstar.nonnegative());

	  gain D = gain::rect(g(m), m);
	  assert(D.nonnegative());
	  total_mm = L + water + Mstar + D;
	  assert(total_mm.total_gain());
	  assert(total_mm.Rcompetitive());
	  assert(total_mm.area >= R);
	}

	if(stack_t < 2.0*m)
	  {
	double diff = total_mt.area - total_mm.area;

	assert(diff >= 0);
	double przeksztalcone = 
	  stack_t*R - 2.0*R*m
	  + stack_t - stack_t*inv_f(stack_t) - stack_t*g(m)
	  - 2.0*m + 2.0*m*inv_f(2.0*m) + 2.0*m*g(m)
	  + (g(t)-g(m))*(t+m-0.5);

	assert(eq(przeksztalcone, diff));
        
        if(t > 1.0/3.0)
        {
            double a = m;
            double b = t;
            //double przeksztalcone2 =
            //    2.0*R*b - 2.0*R*a
            //    + 2.0 * b - 2.0*b*inv_f(2.0*b)-2.0*b*(0.5-a)
             //   -2.0*a + 2.0*a*inv_f(2.0*a)+2.0*a*(0.5-a)
             //   +(a-b)*(b+a-0.5);
            //double przeksztalcone2 =
            //    2.0*R*b - 2.0*R*a
             //   + 2.0 * b - b + 2.0*a*b
             //   -2.0*a +a-2.0*a*a
             //   +a*b + a*a-0.5*a-b*b-a*b+0.5*b
             //   
             //   + 2.0*a*inv_f(2.0*a)
             //   - 2.0*b*inv_f(2.0*b);
                
            //double przeksztalcone2 =
            //    2.0*R*b - 2.0*R*a
             //   + 2.0 * b - b + 2.0*a*b
             //   -2.0*a +a-2.0*a*a
            //    +a*b + a*a-0.5*a-b*b-a*b+0.5*b
            //    
             //   + 2.0*a*inv_f(2.0*a)
             //   - 2.0*b*inv_f(2.0*b);
                
           // double przeksztalcone2 =
           //     m*(-2.0*R - 3.0/2.0)
           //     + t*(2.0*R+3.0/2.0)
           //     - (m-t)*(m-t)
           //     + 2.0*m*inv_f(2.0*m)
           //     - stack_t*inv_f(stack_t);
                
           // double przeksztalcone2 =
           //     a*(-2.0*R-3.0/2.0)
           //     +b*(2.0*R+3.0/2.0)
           //     -(a-b)*(a-b)
           //     + 2.0*m*inv_f(2.0*m)
           //     - stack_t*inv_f(stack_t);
                
           // double przeksztalcone2 =
           //     (b-a)*(2.0*R+3.0/2.0)
            //    -(a-b)*(a-b)
            //    + 2.0*m*inv_f(2.0*m)
            //    - stack_t*inv_f(stack_t);
                
            //double przeksztalcone2 =
            //    (b-a)*(a-b+2.0*R-3.0/2.0)
            //    + 2.0*m*inv_f(2.0*m)
            //    - stack_t*inv_f(stack_t);
            
            //  double przeksztalcone2 =
             //   (b-a)*(2.0*R+3.0/2.0)
            //    -(a-b)*(a-b)
            //    + 2.0*R*(a-b + a * log(4.0*a) - b * log(4.0*b));
                
              double przeksztalcone2 =
                (b-a)*(3.0/2.0)
                -(a-b)*(a-b)
                + 2.0*R*(a * log(4.0*a) - b * log(4.0*b));
                
            assert(g(m) == 1.0/2.0-m);
          
            assert(eq(przeksztalcone, przeksztalcone2));
            
            assert(2.0*b+log(2.0)-1.0 >= log(4.0*b));
            assert(log(4.0*a) >= ((3.0/2.0)*(log(2.0) - log(4.0/3.0))*4.0*a -2.0*log(2.0) + 3.0*log(4.0/3.0)));
            
            
            double est =
                (b-a)*(2.0*R+3.0/2.0)
                -(a-b)*(a-b)
            
                
                +2.0*R*(a-b+a*(   ((3.0/2.0)*(log(2.0) - log(4.0/3.0))*4.0*a -2.0*log(2.0) + 3.0*log(4.0/3.0))   )
                                               -b*(log(4.0*b)));
                
                cout << a << ' ' << b << endl;
                
            assert(leq(est, przeksztalcone));
            assert(leq(est, przeksztalcone2));

            //assert(geq(est, 0));
        } 
        


	//assert(leq(est, przeksztalcone));

	//assert(geq(est, 0));
	assert(geq(przeksztalcone, 0));
	  }
     }
   
    }
    
    //cout << "m: " << m << " t: " << minimum_t_arg << " stack(t): " << stack(minimum_t_arg) << " gain: " << minimum_val << " where: " << where_min << endl;
  }
  cout << "TEST case_m_geq_1_3 FINISHED\n";
}

int main() {
  test_eq();
  gain_test();

  case_m_geq_1_3();

  cout << fi << ' ' << vfi << ' ' << fi*vfi << endl;

  cout << "PROGRAM FINISHED SUCCESSFULLY\n";
  
  return 0;
}

