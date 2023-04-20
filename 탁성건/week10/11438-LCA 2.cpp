#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_N = 100000;

int N, M, H;
vector<vector<int>> adj;
// parent[i][nodeId]: nodeId의 2^i번째 위에 있는 부모(sparse table)
int parent[17][MAX_N + 1];
// level[nodeId]: nodeId의 level
int level[MAX_N + 1];
int maxLevel;

// parent[0], level, maxLevel 계산
void bfs() {
  queue<int> q;
  q.push(1);
  parent[0][1] = 1; // root의 부모는 자기 자신
  level[1] = 0;     // root의 level은 0

  while (!q.empty()) {
    int now = q.front();
    q.pop();

    for (int next : adj[now]) {
      if (level[next] != -1)
        continue;

      q.push(next);
      parent[0][next] = now;
      level[next] = level[now] + 1;

      maxLevel = maxLevel > level[next] ? maxLevel : level[next];
    }
  }
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> N;

  adj = vector<vector<int>>(N + 1);
  memset(level, -1, sizeof(level));

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // parent[0], level, maxLevel 계산
  bfs();

  H = ceil(log2(maxLevel)); // H: sparse table의 높이

  // sparse table 계산
  for (int h = 1; h < H; h++)
    for (int i = 1; i < N + 1; i++)
      parent[h][i] = parent[h - 1][parent[h - 1][i]];

  cin >> M;

  while (M--) {
    int u, v;
    cin >> u >> v;

    // u의 level이 무조건 크도록 변경
    if (level[u] < level[v])
      swap(u, v);

    int diff = level[u] - level[v];

    // u와 v의 level 맞추기
    if (diff > 0)
      for (int i = H - 1; i >= 0; i--)
        if (diff & (1 << i))
          u = parent[i][u];

    // 공통 조상 찾기
    if (u != v) {
      for (int i = H - 1; i >= 0; i--) {
        if (parent[i][u] != parent[i][v]) {
          u = parent[i][u];
          v = parent[i][v];
        }
      }
      u = v = parent[0][u];
    }

    cout << u << '\n';
  }

  return 0;
}
