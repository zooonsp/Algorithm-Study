#include <iostream>
#include <vector>
using namespace std;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  int high = N;
  int low = 1;

  vector<int> limits(N);
  vector<int> heights(N);

  for (int i = 0; i < N; ++i) {
    cin >> limits[i];
    heights[i] = limits[i] > 0 ? high-- : low++;
  }

  if (limits[N - 1] < 0) {
    cout << -1;
    return 0;
  }

  for (const int &height : heights)
    cout << height << ' ';

  return 0;
}
