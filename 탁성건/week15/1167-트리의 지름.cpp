#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
  int to;
  int cost;
};

int V;
vector<vector<Edge>> adj;
vector<int> visited;

void bfs(int src) {
  vector<int>(V + 1).swap(visited);
  queue<int> q;

  visited[src] = 1;
  q.push(src);

  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (const Edge &next : adj[now]) {
      if (visited[next.to] != 0)
        continue;
      visited[next.to] = visited[now] + next.cost;
      q.push(next.to);
    }
  }
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> V;

  vector<vector<Edge>>(V + 1).swap(adj);

  for (int i = 0; i < V; i++) {
    int from, to, cost;
    cin >> from;
    while (true) {
      cin >> to;
      if (to == -1)
        break;
      cin >> cost;
      adj[from].push_back({to, cost});
    }
  }

  int src = 1, ans = 0;

  bfs(src);
  for (int i = 1; i <= V; i++)
    if (visited[src] < visited[i])
      src = i;

  bfs(src);
  for (int i = 1; i <= V; i++)
    if (ans < visited[i])
      ans = visited[i];

  ans--;

  cout << ans << '\n';

  return 0;
}
