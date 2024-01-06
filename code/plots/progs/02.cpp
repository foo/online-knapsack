#include <iostream>
#include <cmath>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1); 

double F(double x) {
  return R * pow(2.0 * E, x - 1.0);
}

double plot(double x) {
  return F(x);
}

int main() {
  for(double x = 0.0; x <= 1.0;x += 0.0001)
    cout << x << ' ' << plot(x) << '\n';
  cout << 1.0 << ' ' << plot(1.0) << '\n';
  return 0;
}
