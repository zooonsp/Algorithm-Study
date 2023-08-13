#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<int> cnt('Z' - 'A' + 1);

  while (N--) {
    string str;
    cin >> str;

    int digit = 1;

    for (int i = str.size() - 1; i >= 0; --i) {
      cnt[str[i] - 'A'] += digit;
      digit *= 10;
    }
  }

  sort(cnt.begin(), cnt.end(), greater<int>());

  int ans = 0;

  for (int i = 0; i < 9; ++i)
    ans += cnt[i] * (9 - i);

  cout << ans << '\n';

  return 0;
}
