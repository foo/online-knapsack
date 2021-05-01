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

double tolerance = 0.0001;
bool geq_test(double a, double b)
{
  return a >= b - tolerance;
}

bool leq_test(double a, double b)
{
  return a <= b + tolerance;
}


//double g(double s) {
// return 0.5 - s;
  //return s/(-2.0*R)+0.5;
//}

double inv_g_linear(double s)
{
  return 0.5 - s;
}

double inv_g_linear2(double s)
{
  return (2.0*R-2.0)*s + 0.5-R;
  // = g^{-1}(s)
  // g(s)=(1/(2.0*R-2.0))*s+0.5;
}

double inv_g_two_linear(double s)
{
  if(s >= 0.25)
    return 0.5-s;
  else
    return -2.0*s-6.0/8.0;
}


double inv_g_two_linear2(double s)
{
  if(s >= 0.25)
    return 0.5-s;
  else
    return (10.0/4.0)*s+1.0-R;
}

double inv_g_two_linear3(double s)
{
  if(s >= 0.25)
    return -4.0*R*s + 2.0*R;
  else
    return (4.0*R-2.0)*s - R;
}

double inv_g_two_linear4(double s)
{
  if(s >= 1.0-R)
    return (1.0/(2.0-4.0*R))*s + 1.0/(8.0*R-4.0);
  else
    return (1.0/(2.0-2.0*R))*s+0.5;
}

double inv_g_two_linear5(double s)
{
  if(s >= 1.0-R)
    return (1.0/(4.0*R-6.0))*s + 1.0/(8.0*R-4.0);
  else
    return (1.0/(2.0*R-2.0))*s+0.5;
}

double inv_g_linear2_inv(double s)
{
  return (1.0/(2.0*R-2.0))*s+0.5;
}

double inv_g_lower_bound(double s)
{
  //return R/s-2.0-2.0*R+2.0*inv_f(stack(s));
  double st = stack(s);
  return (R - R*st - st*(1.0-inv_f(st)))
	  /s;
}


double inv_g(double s) {
  return inv_g_linear(s);
  //return inv_g_lower_bound(s);
}

double max_small = 1.0 / 8.0;
double s_acc_bucket = 1.0 - max_small;

double G1(double s) {
  const double st = stack(s);
  if(leq_test(st,s_acc_bucket))
    return R*st + inv_g(s)*s + st*(1.0-inv_f(st));
  else
    {
      cout << "aoeu" << endl;
    return R*s_acc_bucket + inv_g(max_small)*max_small + s_acc_bucket,st*(1.0-inv_f(s_acc_bucket));
    }
  //return s * (2.0 + 2.0*R - 2.0*inv_f(stack(s))+inv_g(s));
}

double G2(double s) {
  return inv_f(1.0-s)*(1.0-s)+(1.0-inv_g(s) - inv_f(1.0-s))*min(s_acc_bucket,stack(s)) + inv_g(s)*s;
}

double G3(double s) {
  const double st = stack(s);
  return inv_f(1.0-s)*(1.0-s)+R*min(s_acc_bucket,st)-R*(1.0-s)+inv_g(s)*s + (1.0-inv_f(min(s_acc_bucket,st))-inv_g(s))*min(s_acc_bucket,st);
}

double G4(double a, double b) {
  const double st = stack(b);
  return inv_f(1.0-b)*(1.0-a)+(1.0-inv_g(a)-inv_f(1.0-b))*min(s_acc_bucket,st) + inv_g(a)*a + (inv_g(b) - inv_g(a))*max(0.0,0.5+b-1.0+a);
}

double G5(double a, double b) {
  const double st = stack(b);
  return (1.0 - a)*inv_f(1.0-a) + R*min(s_acc_bucket,st)-R*(1.0-a) + a*inv_g(a)
    + (1.0 - inv_f(min(s_acc_bucket,st)) - inv_g(a))*min(s_acc_bucket,st)
    + max(0.0, 0.5 + b - (1.0-a))*(inv_g(b) - inv_g(a));
}

double G6(double s) {
  return s*inv_g(s) + (1.0-s)*inv_f(1.0-s)+F(min(1.0-inv_g(s), inv_f(s_acc_bucket)))-R*(1.0-s);
}

// testing framework

int starting_level = 2; // 1/3, 1/2
int ending_level = 20; // 1/21, 1/20
double step = 0.0001;
double epsilon = 0.0001;

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
  for(level = starting_level; level <= ending_level; ++level)
    {
      start = level_to_interval(level).first;
      end = level_to_interval(level).second;
      assert(start < end);

      for(b = start; b <= end; b += step)
	for(a = b; a <= end; a += step)
	  {
	    if(levelG4 == NO_LEVEL && !test_competitive_ratio(G4(a,b)))
	      {
		levelG4 = level;
		report_ab("G4");
	      }

	    if(levelG5 == NO_LEVEL && !test_competitive_ratio(G5(a,b)))
	      {
		levelG5 = level;
		report_ab("G5");
	      }
	  }

  
      for(s = start; s <= end; s += step)
	{
	  if(levelG1 == NO_LEVEL && !test_competitive_ratio(G1(s)))
	    {
	      levelG1 = level;
	      report_s("G1(lower_bound)");
	    }

	  if(levelG2 == NO_LEVEL && !test_competitive_ratio(G2(s)))
	    {
	      levelG2 = level;
	      report_s("G2");
	    }

	  if(levelG3 == NO_LEVEL && !test_competitive_ratio(G3(s)))
	    {
	      levelG3 = level;
	      report_s("G3");
	    }

	  if(levelG6 == NO_LEVEL && !test_competitive_ratio(G6(s)))
	    {
	      levelG6 = level;
	      report_s("G6");
	    }

	}
    }
  report_levels();
  return 0;
}


int main() {
  return run_tests();
}

