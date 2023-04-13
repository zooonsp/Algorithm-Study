#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// 하, 좌, 우, 상
// 사전순으로 배치
char ch[]{'d', 'l', 'r', 'u'};
int dy[]{0, -1, 1, 0};
int dx[]{1, 0, 0, -1};

int N, M, K;
int R, C;
// dp[x][y][cnt]
// => (x, y)에서 K-cnt번 움직일 수 있을 때 사전순으로 가장 빠른 탈출 경로 저장
vector<vector<vector<string>>> dp;

// (x, y)에서 K-cnt번 움직일 수 있을 때 사전순으로 가장 빠른 탈출 경로는?
string dfs(int x, int y, int cnt) {
  // K번 움직였을 때
  if (cnt >= K) {
    // (R, C)에 도착했다면 가능한 경우이므로 빈 문자열 반환
    if (x == R && y == C)
      return "";
    // 도착하지 못했다면 정답이 될 수 없는 사전순으로 가장 나중인 "z" 반환
    return "z";
  }

  // 이미 문제를 해결한 경우 기록된 값을 반환
  if (dp[x][y][cnt] != "")
    return dp[x][y][cnt];

  string ret = "z";

  // 사전순으로 모든 방향 확인
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx <= 0 || nx > N || ny <= 0 || ny > M)
      continue;

    // (nx, ny)에서 K-(cnt+1)번 움직일 수 있을 때 사전순으로 가장 빠른 탈출 경로
    string temp = dfs(nx, ny, cnt + 1);

    // 목적지에 도달할 수 없는 경우 continue
    if (temp == "z")
      continue;

    // 현재 방향을 선택했을 경우의 정답
    // ch[i]: 현재 방향에 대한 문자
    // temp: 다음 문제에 대한 정답
    ret = min(ret, ch[i] + temp);

    // 사전순 배치 => 정답을 찾은 경우 더는 볼 필요가 없다.
    break;
  }

  return dp[x][y][cnt] = ret;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
  N = n, M = m, R = r, C = c, K = k;
  dp = vector<vector<vector<string>>>(
      N + 1, vector<vector<string>>(M + 1, vector<string>(2501)));

  // (x, y)에서 K번 움직일 수 있을 때 사전순으로 가장 빠른 탈출 경로는?
  string answer = dfs(x, y, 0);

  // 도달할 수 없는 경우 "z"
  if (answer == "z")
    answer = "impossible";

  return answer;
}
