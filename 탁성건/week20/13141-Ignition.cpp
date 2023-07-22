#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
using piii = tuple<int, int, int>;

constexpr int INF = 987654321;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cout << fixed;
  cout.precision(1);

  int N, M;
  cin >> N >> M;

  vector<piii> edges(M);
  vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));

  for (int i = 1; i <= N; ++i)
    dist[i][i] = 0;

  for (int i = 0; i < M; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    edges[i] = {u, v, c};
    dist[u][v] = dist[v][u] = min(dist[u][v], c);
  }

  for (int k = 1; k <= N; ++k)
    for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  double ans = INF;

  for (int st = 1; st <= N; ++st) {
    int maxLen = 0;

    for (const auto &[u, v, c] : edges)
      maxLen = max(maxLen, dist[st][u] + dist[st][v] + c);

    ans = min(ans, (double)maxLen / 2);
  }

  cout << ans << '\n';

  return 0;
}
