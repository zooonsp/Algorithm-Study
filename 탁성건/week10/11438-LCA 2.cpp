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
int parent[17][MAX_N + 1];
int level[MAX_N + 1];
int maxLevel;

void bfs() {
  queue<int> q;
  q.push(1);
  parent[0][1] = 1;
  level[1] = 0;

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

  bfs();

  H = ceil(log2(maxLevel));

  for (int h = 1; h < H; h++)
    for (int i = 1; i < N + 1; i++)
      parent[h][i] = parent[h - 1][parent[h - 1][i]];

  cin >> M;

  while (M--) {
    int u, v;
    cin >> u >> v;

    if (level[u] < level[v])
      swap(u, v);

    int diff = level[u] - level[v];

    if (diff > 0)
      for (int i = H - 1; i >= 0; i--)
        if (diff & (1 << i))
          u = parent[i][u];

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
