#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int INF = 987654321;
constexpr int MAX_V = 52;

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

int alphabet2idx(char ch) {
  if (ch >= 'A' && ch <= 'Z')
    return ch - 'A';
  return ch - 'a' + 26;
}

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<Edge *> adj[MAX_V];

  for (int i = 0; i < N; ++i) {
    char u, v;
    int c;
    cin >> u >> v >> c;

    u = alphabet2idx(u);
    v = alphabet2idx(v);

    Edge *uv = new Edge(v, c);
    Edge *vu = new Edge(u, c);

    uv->reverse = vu;
    vu->reverse = uv;

    adj[u].push_back(uv);
    adj[v].push_back(vu);
  }

  int totalFlow = 0;
  int S = alphabet2idx('A'), E = alphabet2idx('Z');

  while (true) {
    vector<int> prev(MAX_V, -1);
    vector<Edge *> path(MAX_V);
    queue<int> q;
    q.push(S);

    while (!q.empty() && prev[E] == -1) {
      int now = q.front();
      q.pop();

      for (Edge *edge : adj[now]) {
        int next = edge->to;

        if (edge->residualCapacity() > 0 && prev[next] == -1) {
          q.push(next);
          prev[next] = now;
          path[next] = edge;
          if (next == E)
            break;
        }
      }
    }

    if (prev[E] == -1)
      break;

    int flow = INF;

    for (int now = E; now != S; now = prev[now])
      flow = min(flow, path[now]->residualCapacity());
    for (int now = E; now != S; now = prev[now])
      path[now]->addFlow(flow);
    totalFlow += flow;
  }

  cout << totalFlow << '\n';

  return 0;
}
