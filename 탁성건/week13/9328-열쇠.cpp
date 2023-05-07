#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Pos {
  int y;
  int x;
};

constexpr int KEY_SIZE = 'z' - 'a' + 1;

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int H, W;
char MAP[102][102];
int visited[102][102];
bool isOpen[KEY_SIZE]; // 해당 열쇠를 가지고 있는가?
vector<vector<Pos>> waiting; // 문에 도달했는데 열쇠가 없는 경우 대기할 vector

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  int T;
  cin >> T;

  while (T--) {
    memset(visited, 0, sizeof(visited));
    memset(isOpen, false, sizeof(isOpen));
    vector<vector<Pos>>(KEY_SIZE).swap(waiting);

    cin >> H >> W;

    for (int y = 1; y <= H; y++)
      for (int x = 1; x <= W; x++)
        cin >> MAP[y][x];

    H += 2;
    W += 2;

    // 빌딩 가장자리를 빈 공간으로 채우기
    for (int y = 0; y < H; y++)
      MAP[y][0] = MAP[y][W - 1] = '.';

    for (int x = 0; x < W; x++)
      MAP[0][x] = MAP[H - 1][x] = '.';

    string keys;
    cin >> keys;

    if (keys != "0")
      for (char key : keys) // 이미 가지고 있는 열쇠 갱신
        isOpen[key - 'a'] = true;

    int ans = 0;

    queue<Pos> q;
    q.push({0, 0});
    visited[0][0] = 1;

    while (!q.empty()) {
      Pos now = q.front();
      q.pop();

      if (MAP[now.y][now.x] == '$') // 문서 획득
        ans++;

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (ny < 0 || ny >= H || nx < 0 || nx >= W)
          continue;

        if (visited[ny][nx])
          continue;

        char ch = MAP[ny][nx];

        if (ch == '*')
          continue;

        // 문에 도달했는데 열쇠가 없는 경우 waiting으로 이동
        if (ch >= 'A' && ch <= 'Z' && !isOpen[ch - 'A']) {
          waiting[ch - 'A'].push_back({ny, nx});
          continue;
        }

        // 열쇠를 처음 획득한 경우
        if (ch >= 'a' && ch <= 'z' && !isOpen[ch - 'a']) {
          int key = ch - 'a';
          isOpen[key] = true;

          // 문을 열 수 있으므로 waiting에서 대기하고 있던 pos를 queue에 push
          for (Pos &pos : waiting[key])
            q.push(pos);
          vector<Pos>().swap(waiting[key]);
        }

        q.push({ny, nx});
        visited[ny][nx] = 1;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
