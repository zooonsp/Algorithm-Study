#include <iostream>
using namespace std;

constexpr int MAX_N = 400;

int N, K, S;
int graph[MAX_N + 1][MAX_N + 1];

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> N >> K;

  for (int i = 1; i <= K; i++) {
    int u, v;
    cin >> u >> v;
    graph[u][v] = 1;
  }

  for (int k = 1; k <= N; k++)
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= N; j++)
        if (graph[i][k] && graph[k][j])
          graph[i][j] = 1;

  cin >> S;

  for (int s = 1; s <= S; s++) {
    int u, v;
    cin >> u >> v;

    if (graph[u][v])
      cout << -1;
    else if (graph[v][u])
      cout << 1;
    else
      cout << 0;

    cout << '\n';
  }

  return 0;
}
