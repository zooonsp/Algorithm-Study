#include <vector>
using namespace std;

// 2차원 vector를 시계 방향으로 회전
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

  for (int dir = 0; dir < 4; dir++) {       // key를 4번 회전
    for (int sy = 0; sy <= M + N; sy++) {   // key의 시작 y좌표 (0 ~ M+N)
      for (int sx = 0; sx <= M + N; sx++) { // key의 시작 x좌표 (0 ~ M+N)

        // board → lock의 상하좌우로 M 만큼의 여유 공간
        vector<vector<int>> board(N + M * 2, vector<int>(N + M * 2));

        // key를 board에 위치시키기
        for (int y = 0; y < M; y++)
          for (int x = 0; x < M; x++)
            board[sy + y][sx + x] = key[y][x];

        bool flag = true; // key로 lock을 열 수 있는가?

        for (int y = 0; y < N; y++) {
          for (int x = 0; x < N; x++) {
            // key와 lock이 둘 다 0이거나 둘 다 1일 경우 열 수 없다.
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
