#include <cstring>
#include <iostream>
#include <queue>
#define sws ios::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

// 줄기 세포의 정보를 담을 구조체
// PQ에서 작은 시간 우선, 높은 생명력 우선
struct Node {
  int y;
  int x;
  int vitality; // 생명력
  int time;     // 번식하는 시간
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
int cnt; // K시간 이후에 살아있는 번식을 마친 줄기 세포 수
priority_queue<Node> pq;

void simulation() {
  for (int k = 1; k <= K; k++) { // 1시간 ~ K시간
    while (true) {
      if (pq.empty()) // 줄기 세포가 없으면 break
        break;
      if (pq.top().time > k) // 현재 시간에 번식하는 줄기 세포가 없으면 break
        break;

      Node now = pq.top(); // 지금 번식하는 줄기 세포
      pq.pop();

      // 현재 줄기 세포가 K시간 이후에 살아있다면 cnt 증가
      if (k + now.vitality - 1 > K)
        cnt++;

      // 번식
      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (MAP[ny][nx] != 0) // 이미 줄기 세포가 존재하는 경우 번식 X
          continue;

        // 다음 줄기 세포가 번식하는 시간은 현재 시간(k) + 생명력 + 1
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
    // 초기 상태 크기에 맞게 MAP 중앙에 위치시킬 수 있는 Offset 계산
    int yOff = (SIZE - N) / 2;
    int xOff = (SIZE - M) / 2;

    for (int y = 0; y < N; y++) {
      for (int x = 0; x < M; x++) {
        int ny = y + yOff;
        int nx = x + xOff;

        cin >> MAP[ny][nx]; // MAP 중앙에 초기 상태 입력
        if (MAP[ny][nx] != 0)
          // 줄기 세포라면 PQ에 push
          // 번식하는 시간은 생명력 + 1
          pq.push({ny, nx, MAP[ny][nx], MAP[ny][nx] + 1});
      }
    }

    simulation();

    // PQ에 남아있는 줄기 세포 수 + K시간 이후 살아있는 번식을 마친 줄기 세포 수
    cout << '#' << tc << ' ' << pq.size() + cnt << '\n';
  }

  return 0;
}
