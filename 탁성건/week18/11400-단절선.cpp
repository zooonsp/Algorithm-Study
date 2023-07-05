#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_V = 100000;
using pii = pair<int, int>;

int V, E, dcnt, dfsn[MAX_V + 1];
vector<int> adj[MAX_V + 1];
vector<pii> ac;

int dfs(int now, int prev) {
  int nowMinDfsn = dfsn[now] = ++dcnt;

  for (int next : adj[now]) {
    if (next == prev)
      continue;

    if (dfsn[next] > 0)
      nowMinDfsn = min(nowMinDfsn, dfsn[next]);
    else {
      int nextMinDfsn = dfs(next, now);
      nowMinDfsn = min(nowMinDfsn, nextMinDfsn);
      if (nextMinDfsn > dfsn[now])
        ac.push_back(now < next ? pii(now, next) : pii(next, now));
    }
  }

  return nowMinDfsn;
}

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> V >> E;

  for (int i = 1; i <= E; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= V; i++)
    if (!dfsn[i])
      dfs(i, -1);

  sort(ac.begin(), ac.end());

  cout << ac.size() << '\n';

  for (auto [u, v] : ac)
    cout << u << ' ' << v << '\n';

  return 0;
}
