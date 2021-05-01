#include <iostream>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;


const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1.0); 

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
  //nreturn 2.0/5.0+s;
}

double join;
double z;

double inv_g_two_linear7(double s)
{
  if(s >= join)
    return 0.5 - s;
  else
    {
      return ((0.5 - join - z)/join)*s + z;
    }
}

double A, B, C, D;

double inv_g_cubic(double s)
{
  return s*s*s*A+s*s*B+C*s+D;
}


double inv_g_quad(double s)
{
  return s*s*A+s*B+C;
}

double inv_g_candidate_violates(double s)
{
  return -(18.0/25.0)*s + 9.0/25.0;
}

double inv_g(double s) {
  return inv_g_candidate_violates(s);
  //return inv_g_cubic(s);
  //return inv_g_two_linear7(s);
}

double G1(double s) {
  const double st = stack(s);

  if(inv_f(2.0*s)+inv_g(s) > 1.0)
	return 0.0;


  
  if(s >= 0.33334)
    {
      
      return R*st + inv_g(s)*s + st*(1.0-inv_f(st));
    }
  else
    {
      return R*(2.0/3.0) + inv_g(s)*s + (2.0/3.0)*(1.0-inv_f(2.0/3.0));
    }
}

double G2_1arg(double s) {
  const double st = stack(s);

  if(s >= .333334)
    {
      //assert(inv_f(2.0*s)+inv_g(s) <= 1.0);
      if(inv_f(2.0*s)+inv_g(s) > 1.0)
	return 0.0;

      return (1.0 - s) * inv_f(1.0 - s) + F(2.0*s) - F(1.0-s) + 2.0*s*(1.0 - inv_f(2.0*s) - inv_g(s)) + inv_g(s)*s;
    }
 else // s < 1/3
   {
     
     //assert(inv_f(2.0*s)+inv_g(s) <= 1.0);
      if(inv_f(2.0*s)+inv_g(s) > 1.0)
	return 0.0;
     
     return (2.0/3.0)*(1.0-inv_g(s))+s*inv_g(s);
   }
}


double G2(double a, double b) {
  const double sta = stack(a);
  const double stb = stack(b);

  if(a < b)
    {
      cout << "a < b" << endl;
      return 0.0;
    }

  if(a >= .333334)
    {
      if(stb > sta)
	{
	  // (1)
	  return (1.0 - a)*inv_f(1.0-a) + R*sta-R*(1.0-a) + a*inv_g(a) + (1.0 - inv_f(sta) - inv_g(a))*sta; 
	}
      else
	{
	  // (2)
	  if (!(0.5 + b - (1.0 - a) >= 0.0)) return 0.0;
	  if(!(inv_g(b) >= inv_g(a))) return 0.0;
	  if(! (b >= 1.0-2.0*a)) return 0.0;

      return (1.0 - a)*inv_f(1.0-a) + R*stb-R*(1.0-a) + a*inv_g(a) + (1.0 - inv_f(stb) - inv_g(a))*stb + max(0.0, 0.5 + b - (1.0-a))*max(0.0,(inv_g(b) - inv_g(a)));
	}
    }
 else // a < 1/3
   {
     // (3)
     //return (1.0 - a)*inv_f(1.0-a) + R*(2.0/3.0)-R*(1.0-a) + a*inv_g(a) + (1.0 - inv_f(2.0/3.0) - inv_g(a))*(2.0/3.0);

     // new
     return (2.0/3.0)*(1.0-inv_g(a))+a*inv_g(a);
   }
}

double G6(double s) {
  return s*inv_g(s) + (1.0-s)*inv_f(1.0-s)+F(1.0-inv_g(s))-R*(1.0-s);
}

// testing framework

int starting_level = 2; // 1/3, 1/2
int ending_level = 500;
double step = 0.005;
double tolerance = 0.0001;
double epsilon = 0.000001;

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

int level;
double a;
double b;
double s;

double start;
double end;

const int NO_LEVEL = -1;
int levelG1 = NO_LEVEL; 
int levelG2 = NO_LEVEL;
int levelG3 = NO_LEVEL; 
int levelG4 = NO_LEVEL;
int levelG5 = NO_LEVEL;
int levelG6 = NO_LEVEL;

pair<double, double> level_to_interval(int l)
{
  // some horrible hack used to be here
  //if(level == 4)
    // return make_pair(0.21, 0.25);
  return make_pair(1.0 / float(level + 1) + epsilon,
		   1.0 / float(level));
}

void report_level()
{
  cout << " at level " << level << " =interval ( " << level_to_interval(level).first << ", " <<
    level_to_interval(level).second << endl;
}

bool report_ab(string fun_name)
{
  cout << "wrong " << fun_name << " for a = " << a << ", b = " << b;
  report_level();
}

void report_s(string fun_name)
{
  cout << "wrong " << fun_name << " for s = " << s;
  report_level();
}

bool test_competitive_ratio(double gain)
{
  return geq_test(gain,R) && leq_test(gain,1.0);
}

void report_levels()
{
  if(levelG1 == NO_LEVEL) cout << "G1 was OK on all levels" << endl;
  if(levelG2 == NO_LEVEL) cout << "G2 was OK on all levels" << endl;
  if(levelG3 == NO_LEVEL) cout << "G3 was OK on all levels" << endl;
  if(levelG4 == NO_LEVEL) cout << "G4 was OK on all levels" << endl;
  if(levelG5 == NO_LEVEL) cout << "G5 was OK on all levels" << endl;
  if(levelG6 == NO_LEVEL) cout << "G6 was OK on all levels" << endl;
  cout << "END" << endl;
}

int run_tests()
{
  const double g_step = 0.005;
  const double g_coeff = 2.0;
  //join = 0.33333;
  //z = 0.333333;
  //for(join = 0.4; join >= 0.1; join -= g_step)
  // for(z = inv_g(join); z <= 0.5; z += g_step)
  //for(A = -g_coeff; A <= g_coeff; A += g_step)
  A = 0.0;
  B = 0.0;
  C = -18.0/25.0;
  D = 9.0/25.0;
  //for(B = -g_coeff; B <= g_coeff; B += g_step)
  //for(C = -g_coeff; C <= g_coeff; C += g_step)
  //for(D = -g_coeff; D <= g_coeff; D += g_step)
      for(level = starting_level; level <= 400; ++level)
	{
	  start = level_to_interval(level).first;
	  end = level_to_interval(level).second;
	  assert(start <= end);

	  bool ok = true;
  
	  for(s = start; s <= end; s += step)
	    {
	        if(!test_competitive_ratio(G1(s)))
		{
		  ok = false;
		  break;
		}

	      if(!test_competitive_ratio(G2_1arg(s)))
		{
		  ok = false;
		  break;
		}
	    }
	  
	  for(b = start; b <= end; b += step)
	    for(a = b; a <= end; a += step)
	      {
		if(!test_competitive_ratio(G2(a,b)))
		  {
		    ok = false;
		    b = end + 1;
		    break;
		  }
	      }
	  

	  if(!ok)
	    {
	      // break out of levels loop
	      //cout << "FAIL" << endl;
	      break;
	    }

	  if(ok && level >= 2)
	    {
	      //cout << "(" << level << ") success z: " << z << ", join: " << join << ", inv_g(join): " << inv_g(join) << endl;
	      cout << setw(11) << B << ' ' << setw(11) << C << ' ' << setw(11) << D;
	      report_level();
	    }
	  
	}

  cout << "end" << endl;
  return 0;
}


int main() {
  return run_tests();
}

