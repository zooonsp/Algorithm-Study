#include <vector>
using namespace std;

void rotateCW(vector<vector<int>> &v) {
  int N = v.size();

  vector<vector<int>> temp(N, vector<int>(N));

  for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++)
      temp[x][N - y - 1] = v[y][x];

  v = temp;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
  int M = key.size();
  int N = lock.size();

  for (int dir = 0; dir < 4; dir++) {
    for (int sy = 0; sy <= M + N; sy++) {
      for (int sx = 0; sx <= M + N; sx++) {

        vector<vector<int>> board(N + M * 2, vector<int>(N + M * 2));

        for (int y = 0; y < M; y++)
          for (int x = 0; x < M; x++)
            board[sy + y][sx + x] = key[y][x];

        bool flag = true;

        for (int y = 0; y < N; y++) {
          for (int x = 0; x < N; x++) {
            if ((board[M + y - 1][M + x - 1] ^ lock[y][x]) == 0) {
              flag = false;
              break;
            }
          }
        }

        if (flag)
          return true;
      }
    }
    rotateCW(key);
  }
  return false;
}
