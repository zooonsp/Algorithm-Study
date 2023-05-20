#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> height;

int solve(int left, int right) {
  if (left == right)
    return height[left];

  int mid = left + (right - left) / 2;
  int ans = max(solve(left, mid), solve(mid + 1, right));

  int le = mid, ri = mid + 1;
  int h = min(height[le], height[ri]);

  ans = max(ans, h * 2);

  while (true) {
    if (left == le && ri == right)
      break;

    if (left < le && (ri == right || height[le - 1] >= height[ri + 1]))
      h = min(h, height[--le]);
    else if (ri < right && (left == le || height[le - 1] <= height[ri + 1]))
      h = min(h, height[++ri]);

    ans = max(ans, h * (ri - le + 1));
  }

  return ans;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N;
  vector<int>(N).swap(height);

  for (int &h : height)
    cin >> h;

  cout << solve(0, N - 1) << '\n';

  return 0;
}
