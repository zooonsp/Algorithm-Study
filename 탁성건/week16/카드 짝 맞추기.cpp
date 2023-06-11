#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Pos {
  int y;
  int x;
};

constexpr int INF = 987654321;

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int MAP[4][4];
vector<vector<Pos>> cardPos;
vector<bool> cardExist;
int maxCardType, ans;

int bfs(Pos st, Pos de) {
  queue<Pos> q;
  int visited[4][4]{};

  q.push(st);
  visited[st.y][st.x] = 1;

  while (!q.empty()) {
    Pos now = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];

      if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4)
        continue;
      if (visited[ny][nx])
        continue;

      q.push({ny, nx});
      visited[ny][nx] = visited[now.y][now.x] + 1;
    }

    for (int i = 0; i < 4; i++) {
      int ny = now.y;
      int nx = now.x;

      while (true) {
        ny += dy[i];
        nx += dx[i];

        if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) {
          ny -= dy[i];
          nx -= dx[i];
          break;
        }
        if (MAP[ny][nx] != 0)
          break;
      }

      if (visited[ny][nx])
        continue;

      q.push({ny, nx});
      visited[ny][nx] = visited[now.y][now.x] + 1;
    }
  }

  return visited[de.y][de.x] - 1;
}

void dfs(int level, Pos now, int pushCnt) {
  if (level == maxCardType) {
    ans = min(ans, pushCnt);
    return;
  }

  for (int cardType = 1; cardType <= maxCardType; cardType++) {
    if (!cardExist[cardType])
      continue;
    cardExist[cardType] = false;

    Pos pos0 = cardPos[cardType][0];
    Pos pos1 = cardPos[cardType][1];

    int dist0to1 = bfs(now, pos0) + bfs(pos0, pos1) + 2;
    int dist1to0 = bfs(now, pos1) + bfs(pos1, pos0) + 2;

    MAP[pos0.y][pos0.x] = MAP[pos1.y][pos1.x] = 0;

    dfs(level + 1, pos1, pushCnt + dist0to1);
    dfs(level + 1, pos0, pushCnt + dist1to0);

    MAP[pos0.y][pos0.x] = MAP[pos1.y][pos1.x] = cardType;

    cardExist[cardType] = true;
  }
}

int solution(vector<vector<int>> board, int r, int c) {
  vector<vector<Pos>>(7).swap(cardPos);
  vector<bool>(7).swap(cardExist);
  maxCardType = 0;
  ans = INF;

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      int cardType = MAP[y][x] = board[y][x];
      if (cardType == 0)
        continue;
      cardPos[cardType].push_back({y, x});
      cardExist[cardType] = true;
      maxCardType = max(maxCardType, cardType);
    }
  }

  dfs(0, {r, c}, 0);

  return ans;
}
