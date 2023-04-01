#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 좌표 정보를 담은 구조체
// 정렬 시 작은 행 번호 우선, 작은 열 번호 우선
struct Node {
  int y;
  int x;
  bool operator<(Node next) const {
    if (y < next.y)
      return true;
    if (y > next.y)
      return false;
    if (x < next.x)
      return true;
    if (x > next.x)
      return false;
    return false;
  }
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int N, M, fuel;
int MAP[22][22];         // -1: 벽, 0: 빈 공간, 1이상: 손님
vector<Node> clientDest; // clientDest[n]: n번 손님의 목적지 좌표
Node taxi;

bool simulation() {
  vector<Node> clients; // 가장 가까운 손님의 좌표를 담을 vector
  int visited[22][22]{};
  queue<Node> q;

  visited[taxi.y][taxi.x] = 1; // taxi의 위치에서 시작
  q.push(taxi);

  while (!q.empty()) {
    int sz = q.size();

    while (sz--) { // 단계별 Flood Fill
      Node now = q.front();
      q.pop();

      if (MAP[now.y][now.x] > 0) // 손님인 경우 clients에 push
        clients.push_back(now);

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (MAP[ny][nx] == -1)
          continue;
        if (visited[ny][nx] != 0)
          continue;

        visited[ny][nx] = visited[now.y][now.x] + 1;
        q.push({ny, nx});
      }
    }

    if (!clients.empty()) // 손님이 있다면 break
      break;
  }

  if (clients.empty()) // 갈 수 있는 곳을 다 확인했는데 손님이 없으면 false
    return false;

  // 정렬(작은 행 번호 우선, 작은 열 번호 우선)
  sort(clients.begin(), clients.end());

  taxi = clients[0];                      // taxi가 손님의 위치로 이동
  int clientId = MAP[taxi.y][taxi.x];     // 손님의 ID
  int dist = visited[taxi.y][taxi.x] - 1; // 손님까지의 최단 거리
  Node ndest = clientDest[clientId];      // 현재 손님의 목적지 좌표

  if (fuel < dist) // 손님의 위치까지 가는데 연료가 부족한 경우 false
    return false;

  fuel -= dist;            // 연료 소모
  MAP[taxi.y][taxi.x] = 0; // 손님을 태웠으므로 빈 공간으로 만들기

  // 초기화
  memset(visited, 0, sizeof(visited));
  q = queue<Node>();

  visited[taxi.y][taxi.x] = 1; // taxi의 위치에서 시작
  q.push(taxi);

  while (!q.empty()) {
    Node now = q.front();
    q.pop();

    if (now.y == ndest.y && now.x == ndest.x) // 목적지에 도달하면 break
      break;

    for (int i = 0; i < 4; i++) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];

      if (MAP[ny][nx] == -1)
        continue;
      if (visited[ny][nx] != 0)
        continue;

      visited[ny][nx] = visited[now.y][now.x] + 1;
      q.push({ny, nx});
    }
  }

  dist = visited[ndest.y][ndest.x] - 1; // 목적지까지의 최단 거리

  // 연료가 부족하거나 목적지까지 갈 수 없는 경우 false
  if (fuel < dist || dist == -1)
    return false;

  taxi = ndest; // taxi가 목적지까지 이동
  fuel += dist; // 연료 충전

  return true;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N >> M >> fuel;

  clientDest = vector<Node>(M + 1); // 손님은 M명

  for (int i = 0; i <= N + 1; i++) // MAP 주변 울타리 치기(-1: 벽)
    MAP[i][0] = MAP[i][N + 1] = MAP[0][i] = MAP[N + 1][i] = -1;

  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      cin >> MAP[y][x];
      if (MAP[y][x]) // 입력이 1인 경우 -1로 변경
        MAP[y][x] = -1;
    }
  }

  cin >> taxi.y >> taxi.x;

  for (int i = 1; i <= M; i++) {
    // 손님의 시작 위치는 MAP에 표시
    // 손님의 목적지 좌표는 clientDest에 저장
    Node st;
    cin >> st.y >> st.x >> clientDest[i].y >> clientDest[i].x;
    MAP[st.y][st.x] = i;
  }

  for (int i = 0; i < M; i++) { // M명의 손님 태우기
    if (!simulation()) {        // 이동할 수 없는 경우
      fuel = -1;                // 정답은 -1
      break;
    }
  }

  cout << fuel << '\n';

  return 0;
}
