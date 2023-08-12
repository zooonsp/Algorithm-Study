#include <deque>
#include <iostream>
using namespace std;

constexpr int LIMIT = 1000;
constexpr int MAX_N = 12;
constexpr int MAX_K = 10;

const int input2dir[]{0, 0, 2, 1, 3};
const int dx[]{1, 0, -1, 0}; // R U L D
const int dy[]{0, -1, 0, 1};

enum { WHITE, RED, BLUE };

struct Piece {
  int y;
  int x;
  int dir;
};

int N, K;
int board[MAX_N + 2][MAX_N + 2];
deque<int> dq[MAX_N + 2][MAX_N + 2];
Piece pieces[MAX_K + 1];

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  cin >> N >> K;

  for (int i = 0; i <= N + 1; ++i)
    board[0][i] = board[N + 1][i] = board[i][0] = board[i][N + 1] = 2;

  for (int y = 1; y <= N; ++y)
    for (int x = 1; x <= N; ++x)
      cin >> board[y][x];

  for (int i = 1; i <= K; ++i) {
    int y, x, dir;
    cin >> y >> x >> dir;
    pieces[i] = {y, x, input2dir[dir]};
    dq[y][x].push_back(i);
  }

  int turn = 0;

  while (turn < LIMIT) {
    ++turn;

    for (int i = 1; i <= K; ++i) {
      auto [y, x, dir] = pieces[i];

      if (dq[y][x].front() != i)
        continue;

      int ny = y + dy[dir];
      int nx = x + dx[dir];

      if (board[ny][nx] == WHITE) {
        while (!dq[y][x].empty()) {
          int p = dq[y][x].front();
          dq[ny][nx].push_back(p);
          pieces[p].y = ny;
          pieces[p].x = nx;
          dq[y][x].pop_front();
        }
      } else if (board[ny][nx] == RED) {
        while (!dq[y][x].empty()) {
          int p = dq[y][x].back();
          dq[ny][nx].push_back(p);
          pieces[p].y = ny;
          pieces[p].x = nx;
          dq[y][x].pop_back();
        }
      } else if (board[ny][nx] == BLUE) {
        dir = (dir + 2) % 4;
        pieces[i].dir = dir;
        ny = y + dy[dir];
        nx = x + dx[dir];
        if (board[ny][nx] != BLUE)
          --i;
      }

      if (dq[ny][nx].size() >= 4) {
        cout << turn << '\n';
        return 0;
      }
    }
  }

  cout << -1 << '\n';

  return 0;
}
