#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int y;
  int x;
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int N;
int MAP[14][14]; // 멕시노스(빈 공간: 0, 코어: 1, 전선: 2, 가장자리: -1)
vector<Node> v; // Core의 위치를 저장할 vector
// max_core: 전원을 연결할 수 있는 Core 개수의 최대값
// min_wire: 최대한 많은 Core에 전원을 연결했을 경우 전선 길이 합의 최소값
int max_core, min_wire;

// v에 있는 Core들을 하나씩 보면서 상하좌우 연결 or 연결 X 선택
// level: 현재 Core의 index
// core: 전원이 연결된 Core 개수
// wire: 전선 길이 합
void dfs(int level, int core, int wire) {
  // 모든 Core에 대해서 선택을 완료했을 경우 정답 갱신
  if (level >= v.size()) {
    if (max_core < core) {
      max_core = core;
      min_wire = wire;
    } else if (max_core == core) {
      min_wire = min_wire < wire ? min_wire : wire;
    }
    return;
  }

  // 현재 Core의 전원을 연결하지 않고 다음 Core로 넘어감
  dfs(level + 1, core, wire);

  // 현재 Core
  Node now = v[level];

  // 상하좌우 4방향으로 연결해보기
  for (int i = 0; i < 4; i++) {
    int ny = now.y + dy[i];
    int nx = now.x + dx[i];
    int cnt = 0; // 현재 Core를 연결하는데 필요한 전선의 길이

    // 현재 방향으로 전선을 연결하면서 갈 수 있는 만큼 이동(빈 공간일 경우 이동)
    // 코어, 전선, 가장자리를 만나는 경우 stop
    while (MAP[ny][nx] == 0) {
      MAP[ny][nx] = 2;
      ny += dy[i];
      nx += dx[i];
      cnt++;
    }

    // 만약 전선이 가장자리를 만나 현재 Core에 전원을 연결할 수 있다면
    // 전원이 연결된 Core의 개수 증가
    // 현재 Core를 연결하는데 필요한 전선의 길이 더하기
    // 다음 Core로 넘어감
    if (MAP[ny][nx] == -1)
      dfs(level + 1, core + 1, wire + cnt);

    ny = now.y + dy[i];
    nx = now.x + dx[i];

    // 현재 Core에 연결했던 전선 제거
    for (int j = 0; j < cnt; j++) {
      MAP[ny][nx] = 0;
      ny += dy[i];
      nx += dx[i];
    }
  }
}

int main(void) {
  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++) {
    cout << '#' << tc << ' ';

    v = vector<Node>();
    max_core = 0, min_wire = 0;
    memset(MAP, -1, sizeof(MAP)); // 멕시노스 주변에 -1로 울타리 치기

    cin >> N;

    for (int y = 1; y <= N; y++) {
      for (int x = 1; x <= N; x++) {
        cin >> MAP[y][x];
        // v에 Core 위치 저장
        // 가장자리에 위치한 Core는 이미 전원이 연결된 상태이므로 skip
        if (MAP[y][x] == 1 && y != 1 && y != N && x != 1 && x != N)
          v.push_back({y, x});
      }
    }

    dfs(0, 0, 0);

    cout << min_wire << '\n';
  }

  return 0;
}
