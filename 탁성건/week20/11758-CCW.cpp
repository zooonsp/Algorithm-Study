#include <iostream>
using namespace std;

int cross(int x1, int y1, int x2, int y2) { return x1 * y2 - x2 * y1; }

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int x1, y1, x2, y2, x3, y3;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

  int res = cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
  cout << (res ? (res > 0 ? 1 : -1) : 0) << '\n';

  return 0;
}
