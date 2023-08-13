#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<pii> meeting(N);

  for (auto &[en, st] : meeting)
    cin >> st >> en;

  sort(meeting.begin(), meeting.end());

  int ans = 0, now = 0;

  for (const auto [en, st] : meeting) {
    if (now <= st) {
      now = en;
      ++ans;
    }
  }

  cout << ans << '\n';

  return 0;
}
