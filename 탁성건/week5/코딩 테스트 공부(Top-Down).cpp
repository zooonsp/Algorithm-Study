#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 987654321;
int dp[151][151];
int maxAlp, maxCop;

int dfs(int alp, int cop, const vector<vector<int>> &problems) {
  if (alp >= maxAlp && cop >= maxCop)
    return 0;

  if (dp[alp][cop] != -1)
    return dp[alp][cop];

  int res = MAX;

  for (auto prob : problems) {
    if (alp < prob[0] || cop < prob[1])
      continue;

    int na = min(alp + prob[2], maxAlp);
    int nc = min(cop + prob[3], maxCop);

    if (na == alp && nc == cop)
      continue;

    res = min(res, dfs(na, nc, problems) + prob[4]);
  }

  return dp[alp][cop] = res;
}

int solution(int alp, int cop, vector<vector<int>> problems) {
  problems.push_back({0, 0, 1, 0, 1});
  problems.push_back({0, 0, 0, 1, 1});

  maxAlp = alp;
  maxCop = cop;

  for (auto prob : problems) {
    maxAlp = max(maxAlp, prob[0]);
    maxCop = max(maxCop, prob[1]);
  }

  memset(dp, -1, sizeof(dp));

  return dfs(alp, cop, problems);
}
