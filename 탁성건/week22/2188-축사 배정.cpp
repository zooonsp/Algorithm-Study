#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int INF = 987654321;

struct Edge {
  int to;
  int capacity;
  int flow;
  Edge *reverse;

  Edge() : Edge(-1, 0) {}
  Edge(int to, int capacity)
      : to(to), capacity(capacity), flow(0), reverse(nullptr) {}

  int residualCapacity() const { return capacity - flow; }

  void addFlow(int amt) {
    flow += amt;
    reverse->flow -= amt;
  }
};

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  vector<vector<Edge *>> adj(N + M + 2);

  for (int u = 1; u <= N; ++u) {
    int k;
    cin >> k;

    for (int i = 1; i <= k; ++i) {
      int v;
      cin >> v;

      v += N;

      Edge *uv = new Edge(v, 1);
      Edge *vu = new Edge(u, 0);

      uv->reverse = vu;
      vu->reverse = uv;

      adj[u].push_back(uv);
      adj[v].push_back(vu);
    }
  }

  int s = 0, e = N + M + 1;

  for (int u = 1; u <= N; ++u) {
    Edge *su = new Edge(u, 1);
    Edge *us = new Edge(s, 0);

    su->reverse = us;
    us->reverse = su;

    adj[s].push_back(su);
    adj[u].push_back(us);
  }

  for (int i = 1; i <= M; ++i) {
    int v = i + N;

    Edge *ve = new Edge(e, 1);
    Edge *ev = new Edge(v, 0);

    ve->reverse = ev;
    ev->reverse = ve;

    adj[v].push_back(ve);
    adj[e].push_back(ev);
  }

  int totalFlow = 0;

  while (true) {
    vector<int> prev(N + M + 2, -1);
    vector<Edge *> path(N + M + 2);
    queue<int> q;
    q.push(s);

    while (!q.empty() && prev[e] == -1) {
      int now = q.front();
      q.pop();

      for (Edge *edge : adj[now]) {
        int next = edge->to;

        if (edge->residualCapacity() > 0 && prev[next] == -1) {
          q.push(next);
          prev[next] = now;
          path[next] = edge;
          if (next == e)
            break;
        }
      }
    }

    if (prev[e] == -1)
      break;

    int flow = INF;

    for (int now = e; now != s; now = prev[now])
      flow = min(flow, path[now]->residualCapacity());
    for (int now = e; now != s; now = prev[now])
      path[now]->addFlow(flow);
    totalFlow += flow;
  }

  cout << totalFlow << '\n';

  return 0;
}
