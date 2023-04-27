#include <iostream>
#include <queue>
using namespace std;

enum { AIR = 0, CHEEZE = 1 };

struct Node {
  int y;
  int x;
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int N, M, cnt;
int MAP[100][100];
bool visited[100][100];

void simulation() {
  queue<Node> air;
  queue<Node> melt;
  visited[0][0] = true;
  air.push({0, 0});

  int hour = 0, prevCnt = cnt;

  while (true) {
    while (!air.empty()) {
      Node now = air.front();
      air.pop();

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (ny < 0 || ny >= N || nx < 0 || nx >= M)
          continue;
        if (visited[ny][nx] == true)
          continue;

        visited[ny][nx] = true;
        MAP[ny][nx] == AIR ? air.push({ny, nx}) : melt.push({ny, nx});
      }
    }

    if (melt.empty())
      break;

    prevCnt = cnt;

    while (!melt.empty()) {
      Node now = melt.front();
      melt.pop();
      MAP[now.y][now.x] = AIR;
      air.push(now);
      cnt--;
    }

    hour++;
  }

  cout << hour << '\n' << prevCnt << '\n';
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> N >> M;

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < M; x++) {
      cin >> MAP[y][x];
      cnt += MAP[y][x];
    }
  }

  simulation();

  return 0;
}
