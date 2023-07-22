#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

constexpr long long INF = 2e18;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N, S, E, M;
  cin >> N >> S >> E >> M;

  vector<vector<pii>> adj(N);
  vector<int> profit(N);
  vector<long long> dist(N, -INF);
  vector<int> cycleNode;

  for (int i = 0; i < M; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    adj[u].push_back({v, c});
  }

  for (int &p : profit)
    cin >> p;

  dist[S] = profit[S];

  for (int i = 0; i < N; ++i) {
    for (int now = 0; now < N; ++now) {
      for (const auto &[next, cost] : adj[now]) {
        long long ncost = dist[now] - cost + profit[next];
        if (dist[now] != -INF && dist[next] < ncost) {
          dist[next] = ncost;
          if (i == N - 1)
            cycleNode.push_back(now);
        }
      }
    }
  }

  vector<bool> visited(N);
  queue<int> q;

  for (const int &node : cycleNode) {
    visited[node] = true;
    q.push(node);
  }

  while (!q.empty()) {
    int now = q.front();
    q.pop();

    for (const auto &[next, ignore] : adj[now]) {
      if (visited[next])
        continue;
      visited[next] = true;
      q.push(next);
    }
  }

  if (dist[E] == -INF)
    cout << "gg\n";
  else if (visited[E])
    cout << "Gee\n";
  else
    cout << dist[E] << '\n';

  return 0;
}
