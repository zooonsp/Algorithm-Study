#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_V = 10000;

int V, E, dcnt, dfsn[MAX_V + 1];
vector<int> adj[MAX_V + 1];
bool ap[MAX_V + 1];

int dfs(int now, int prev, bool root) {
  int nowMinDfsn = dfsn[now] = ++dcnt;
  int childCnt = 0;

  for (int next : adj[now]) {
    if (next == prev)
      continue;

    if (dfsn[next] > 0)
      nowMinDfsn = min(nowMinDfsn, dfsn[next]);
    else {
      childCnt++;
      int nextMinDfsn = dfs(next, now, false);
      nowMinDfsn = min(nowMinDfsn, nextMinDfsn);
      if (!root && nextMinDfsn >= dfsn[now])
        ap[now] = true;
    }
  }

  if (root && childCnt >= 2)
    ap[now] = true;

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
      dfs(i, -1, true);

  int apCnt = 0;

  for (int i = 1; i <= V; i++)
    if (ap[i])
      apCnt++;

  cout << apCnt << '\n';

  for (int i = 1; i <= V; i++)
    if (ap[i])
      cout << i << ' ';

  return 0;
}
