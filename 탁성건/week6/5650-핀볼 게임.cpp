#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int y;
  int x;
  Node(int y, int x) : y(y), x(x) {}
  bool operator==(Node next) { return y == next.y && x == next.x; }
};

int dx[]{1, 0, -1, 0}; // 0: R, 1: U, 2: L, 3: D
int dy[]{0, -1, 0, 1};

int N;
int MAP[102][102];
vector<vector<Node>> wormhole; // 웜홀 번호에 해당하는 웜홀 쌍의 좌표
int ans; // 게임에서 얻을 수 있는 점수의 최대값

// [블록 번호][진행 방향] => 변화된 방향
// ex) blockDir[3][1] == 2
// 3번 블록에 1방향(U, 위)으로 만나면 2방향(L, 왼쪽)으로 변한다.
int blockDir[6][4]{{0, 0, 0, 0}, {2, 3, 1, 0}, {2, 0, 3, 1},
                   {3, 2, 0, 1}, {1, 3, 0, 2}, {2, 3, 0, 1}};

void simulation(int sy, int sx, int sdir) {
  // 출발 위치로 돌아오면 게임 끝 => 블랙홀로 만들기
  MAP[sy][sx] = -1;

  int score = 0;
  int y = sy, x = sx, dir = sdir;

  while (true) {
    // 진행 방향으로 한 칸 이동
    y += dy[dir];
    x += dx[dir];

    // 블랙홀에 빠지면 게임 끝
    if (MAP[y][x] == -1)
      break;

    int block = MAP[y][x];

    if (block >= 1 && block <= 5) { // 1~5번 블록이라면
      dir = blockDir[block][dir]; // 블록 번호와 진행 방향에 해당하는 방향 변화
      score++;                    // 점수 획득
    } else if (block >= 6 && block <= 10) { // 6~10번 웜홀이라면
      // 웜홀 번호에 해당하는 좌표 쌍 중 반대편 웜홀 좌표 찾기
      Node next = Node(y, x) == wormhole[block][0] ? wormhole[block][1]
                                                   : wormhole[block][0];

      // 반대편 웜홀로 이동
      y = next.y;
      x = next.x;
    }
  }

  // 출발 위치를 빈공간으로 복구
  MAP[sy][sx] = 0;

  ans = max(ans, score);
}

int main(void) {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    ans = 0;
    // 웜홀은 6~10의 번호를 가지므로 11의 크기로 초기화
    wormhole = vector<vector<Node>>(11);

    cin >> N;
    // 게임판 주변을 5번 블록으로 울타리 치기
    for (int i = 0; i <= N + 1; i++)
      MAP[0][i] = MAP[N + 1][i] = MAP[i][0] = MAP[i][N + 1] = 5;

    for (int y = 1; y <= N; y++) {
      for (int x = 1; x <= N; x++) {
        cin >> MAP[y][x];
        // 웜홀 번호에 해당하는 좌표 정보 저장
        if (MAP[y][x] >= 6 && MAP[y][x] <= 10)
          wormhole[MAP[y][x]].push_back({y, x});
      }
    }

    // 모든 좌표를 확인하며 빈 공간이라면 모든 방향으로 게임 진행
    for (int y = 1; y <= N; y++)
      for (int x = 1; x <= N; x++)
        if (MAP[y][x] == 0)
          for (int i = 0; i < 4; i++)
            simulation(y, x, i);

    cout << '#' << tc << ' ' << ans << '\n';
  }

  return 0;
}
