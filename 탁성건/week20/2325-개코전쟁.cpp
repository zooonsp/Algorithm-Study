#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using pii = pair<int, int>;

constexpr int INF = 21e8;

struct Edge {
  int to;
  int cost;
  bool operator<(const Edge &next) const { return cost > next.cost; }
};

int N, M;
vector<vector<Edge>> adj;
vector<int> dist;
vector<int> path;
vector<pii> pathEdges;

void findPathEdges() {
  dist.assign(N + 1, INF);
  priority_queue<Edge> pq;
  path.assign(N + 1, 0);

  dist[1] = 0;
  pq.push({1, 0});

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (dist[now.to] < now.cost)
      continue;

    for (const Edge &next : adj[now.to]) {
      int ncost = dist[now.to] + next.cost;

      if (dist[next.to] <= ncost)
        continue;

      dist[next.to] = ncost;
      pq.push({next.to, ncost});
      path[next.to] = now.to;
    }
  }

  int now = N;

  while (path[now]) {
    pathEdges.push_back({now, path[now]});
    now = path[now];
  }
}

int destroyEdge(int u, int v) {
  dist.assign(N + 1, INF);
  priority_queue<Edge> pq;

  dist[1] = 0;
  pq.push({1, 0});

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (dist[now.to] < now.cost)
      continue;

    for (const Edge &next : adj[now.to]) {
      int ncost = dist[now.to] + next.cost;

      if (dist[next.to] <= ncost)
        continue;

      if ((u == now.to && v == next.to) || (u == next.to && v == now.to))
        continue;

      dist[next.to] = ncost;
      pq.push({next.to, ncost});
    }
  }

  return dist[N];
}

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> N >> M;

  adj.assign(N + 1, {});

  for (int i = 0; i < M; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    adj[u].push_back({v, c});
    adj[v].push_back({u, c});
  }

  findPathEdges();

  int ans = 0;

  for (const auto &[u, v] : pathEdges)
    ans = max(ans, destroyEdge(u, v));

  cout << ans << '\n';

  return 0;
}
