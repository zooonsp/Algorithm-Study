#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

struct Pos {
  int y;
  int x;
};

class UnionFind {
private:
  vector<int> parent;

public:
  UnionFind(int sz) : parent(sz, -1) {}

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
  int R, C;
  cin >> R >> C;

  vector<vector<char>> MAP(R, vector<char>(C));
  vector<vector<bool>> visited(R, vector<bool>(C));
  UnionFind uf(R * C);
  queue<Pos> water, melt;
  int st = -1, de = -1, hour = 0;

  for (int y = 0; y < R; y++) {
    for (int x = 0; x < C; x++) {
      cin >> MAP[y][x];
      if (MAP[y][x] == 'L') {
        st == -1 ? (st = y * C + x) : (de = y * C + x);
        MAP[y][x] = '.';
      }
    }
  }

  for (int sy = 0; sy < R; sy++) {
    for (int sx = 0; sx < C; sx++) {
      if (MAP[sy][sx] == '.' && !visited[sy][sx]) {
        water.push({sy, sx});
        visited[sy][sx] = 1;

        while (!water.empty()) {
          Pos now = water.front();
          water.pop();

          for (int i = 0; i < 4; i++) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (ny < 0 || ny >= R || nx < 0 || nx >= C)
              continue;
            if (visited[ny][nx])
              continue;

            if (MAP[ny][nx] == 'X')
              melt.push({ny, nx});
            else if (MAP[ny][nx] == '.') {
              water.push({ny, nx});
              uf.Union(now.y * C + now.x, ny * C + nx);
            }

            visited[ny][nx] = 1;
          }
        }
      }
    }
  }

  while (uf.Find(st) != uf.Find(de)) {
    int sz = melt.size();
    while (sz--) {
      Pos now = melt.front();
      melt.pop();
      MAP[now.y][now.x] = '.';

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (ny < 0 || ny >= R || nx < 0 || nx >= C)
          continue;

        if (MAP[ny][nx] == 'X' && !visited[ny][nx])
          melt.push({ny, nx});
        else if (MAP[ny][nx] == '.')
          uf.Union(now.y * C + now.x, ny * C + nx);

        visited[ny][nx] = 1;
      }
    }

    hour++;
  }

  cout << hour << '\n';

  return 0;
}
