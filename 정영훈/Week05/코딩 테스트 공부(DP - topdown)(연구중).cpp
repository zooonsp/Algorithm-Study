#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
const int INF = static_cast<int>(21e8);
int goalAlp, goalCop;
int baseAlp, baseCop;
vector<vector<int>> DP;
const int SIZE = 300;
// int DP[SIZE][SIZE]{};

const int maxReward = 30;
// 30 -> 50 + 15 (2, 3, 5, 6, 8, 9, 10 실패)
// 100 -> 50 + 35 (3, 6 - 실패, 10 TLE)
// 120 -> 50 + 40 (3 - 실패, 10 TLE)
// 150 -> 50 + 40 (3 - 실패, 10 TLE)
// 170 -> 50 + 40 (3 - 실패, 10 TLE)
// 180 -> 50 + 40 (3, 10 TLE)
// 200 -> 50 + 40 (3, 10 TLE)
// 300 -> 50 + 35 (3, 6, 10 TLE)

// 이렇게 구현하면 누락되는 케이스가 있다고 하신다..
// 또한 Top Down 방식에 대한 오해가 있었다 ㅎㅎ


int dfs(int alp, int cop, vector<vector<int>>& problems) {
	// base case
	if (alp == baseAlp && cop == baseCop) {
		return 0;
	}

	// DP
	if (DP[alp][cop] != INF) return DP[alp][cop];

	// [alp_req, cop_req, alp_rwd, cop_rwd, cost]
	int ret = INF;
	for (auto& problem : problems) {
		if (alp - problem[2] >= problem[0] && cop - problem[3] >= problem[1]) { // can solve
			// alp - problem[2] < baseAlp || cop - problem[3] < baseCop 이면 갈 수 없는 경우임
			// 시작점이 baseAlp, baseCop이기 때문에..
			if (alp - problem[2] < baseAlp || cop - problem[3] < baseCop) continue;
			ret = min(ret, problem[4] + dfs(alp - problem[2], cop - problem[3], problems));
		}
	}

	// 더 이상 문제를 풀 수 없는 경우
	if (alp > baseAlp) ret = min(ret, 1 + dfs(alp - 1, cop, problems));
	if (cop > baseCop) ret = min(ret, 1 + dfs(alp, cop - 1, problems));

	return DP[alp][cop] = ret;
}

int solution(int alp, int cop, vector<vector<int>> problems) {
	int answer = INF;
	goalAlp = -1, goalCop = -1;
	int maxRewardAlp = -1, maxRewardCop = -1;
	for (auto& problem : problems) {
		goalAlp = max(goalAlp, problem[0]);
		goalCop = max(goalCop, problem[1]);
		maxRewardAlp = max(maxRewardAlp, problem[2]);
		maxRewardCop = max(maxRewardCop, problem[3]);
	}
	// DP = vector<vector<int>>(goalAlp + maxRewardAlp, vector<int>(goalCop + maxRewardCop, INF));
	DP = vector<vector<int>>(goalAlp + maxReward, vector<int>(goalCop + maxReward, INF));
	/*for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			DP[i][j] = INF;
		}
	}*/
	baseAlp = min(alp, goalAlp);
	baseCop = min(cop, goalCop);

	for (int al{}; al < maxReward; ++al) {
		for (int co{}; co < maxReward; ++co) {
			answer = min(answer, dfs(goalAlp + al, goalCop + co, problems));
		}
	}

	return answer;
}
int main() {
	// T1 - 15
	vector<vector<int>> problems{ {10,15,2,1,2}, {20,20,3,3,4} };
	int alp{ 10 }, cop{ 10 };
	cout << solution(alp, cop, problems) << '\n';

	// T2 - 13
	problems.assign({ {0,0,2,1,2}, {4,5,3,1,2},{4,11,4,0,2},{10,4,0,4,2} });
	alp = cop = 0;
	cout << solution(alp, cop, problems) << '\n';

	problems.assign({ {0,0,2,1,2}, {0,30,2,1,2}, {0,20,2,1,2}, {0,10,2,1,2} });
	alp = 0;
	cop = 100;
	cout << solution(alp, cop, problems) << '\n';

	return 0;
}