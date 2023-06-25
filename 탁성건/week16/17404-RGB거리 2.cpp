#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 987654321;
enum { R, G, B };

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<vector<int>> cost(N, vector<int>(3));
  vector<vector<int>> dp(N, vector<int>(3));

  int ans = INF;

  for (int i = 0; i < N; i++)
    cin >> cost[i][R] >> cost[i][G] >> cost[i][B];

  for (int startColor = 0; startColor < 3; startColor++) {
    dp[0][R] = dp[0][G] = dp[0][B] = INF;
    dp[0][startColor] = cost[0][startColor];

    for (int i = 1; i < N; i++) {
      dp[i][R] = cost[i][R] + min(dp[i - 1][G], dp[i - 1][B]);
      dp[i][G] = cost[i][G] + min(dp[i - 1][R], dp[i - 1][B]);
      dp[i][B] = cost[i][B] + min(dp[i - 1][R], dp[i - 1][G]);
    }

    for (int endColor = 0; endColor < 3; endColor++) {
      if (endColor == startColor)
        continue;
      ans = min(ans, dp[N - 1][endColor]);
    }
  }

  cout << ans << '\n';

  return 0;
}
