#include <algorithm>
#include <string>
#include <vector>
using namespace std;

char ch[]{'d', 'l', 'r', 'u'};
int dy[]{0, -1, 1, 0};
int dx[]{1, 0, 0, -1};

int N, M, K;
int R, C;
vector<vector<vector<string>>> dp;

string dfs(int x, int y, int cnt) {
  if (cnt >= K) {
    if (x == R && y == C)
      return "";
    return "z";
  }

  if (dp[x][y][cnt] != "")
    return dp[x][y][cnt];

  string ret = "z";

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx <= 0 || nx > N || ny <= 0 || ny > M)
      continue;

    string temp = dfs(nx, ny, cnt + 1);

    if (temp == "z")
      continue;

    ret = min(ret, ch[i] + temp);

    break;
  }

  return dp[x][y][cnt] = ret;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
  N = n, M = m, R = r, C = c, K = k;
  dp = vector<vector<vector<string>>>(
      N + 1, vector<vector<string>>(M + 1, vector<string>(2501)));

  string answer = dfs(x, y, 0);

  if (answer == "z")
    answer = "impossible";

  return answer;
}
