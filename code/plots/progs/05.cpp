#include <iostream>
#include <cmath>
using namespace std;

const double E = exp(1.0);
const double R = 1.0 / (log(2.0) + 1); 

double f_without_if(double x) {
  return 0.5 * pow(E, (x - R) / R);
}

double plot(double x) {
  return f_without_if(x);
}

int main() {
  for(double x = 0.0; x <= 1.0;x += 0.0001)
    cout << x << ' ' << plot(x) << '\n';
  cout << 1.0 << ' ' << plot(1.0) << '\n';
  return 0;
}

