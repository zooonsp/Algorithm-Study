#include <cstring>
#include <iostream>
#include <queue>
#define sws ios::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

struct Node {
  int y;
  int x;
  int vitality;
  int time;
  bool operator<(Node next) const {
    if (time < next.time)
      return false;
    if (time > next.time)
      return true;
    if (vitality > next.vitality)
      return false;
    if (vitality < next.vitality)
      return true;
    return false;
  }
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

const int SIZE = 500;
int N, M, K;
int MAP[SIZE][SIZE];
int cnt;
priority_queue<Node> pq;

void simulation() {
  for (int k = 1; k <= K; k++) {
    while (true) {
      if (pq.empty())
        break;
      if (pq.top().time > k)
        break;

      Node now = pq.top();
      pq.pop();

      if (k + now.vitality - 1 > K)
        cnt++;

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (MAP[ny][nx] != 0)
          continue;

        pq.push({ny, nx, now.vitality, now.vitality + k + 1});
        MAP[ny][nx] = now.vitality;
      }
    }
  }
}

int main(void) {
  sws;
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    memset(MAP, 0, sizeof(MAP));
    cnt = 0;
    pq = priority_queue<Node>();

    cin >> N >> M >> K;
    int yOff = (SIZE - N) / 2;
    int xOff = (SIZE - M) / 2;

    for (int y = 0; y < N; y++) {
      for (int x = 0; x < M; x++) {
        int ny = y + yOff;
        int nx = x + xOff;

        cin >> MAP[ny][nx];
        if (MAP[ny][nx] != 0)
          pq.push({ny, nx, MAP[ny][nx], MAP[ny][nx] + 1});
      }
    }

    simulation();

    cout << '#' << tc << ' ' << pq.size() + cnt << '\n';
  }

  return 0;
}
