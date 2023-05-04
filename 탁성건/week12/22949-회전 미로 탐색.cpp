#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
  int rot;
  int y;
  int x;
};

const int MAX_SIZE = 125 * 4;

int dx[]{1, 0, -1, 0, 0}; // R, U, L, D, X
int dy[]{0, -1, 0, 1, 0};

int K;
char original[MAX_SIZE][MAX_SIZE];
char MAP[4][MAX_SIZE][MAX_SIZE];
int visited[4][MAX_SIZE][MAX_SIZE];
Node st;

void input() {
  cin >> K;

  for (int y = 0; y < K * 4; y++) {
    for (int x = 0; x < K * 4; x++) {
      cin >> original[y][x];
      if (original[y][x] == 'S')
        st = {0, y, x};
    }
  }
}

void createMap() {
  memcpy(MAP[0], original, sizeof(original));

  for (int rot = 1; rot < 4; rot++) {
    for (int sy = 0; sy < K * 4; sy += 4) {
      for (int sx = 0; sx < K * 4; sx += 4) {
        for (int y = 0; y < 4; y++) {
          for (int x = 0; x < 4; x++) {
            MAP[rot][sy + x][sx + 3 - y] = MAP[rot - 1][sy + y][sx + x];
          }
        }
      }
    }
  }
}

int bfs() {
  queue<Node> q;
  q.push(st);
  visited[st.rot][st.y][st.x] = 1;

  while (!q.empty()) {
    Node now = q.front();
    q.pop();

    for (int i = 0; i < 5; i++) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];

      if (ny < 0 || ny >= K * 4 || nx < 0 || nx >= K * 4)
        continue;

      int nrot = (now.y / 4 == ny / 4) && (now.x / 4 == nx / 4) ? now.rot : 0;

      if (MAP[nrot][ny][nx] == '#')
        continue;
      if (MAP[nrot][ny][nx] == 'E')
        return visited[now.rot][now.y][now.x];

      nrot = (nrot + 1) % 4;
      int ry = (ny - ny % 4) + (nx % 4);
      int rx = (nx - nx % 4) + (3 - ny % 4);

      if (visited[nrot][ry][rx] != 0)
        continue;

      visited[nrot][ry][rx] = visited[now.rot][now.y][now.x] + 1;
      q.push({nrot, ry, rx});
    }
  }

  return -1;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  input();
  createMap();
  cout << bfs() << '\n';
  return 0;
}
