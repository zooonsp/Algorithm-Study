// https://rebro.kr/153
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int a, b, temp;
  bool operator<(const Edge &next) const { return temp < next.temp; }
};

struct Query {
  int x, y;
};

struct Answer {
  int minTemp, cnt;
};

int N, M, Q;
vector<int> parent;

int Find(int x) {
  if (parent[x] < 0)
    return x;
  return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
  int pa = Find(a);
  int pb = Find(b);
  if (pa == pb)
    return;
  parent[pa] += parent[pb];
  parent[pb] = pa;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N >> M;
  vector<Edge> edges(M);
  for (Edge &edge : edges)
    cin >> edge.a >> edge.b >> edge.temp;

  cin >> Q;
  vector<Query> quries(Q);
  for (Query &query : quries)
    cin >> query.x >> query.y;

  sort(edges.begin(), edges.end());
  vector<int> l(Q), r(Q, M - 1);
  vector<Answer> ans(Q);

  while (true) {
    vector<vector<int>> mid(M);
    bool flag = false;

    for (int q = 0; q < Q; q++) {
      if (l[q] <= r[q]) {
        int m = l[q] + (r[q] - l[q]) / 2;
        mid[m].push_back(q);
        flag = true;
      }
    }

    if (!flag)
      break;
    parent.assign(N + 1, -1);

    for (int m = 0; m < M; m++) {
      Edge now = edges[m];
      Union(now.a, now.b);

      for (int q : mid[m]) {
        if (Find(quries[q].x) == Find(quries[q].y)) {
          ans[q] = {edges[m].temp, -parent[Find(quries[q].x)]};
          r[q] = m - 1;
        } else
          l[q] = m + 1;
      }
    }
  }

  for (int q = 0; q < Q; q++) {
    if (l[q] >= M)
      cout << "-1\n";
    else
      cout << ans[q].minTemp << ' ' << ans[q].cnt << '\n';
  }

  return 0;
}
