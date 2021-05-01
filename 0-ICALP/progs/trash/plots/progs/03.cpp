#include <iostream>
#include <cmath>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1); 

double xs(double s) {
  return R * (log(2.0 * s) + 1.0);
}

double plot(double s) {
  return xs(s);
}

int main() {
  for(double x = 0.0; x <= 1.0;x += 0.0001)
    cout << x << ' ' << plot(x) << '\n';
  cout << 1.0 << ' ' << plot(1.0) << '\n';
  return 0;
}

