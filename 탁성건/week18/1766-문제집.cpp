#include <functional>
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
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    income[v]++;
  }

  for (int i = 1; i <= N; i++)
    if (income[i] == 0)
      pq.push(i);

  while (!pq.empty()) {
    int now = pq.top();
    pq.pop();
    cout << now << ' ';

    for (int next : adj[now]) {
      if (income[next] == 0)
        continue;
      if (--income[next] == 0)
        pq.push(next);
    }
  }

  return 0;
}
