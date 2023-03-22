#include <iostream>
#include <queue>
#include <vector>
#define sws ios::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

struct Node {
  int y;
  int x;
};

enum { EMPTY = 0, WALL = 1, VIRUS = 2 };

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

const int INF = 987654321;
int N, M;
int MAP[52][52];
vector<Node> virus;      // 바이러스 좌표
int selected[10];        // 활성 상태로 변경할 바이러스 번호
int ans = INF, emptyCnt; // emptyCnt: 연구소 전체 빈 칸 개수

// 바이러스 퍼뜨리기
void bfs() {
  int hour = 0, spreadCnt = 0; // spreadCnt: 바이러스를 퍼뜨린 빈 칸 개수
  int visited[52][52]{};
  queue<Node> q;

  // 활성 상태로 변경된 M개의 바이러스를 queue에 넣고 방문 체크
  for (int i = 0; i < M; i++) {
    Node v = virus[selected[i]];
    q.push(v);
    visited[v.y][v.x] = 1;
  }

  while (!q.empty()) {
    // 연구소 전체 빈 칸에 바이러스를 퍼뜨렸다면 정답 갱신 후 return
    if (spreadCnt == emptyCnt) {
      ans = ans < hour ? ans : hour;
      return;
    }

    hour++;

    if (hour >= ans) // 지금까지 찾은 정답보다 많은 시간이 걸리면 return
      return;

    int sz = q.size();

    while (sz--) {
      Node now = q.front();
      q.pop();

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (MAP[ny][nx] == WALL)
          continue;
        if (visited[ny][nx] != 0)
          continue;

        // 빈 공간이라면 바이러스를 퍼뜨린 빈 칸 개수 증가
        if (MAP[ny][nx] == EMPTY)
          spreadCnt++;

        q.push({ny, nx});
        visited[ny][nx] = 1;
      }
    }
  }
}

// 전체 바이러스 중 M개 선택 => 활성 상태로 변경
// level: 선택한 바이러스 개수, last: 이전에 선택했던 바이러스 번호
void dfs(int level, int last) {
  if (level >= M) { // M개의 바이러스를 선택했다면
    bfs();          // 바이러스 퍼뜨리기
    return;
  }

  // 이전에 선택했던 바이러스 이후부터 바이러스 선택
  for (int i = last + 1; i < virus.size(); i++) {
    selected[level] = i;
    dfs(level + 1, i);
    selected[level] = 0;
  }
}

int main(void) {
  sws;

  cin >> N >> M;

  // 연구소 주변 울타리 치기
  for (int i = 0; i <= N + 1; i++)
    MAP[0][i] = MAP[N + 1][i] = MAP[i][0] = MAP[i][N + 1] = WALL;

  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      cin >> MAP[y][x];
      if (MAP[y][x] == VIRUS) // 바이러스 좌표 저장
        virus.push_back({y, x});
      if (MAP[y][x] == EMPTY) // 연구소 전체 빈 칸 개수 count
        emptyCnt++;
    }
  }

  dfs(0, -1);

  if (ans == INF)
    ans = -1;

  cout << ans << '\n';

  return 0;
}
