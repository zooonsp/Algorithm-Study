#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

constexpr int MAX_V = 10000;

// V: 정점 개수, E: 간선 개수, dcnt: 총 정점 방문 횟수
// dfsn[v]: v정점 방문 순서
int V, E, dcnt, dfsn[MAX_V + 1];
vector<int> adj[MAX_V + 1]; // 인접 리스트
bool finished[MAX_V + 1];   // finished[v]: v정점 방문이 끝났는가?
vector<vector<int>> scc;    // 추출된 SCC를 담을 vector
stack<int> st;              // 방문한 정점을 쌓을 stack

int dfs(int now) {
  // nowMinDfsn: 현재 정점에서 도달할 수 있는 정점들의 dfsn 최소값
  // 현재 정점 방문 순서(dfsn[now]) 갱신
  int nowMinDfsn = dfsn[now] = ++dcnt;
  st.push(now); // 현재 정점을 stack에 push

  // 현재 정점에서 갈 수 있는 모든 정점 확인
  for (const int &next : adj[now]) {
    // 아직 방문하지 않은 정점이라면 방문(dfs(next)) 및 nowMinDfsn 갱신
    if (!dfsn[next])
      nowMinDfsn = min(nowMinDfsn, dfs(next));
    // 정점 방문이 끝나지 않았다면 nowMinDfsn 갱신
    else if (!finished[next])
      nowMinDfsn = min(nowMinDfsn, dfsn[next]);
  }

  // 자신의 조상으로 갈 수 있는 경우가 하나도 없는 경우 SCC 발견
  // → stack에서 자신, 자신보다 위에 있는 정점을 하나의 SCC로 추출
  if (nowMinDfsn == dfsn[now]) {
    vector<int> nowScc;

    while (true) {
      int t = st.top();
      st.pop();
      nowScc.emplace_back(t);
      finished[t] = true; // 정점 방문 끝남
      if (t == now)
        break;
    }

    // 추출한 SCC 정렬
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

  // 모든 정점을 확인하며 방문하지 않았다면 SCC 추출
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
