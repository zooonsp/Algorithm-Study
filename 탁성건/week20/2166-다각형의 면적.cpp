#include <cmath>
#include <iostream>
using namespace std;

struct Vector {
  long long x;
  long long y;

  long long cross(const Vector &rhs) { return x * rhs.y - y * rhs.x; }
};

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cout << fixed;
  cout.precision(1);

  int N;
  cin >> N;

  long long res = 0;
  Vector v0, v1, v2;

  cin >> v1.x >> v1.y;
  v0 = v1;

  for (int i = 0; i < N - 1; ++i) {
    cin >> v2.x >> v2.y;
    res += v1.cross(v2);
    v1 = v2;
  }

  res += v1.cross(v0);

  cout << abs((double)res / 2) << '\n';

  return 0;
}
