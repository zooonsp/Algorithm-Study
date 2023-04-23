#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int a;
  int b;
  int temp;
  bool operator<(const Edge &next) const { return temp < next.temp; }
};

const int INF = 987654321;
int N, M, Q;
vector<Edge> v;
vector<int> parent;

int Find(int x) {
  if (parent[x] == -1)
    return x;
  return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
  int pa = Find(a);
  int pb = Find(b);
  if (pa == pb)
    return;
  parent[pb] = pa;
}

int connectEdges(int temp) {
  parent.assign(N + 1, -1);
  int cnt = 0;

  for (const Edge &now : v) {
    if (Find(now.a) == Find(now.b))
      continue;
    if (now.temp > temp)
      break;

    Union(now.a, now.b);
    cnt++;
  }

  return cnt;
}

void pSearch(int st, int de) {
  int left = 0;
  int right = v[v.size() - 1].temp;
  int minTemp = INF, edgeCnt = 0;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    int cnt = connectEdges(mid);

    if (Find(st) == Find(de)) {
      right = mid - 1;
      minTemp = mid;
      edgeCnt = cnt;
    } else {
      left = mid + 1;
    }
  }

  if (minTemp == INF) {
    cout << "-1\n";
    return;
  }

  cout << minTemp << ' ' << edgeCnt + 1 << '\n';
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> N >> M;

  v.assign(M, {});

  for (Edge &e : v)
    cin >> e.a >> e.b >> e.temp;

  sort(v.begin(), v.end());

  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int x, y;
    cin >> x >> y;
    pSearch(x, y);
  }

  return 0;
}
