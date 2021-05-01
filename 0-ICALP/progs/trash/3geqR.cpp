#include <stdio.h>
#include <math.h>
#include <assert.h>

const double R = 1 / (log(2) + 1);


double G3(double a, double b)
{
  assert(a <= b);
  return (82. / 50. - 2 * R * log(4)) * a 
	 - 18. / 25. * a * a
	 - 2 * R * a * log(a)
	 + 36. / 25. * a * b
	 + R * log(2 - 2 * b) * (1 - b);
}

int main(void)
{
  for (double a = 0.34; a <= 0.5; a += 0.0001)
    for (double b = a; b <= 0.5; b += 0.0001)
    {
      double c = (4 + a)/9;
      if (G3(a, b) < G3(c, c))
	printf("[%lf %lf %lf] %lf < %lf\n", a, b, c, G3(a, b), G3(c, c));
    }
  return 0;
}
