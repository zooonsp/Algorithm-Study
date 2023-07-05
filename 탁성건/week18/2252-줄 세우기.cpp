#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adj(N + 1);
  vector<int> income(N + 1);
  queue<int> q;

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    income[v]++;
  }

  for (int i = 1; i <= N; i++)
    if (income[i] == 0)
      q.push(i);

  while (!q.empty()) {
    int now = q.front();
    q.pop();
    cout << now << ' ';

    for (int next : adj[now]) {
      if (income[next] == 0)
        continue;
      if (--income[next] == 0)
        q.push(next);
    }
  }

  return 0;
}
