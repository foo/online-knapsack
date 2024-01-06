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
double K(double a, double b) { return 0; }
double M(double a) { return 0; }

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

const double step = 0.001;

// case description:
// no M buckets, some M*, B*, L-buckets
// stack(t*) < 1-fi
// tight t* implies gain(D) >= area(t*)
//
// part of (fi, 1] algorithm
void case_nom_Mstar() {
  // nom Mstar case works for wide range of (0.2, 0.5]
  for(double s = 0.2 + step; s < 0.5; s += step) {
    const double stack_s = stack(s);
    gain L = gain::F_to_level(stack_s);
    gain Mstar = gain::rect(1.0 - inv_f(stack_s), stack_s);
    gain D = gain::rect_with_L(g(s), s);
    gain total = L + Mstar + D;
    if(!total.Rcompetitive())
      {
	cout << s << endl;
      }
    assert(total.total_gain());
    assert(total.Rcompetitive());
  }
  cout << "TEST case_nom FINISHED\n";
}

// ALG[0.2, 1]
// case description
// no M-buckets, some M*, B*, L-buckets
// stack(t*) >= 1-fi
//
// part of (fi, 1] algorithm
void case_nom_Bstar() {
  // any gain on D is sufficient when we have B* buckets
  
  // existance of B* buckets imply that something at least fi and at most 2*[0.2, fi] is rejectable
  // and hence some item smaller than 2fi is tight
   for(double s = fi + step; s < 2.0 * fi; s += step) {
     const double b_star_is_at_least = 1.0 - fi;
     gain L = gain::F_to_level(b_star_is_at_least);
     gain Bstar = gain::rect(1.0 - inv_f(b_star_is_at_least), b_star_is_at_least);
     gain D = gain::rect_with_L(g(s), s);
     gain total = L + Bstar + D;
     assert(total.total_gain());
     assert(total.Rcompetitive());
  }
  cout << "TEST case_nom_Bstar FINISHED\n";
}

// case description
// 
void case_m_leq_1_3() {
  for(double s = fi + step; s < 1.0 / 3.0; s += step) {
    // full D with a tight item <= 1/3 imply minimum possible gain on Mstar
    gain L_Mstar = gain::rect(1.0 - g(s), 2.0 / 3.0);
    gain M = gain::rect(g(s), s);
    gain total = L_Mstar + M;
    assert(total.total_gain());
    if(!total.Rcompetitive())
      {
	cout << s << endl;
	total.print();
      }
    assert(total.Rcompetitive());
  }
  cout << "TEST case_m_leq_1_3 FINISHED\n";
}

void case_m_Bstar() {
   // existance of B* buckets imply that something at least fi and at most 2*[0.2, fi] is rejectable
  // and hence some item smaller than 2fi is tight

  // D sits completely in M-buckets
   for(double m = fi + step; m < 2.0 * fi; m += step) {
       const double b_star_is_at_least = 1.0 - fi;
       gain L = gain::F_to_level(b_star_is_at_least);
       gain water = gain::M(1.0-m);
       gain Bstar = gain::rect(1.0 - inv_f(b_star_is_at_least) - g(m), b_star_is_at_least);
       gain D = gain::rect(g(m), m);
       gain total = L + water + Bstar + D;
       if(!total.total_gain())
	 {
	   total.print();
	 }
       assert(total.total_gain());
       if(!total.Rcompetitive())
	 {
	   
	   total.print();
	   cout << m << ' ' << endl;
	 }
       assert(total.Rcompetitive());
     }
  cout << "TEST case_m_Bstar FINISHED\n";
}

void case_m_geq_1_3() {
  // two parameters: m* and t*
  const double m_step = 0.01;
  for(double m = 1.0/3.0 + m_step; m < 1.0 / 2.0; m += m_step) {
    double minimum_t_arg;
    double minimum_val = 1.0; // which is the maximum possible value
    
    //for(double t = fi; t < m; t += step) { // possibly enough to check t < 1/3
    for(double t = m; t >= fi; t -= step) { // possibly enough to check t < 1/3
      const double stack_t = stack(t);
      gain L = gain::F_to_level(stack_t);
      gain water = gain::M(1.0-m);
      gain Mstar = gain::rect(1.0 - inv_f(stack_t) - g(m), stack_t);


      gain impr = gain::rect_with_L(g(t) - g(m), max(0.0, t - 0.5 + m));
      assert(g(t) - g(m) >= 0.0);
      gain D = gain::rect(g(m), m);
      gain total = L + water + Mstar + D + impr;
      assert(total.total_gain());
      assert(total.Rcompetitive());

      cout << "m: " << m << " t: " << t << " stack(t): " << stack(t) << " gain: " << total.area << " mstar: " << (1.0-inv_f(stack_t)-g(m)) << " x: " << L.width << " y: " << Mstar.width << " z: " << D.width << endl;
      cout << g(m) << ' ' << inv_f(stack_t) << endl;
    
      if(total.area < minimum_val) {
	minimum_val = total.area;
	minimum_t_arg = t;
      }
    }
    //cout << "m: " << m << " min_t: " << minimum_t_arg << " stack(t): " << stack(minimum_t_arg) << " gain: " << minimum_val << " diffg: " << g(minimum_t_arg) - g(m) << endl;
  }
  cout << "TEST case_m_geq_1_3 FINISHED\n";
}

int main() {
  test_eq();
  gain_test();

  case_nom_Mstar();
  case_nom_Bstar();
  case_m_leq_1_3();
  case_m_geq_1_3();
  case_m_Bstar();

  cout << fi << ' ' << vfi << ' ' << fi*vfi << ' ' << 0.5-vfi << endl;
  cout << gain::F_to_level(1.0).area << endl;
  cout << gain::F_to_level(0.8).area << endl;
  cout << inv_f(1.0) << endl;
  cout << "PROGRAM FINISHED SUCCESSFULLY\n";
  
  return 0;
}

