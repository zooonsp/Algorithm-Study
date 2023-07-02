#include <iostream>
#include <vector>
using namespace std;

constexpr long long INF = 2e18;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, int>>> adj(N);
  vector<long long> dist(N, INF);

  for (int i = 0; i < M; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    adj[from - 1].push_back({to - 1, cost});
  }

  dist[0] = 0;
  bool updated = false;

  for (int i = 0; i < N; i++) {
    updated = false;

    for (int now = 0; now < N; now++) {
      for (auto [next, cost] : adj[now]) {
        if (dist[now] != INF && dist[next] > dist[now] + cost) {
          dist[next] = dist[now] + cost;
          updated = true;
        }
      }
    }

    if (!updated)
      break;
  }

  if (updated)
    cout << "-1\n";
  else
    for (int i = 1; i < N; i++)
      cout << (dist[i] == INF ? -1 : dist[i]) << '\n';

  return 0;
}
