#include <iostream>
#include <vector>
using namespace std;

constexpr long long INF = 2e18;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++) {
    int N, M, W;
    cin >> N >> M >> W;

    vector<vector<pair<int, int>>> adj(N);
    vector<long long> dist(N, INF);

    for (int i = 0; i < M; i++) {
      int u, v, cost;
      cin >> u >> v >> cost;
      adj[u - 1].push_back({v - 1, cost});
      adj[v - 1].push_back({u - 1, cost});
    }

    for (int i = 0; i < W; i++) {
      int u, v, cost;
      cin >> u >> v >> cost;
      adj[u - 1].push_back({v - 1, -cost});
    }

    bool updated = false;

    for (int i = 0; i < N; i++) {
      updated = false;

      for (int now = 0; now < N; now++) {
        for (auto [next, cost] : adj[now]) {
          if (dist[next] > dist[now] + cost) {
            dist[next] = dist[now] + cost;
            updated = true;
          }
        }
      }

      if (!updated)
        break;
    }

    cout << (updated ? "YES" : "NO") << '\n';
  }

  return 0;
}
