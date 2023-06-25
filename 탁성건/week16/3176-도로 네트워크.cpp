#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int MAX_N = 100000;
constexpr int MAX_H = 17;
constexpr int INF = 987654321;

struct Edge {
  int to;
  int cost;
};

int N, K;
vector<Edge> adj[MAX_N + 1];
int level[MAX_N + 1];
int parent[MAX_H][MAX_N + 1];
int minCost[MAX_H][MAX_N + 1];
int maxCost[MAX_H][MAX_N + 1];

void bfs() {
  queue<Edge> q;
  q.push({1, 0});
  level[1] = 1;
  parent[0][1] = 1;

  while (!q.empty()) {
    Edge now = q.front();
    q.pop();

    for (const Edge &next : adj[now.to]) {
      if (level[next.to])
        continue;

      q.push(next);
      level[next.to] = level[now.to] + 1;
      parent[0][next.to] = now.to;
      minCost[0][next.to] = maxCost[0][next.to] = next.cost;
    }
  }
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N;

  for (int i = 0; i < N - 1; i++) {
    int u, v, cost;
    cin >> u >> v >> cost;
    adj[u].push_back({v, cost});
    adj[v].push_back({u, cost});
  }

  bfs();

  for (int h = 1; h < MAX_H; h++) {
    for (int i = 1; i <= N; i++) {
      parent[h][i] = parent[h - 1][parent[h - 1][i]];
      minCost[h][i] = min(minCost[h - 1][i], minCost[h - 1][parent[h - 1][i]]);
      maxCost[h][i] = max(maxCost[h - 1][i], maxCost[h - 1][parent[h - 1][i]]);
    }
  }

  cin >> K;

  while (K--) {
    int u, v;
    cin >> u >> v;

    if (level[u] < level[v])
      swap(u, v);

    int diff = level[u] - level[v];
    int minAns = INF, maxAns = 0;

    for (int h = MAX_H - 1; h >= 0; h--) {
      if (diff & (1 << h)) {
        minAns = min(minAns, minCost[h][u]);
        maxAns = max(maxAns, maxCost[h][u]);
        u = parent[h][u];
      }
    }

    if (u != v) {
      for (int h = MAX_H - 1; h >= 0; h--) {
        if (parent[h][u] == parent[h][v])
          continue;
        minAns = min({minAns, minCost[h][u], minCost[h][v]});
        maxAns = max({maxAns, maxCost[h][u], maxCost[h][v]});
        u = parent[h][u];
        v = parent[h][v];
      }
      minAns = min({minAns, minCost[0][u], minCost[0][v]});
      maxAns = max({maxAns, maxCost[0][u], maxCost[0][v]});
    }

    cout << minAns << ' ' << maxAns << '\n';
  }

  return 0;
}
