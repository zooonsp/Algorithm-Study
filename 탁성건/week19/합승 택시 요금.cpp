#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

constexpr int INF = 987654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
  int ret = INF;

  vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

  for (int i = 1; i <= n; i++)
    dist[i][i] = 0;

  for (const vector<int> &fare : fares) {
    auto [u, v, c] = make_tuple(fare[0], fare[1], fare[2]);
    dist[u][v] = dist[v][u] = c;
  }

  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  for (int i = 1; i <= n; ++i)
    if (dist[s][i] != INF && dist[i][a] != INF && dist[i][b] != INF)
      ret = min(ret, dist[s][i] + dist[i][a] + dist[i][b]);

  return ret;
}
