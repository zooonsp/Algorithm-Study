// https://blog.encrypted.gg/1032
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Pos {
  int y;
  int x;
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int dfs(vector<vector<int>> &board, Pos now, Pos op) {
  if (board[now.y][now.x] == 0)
    return 0;

  int ret = 0;

  for (int i = 0; i < 4; i++) {
    int ny = now.y + dy[i];
    int nx = now.x + dx[i];

    if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
      continue;
    if (board[ny][nx] == 0)
      continue;

    board[now.y][now.x] = 0;
    int val = dfs(board, op, {ny, nx}) + 1;
    board[now.y][now.x] = 1;

    if (!(ret & 1) && (val & 1))
      ret = val;
    else if (!(ret & 1) && !(val & 1))
      ret = max(ret, val);
    else if ((ret & 1) && (val & 1))
      ret = min(ret, val);
  }

  return ret;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
  return dfs(board, {aloc[0], aloc[1]}, {bloc[0], bloc[1]});
}
