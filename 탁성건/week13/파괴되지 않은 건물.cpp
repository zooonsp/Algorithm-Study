// https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-6-%ED%8C%8C%EA%B4%B4%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EA%B1%B4%EB%AC%BC
#include <vector>
using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
  int answer = 0;
  const int N = board.size(), M = board[0].size();

  // 2차원 누적합을 계산할 vector
  vector<vector<int>> sum(N + 1, vector<int>(M + 1));

  for (vector<int> &s : skill) {
    int type = s[0];
    int r1 = s[1], c1 = s[2];
    int r2 = s[3], c2 = s[4];
    int degree = s[5];

    if (type == 1)
      degree *= -1;

    sum[r1][c1] += degree;
    sum[r1][c2 + 1] -= degree;
    sum[r2 + 1][c1] -= degree;
    sum[r2 + 1][c2 + 1] += degree;
  }

  // row 누적합
  for (int r = 0; r < N; r++)
    for (int c = 0; c < M; c++)
      sum[r][c + 1] += sum[r][c];

  // col 누적합
  for (int c = 0; c < M; c++)
    for (int r = 0; r < N; r++)
      sum[r + 1][c] += sum[r][c];

  // board와 더하기
  for (int r = 0; r < N; r++)
    for (int c = 0; c < M; c++)
      if (board[r][c] + sum[r][c] > 0)
        answer++;

  return answer;
}
