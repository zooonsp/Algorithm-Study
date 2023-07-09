#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

constexpr int MAX_V = 10000;

int V, E, dcnt, dfsn[MAX_V + 1];
vector<int> adj[MAX_V + 1];
bool finished[MAX_V + 1];
vector<vector<int>> scc;
stack<int> st;

int dfs(int now) {
  int nowMinDfsn = dfsn[now] = ++dcnt;
  st.push(now);

  for (const int &next : adj[now]) {
    if (!dfsn[next])
      nowMinDfsn = min(nowMinDfsn, dfs(next));
    else if (!finished[next])
      nowMinDfsn = min(nowMinDfsn, dfsn[next]);
  }

  if (nowMinDfsn == dfsn[now]) {
    vector<int> nowScc;

    while (true) {
      int t = st.top();
      st.pop();
      nowScc.emplace_back(t);
      finished[t] = true;
      if (t == now)
        break;
    }

    sort(nowScc.begin(), nowScc.end());
    scc.emplace_back(nowScc);
  }

  return nowMinDfsn;
}

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> V >> E;

  for (int i = 1; i <= E; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].emplace_back(v);
  }

  for (int i = 1; i <= V; ++i)
    if (!dfsn[i])
      dfs(i);

  sort(scc.begin(), scc.end());

  cout << scc.size() << '\n';

  for (const vector<int> &nowScc : scc) {
    for (const int &now : nowScc)
      cout << now << ' ';
    cout << "-1\n";
  }

  return 0;
}
