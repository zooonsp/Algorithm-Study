#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 987654321;
// dp[알고력][코딩력]: 해당 알고력과 해당 코딩력을 얻기 위해 필요한 최단 시간
int dp[151][151];
// maxAlp: 모든 문제를 다 풀 수 있도록 하는 목표 알고력
// maxCop: 모든 문제를 다 풀 수 있도록 하는 목표 코딩력
int maxAlp, maxCop;

// alp: 초기 알고력
// cop: 초기 코딩력
// problems: 문제의 정보를 담은 2차원 vector

// problems의 원소: [alpReq, copReq, alpRwd, copRwd, cost]
// - alpReq: 문제를 푸는데 필요한 알고력
// - copReq: 문제를 푸는데 필요한 코딩력
// - alpRwd: 문제를 풀었을 때 증가하는 알고력
// - copRwd: 문제를 풀었을 때 증가하는 코딩력
// - cost: 문제를 푸는데 드는 시간
int solution(int alp, int cop, vector<vector<int>> problems) {
  // 알고리즘 공부 => 알고력 1을 높이기 위해 1의 시간 필요
  problems.push_back({0, 0, 1, 0, 1});
  // 코딩 공부 => 코딩력 1을 높이기 위해 1의 시간 필요
  problems.push_back({0, 0, 0, 1, 1});

  // 처음부터 모든 문제를 다 풀 수 있는 경우가 있으므로
  // 목표 알고력과 목표 코딩력을 초기 알고력과 초기 코딩력으로 초기화
  maxAlp = alp;
  maxCop = cop;

  // 문제들을 확인하면서 목표 알고력과 목표 코딩력 갱신
  for (auto prob : problems) {
    maxAlp = max(maxAlp, prob[0]);
    maxCop = max(maxCop, prob[1]);
  }

  // 초기 알고력부터 목표 알고력까지
  // 초기 코딩력부터 목표 코딩력까지
  // dp를 최대값으로 초기화
  for (int a = alp; a <= maxAlp; a++)
    for (int c = cop; c <= maxCop; c++)
      dp[a][c] = MAX;

  // 초기 알고력과 초기 코딩력을 얻기 위해 필요한 최단 시간은 0
  dp[alp][cop] = 0;

  // 초기 알고력부터 목표 알고력까지
  // 초기 코딩력부터 목표 코딩력까지
  // 풀 수 있는 문제들을 풀어가며
  // 다음 알고력과 다음 코딩력을 얻기 위해 필요한 최단 시간 계산
  for (int a = alp; a <= maxAlp; a++) {
    for (int c = cop; c <= maxCop; c++) {
      // 모든 문제들을 확인
      for (auto prob : problems) {
        // 문제를 풀 수 없으면 skip
        if (a < prob[0] || c < prob[1])
          continue;

        // 문제를 풀었을 때 얻을 수 있는 다음 알고력과 다음 코딩력
        // 목표 알고력과 목표 코딩력을 넘어가지 않도록 처리
        int na = min(a + prob[2], maxAlp);
        int nc = min(c + prob[3], maxCop);

        // 다음 알고력과 다음 코딩력을 얻기 위해 필요한 시간
        // = 현재 알고력과 현재 코딩력을 얻기 위해 필요한 시간
        // + 현재 문제를 푸는데 드는 시간
        int ncost = dp[a][c] + prob[4];

        // 다음 알고력과 다음 코딩력을 얻기 위해 필요한 시간이
        // 이미 기록된 값보다 작다면 최소값으로 갱신
        if (dp[na][nc] > ncost)
          dp[na][nc] = ncost;
      }
    }
  }

  // 목표 알고력과 목표 코딩력을 얻기 위해 필요한 최단 시간 return
  return dp[maxAlp][maxCop];
}
