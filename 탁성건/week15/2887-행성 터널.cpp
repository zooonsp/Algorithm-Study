#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Planet {
  int pos, id;
  bool operator<(const Planet &next) { return pos < next.pos; }
};

struct Edge {
  int a, b, cost;
  bool operator<(const Edge &next) { return cost < next.cost; }
};

class UnionFind {
private:
  vector<int> parent;

public:
  UnionFind(int sz) : parent(vector<int>(sz, -1)) {}

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
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  int N;
  cin >> N;

  vector<Planet> planetX(N), planetY(N), planetZ(N);
  vector<Edge> edge;

  for (int i = 0; i < N; i++) {
    cin >> planetX[i].pos >> planetY[i].pos >> planetZ[i].pos;
    planetX[i].id = planetY[i].id = planetZ[i].id = i;
  }

  sort(planetX.begin(), planetX.end());
  sort(planetY.begin(), planetY.end());
  sort(planetZ.begin(), planetZ.end());

  for (int i = 0; i < N - 1; i++) {
    edge.push_back({planetX[i].id, planetX[i + 1].id,
                    planetX[i + 1].pos - planetX[i].pos});
    edge.push_back({planetY[i].id, planetY[i + 1].id,
                    planetY[i + 1].pos - planetY[i].pos});
    edge.push_back({planetZ[i].id, planetZ[i + 1].id,
                    planetZ[i + 1].pos - planetZ[i].pos});
  }

  sort(edge.begin(), edge.end());
  UnionFind uf(N);
  int sum = 0;

  for (const Edge &e : edge) {
    if (uf.Find(e.a) == uf.Find(e.b))
      continue;

    sum += e.cost;
    uf.Union(e.a, e.b);
  }

  cout << sum << '\n';

  return 0;
}
