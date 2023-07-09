#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

constexpr int INF = 987654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
  int ret = INF;

  vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

  for (int i = 1; i <= n; ++i)
    dist[i][i] = 0;

  // 간선 정보 적용
  for (const vector<int> &fare : fares) {
    auto [u, v, c] = make_tuple(fare[0], fare[1], fare[2]);
    dist[u][v] = dist[v][u] = c;
  }

  // 플로이드 와샬
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  // 모든 정점 i에 대해 확인
  // 정점 s부터 정점 i까지는 A, B가 합승하여 택시 이용
  // 정점 i부터는 A, B 각자 택시 이용
  for (int i = 1; i <= n; ++i)
    if (dist[s][i] != INF && dist[i][a] != INF && dist[i][b] != INF)
      ret = min(ret, dist[s][i] + dist[i][a] + dist[i][b]);

  return ret;
}
