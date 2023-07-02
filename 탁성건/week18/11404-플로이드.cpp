#include <iostream>
using namespace std;

constexpr int INF = 987654321;
constexpr int MAX_N = 100;

int dist[MAX_N + 1][MAX_N + 1];

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      dist[i][j] = INF;
    dist[i][i] = 0;
  }

  for (int i = 1; i <= M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    if (dist[u][v] > c)
      dist[u][v] = c;
  }

  for (int k = 1; k <= N; k++)
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        if (dist[i][j] > dist[i][k] + dist[k][j])
          dist[i][j] = dist[i][k] + dist[k][j];

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      cout << (dist[i][j] == INF ? 0 : dist[i][j]) << ' ';
    cout << '\n';
  }

  return 0;
}
