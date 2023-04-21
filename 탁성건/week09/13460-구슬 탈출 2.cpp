#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Marble {
  int ry;
  int rx;
  int by;
  int bx;
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int N, M;
char MAP[10][10];
int visited[10][10][10][10]; // ry, rx, by, bx
Marble st;

int bfs() {
  queue<Marble> q;
  q.push(st);
  memset(visited, -1, sizeof(visited));
  visited[st.ry][st.rx][st.by][st.bx] = 0;

  while (!q.empty()) {
    Marble now = q.front();
    q.pop();

    int dist = visited[now.ry][now.rx][now.by][now.bx];

    if (dist >= 10)
      continue;

    for (int dir = 0; dir < 4; dir++) {
      int nry = now.ry, nrx = now.rx;
      int nby = now.by, nbx = now.bx;

      if ((now.ry * dy[dir] + now.rx * dx[dir]) >=
          (now.by * dy[dir] + now.bx * dx[dir])) {
        while (MAP[nry + dy[dir]][nrx + dx[dir]] != '#' &&
               MAP[nry][nrx] != 'O') {
          nry += dy[dir];
          nrx += dx[dir];
        }

        if (MAP[nry][nrx] != 'O')
          MAP[nry][nrx] = '#';

        while (MAP[nby + dy[dir]][nbx + dx[dir]] != '#' &&
               MAP[nby][nbx] != 'O') {
          nby += dy[dir];
          nbx += dx[dir];
        }

        if (MAP[nry][nrx] == '#')
          MAP[nry][nrx] = '.';
      } else {
        while (MAP[nby + dy[dir]][nbx + dx[dir]] != '#' &&
               MAP[nby][nbx] != 'O') {
          nby += dy[dir];
          nbx += dx[dir];
        }

        if (MAP[nby][nbx] != 'O')
          MAP[nby][nbx] = '#';

        while (MAP[nry + dy[dir]][nrx + dx[dir]] != '#' &&
               MAP[nry][nrx] != 'O') {
          nry += dy[dir];
          nrx += dx[dir];
        }

        if (MAP[nby][nbx] == '#')
          MAP[nby][nbx] = '.';
      }

      if (MAP[nby][nbx] == 'O')
        continue;

      if (MAP[nry][nrx] == 'O')
        return dist + 1;

      if (visited[nry][nrx][nby][nbx] != -1)
        continue;

      visited[nry][nrx][nby][nbx] = dist + 1;
      q.push({nry, nrx, nby, nbx});
    }
  }

  return -1;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N >> M;

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < M; x++) {
      cin >> MAP[y][x];
      if (MAP[y][x] == 'R') {
        st.ry = y;
        st.rx = x;
        MAP[y][x] = '.';
      } else if (MAP[y][x] == 'B') {
        st.by = y;
        st.bx = x;
        MAP[y][x] = '.';
      }
    }
  }

  cout << bfs() << '\n';

  return 0;
}
