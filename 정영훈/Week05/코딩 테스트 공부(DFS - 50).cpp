// 정확성(50) + 효율성(0)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = static_cast<int>(21e8);

int goalAlp, goalCop;
int lowAlp, lowCop;
int Ans;

void dfs(vector<vector<int>>& problems, int nowTime, int curAlp, int curCop) {
	// basecase
	if (curAlp >= goalAlp && curCop >= goalCop) {
		Ans = min(Ans, nowTime);
		return;
	}

	// pruning
	if (nowTime >= Ans) return;

	// solve
	// [alp_req, cop_req, alp_rwd, cop_rwd, cost]
	for (auto& problem : problems) {
		if (problem[0] <= curAlp && problem[1] <= curCop) { // can solve
			dfs(problems, nowTime + problem[4], curAlp + problem[2], curCop + problem[3]);
		}
	}

	// study
	if(curAlp < goalAlp) dfs(problems, nowTime + 1, curAlp + 1, curCop);
	if(curCop < goalCop) dfs(problems, nowTime + 1, curAlp, curCop + 1);
}

int solution(int alp, int cop, vector<vector<int>> problems) {
	int answer = 0;
	lowAlp = lowCop = INF;
	// problems[i] : [alp_req, cop_req, alp_rwd, cop_rwd, cost]
	// [필요한 알고력, 필요한 코딩력, 증가하는 알고력, 증가하는 코딩력, 걸리는 시간]

	for (auto& problem : problems) {
		goalAlp = max(goalAlp, problem[0]);
		goalCop = max(goalCop, problem[1]);
		lowAlp = min(lowAlp, problem[0]);
		lowCop = min(lowCop, problem[1]);
	}

	/*auto cmp = [](const vector<int>& p1, const vector<int>& p2) {
		return (p1[0] + p1[1] < p2[0] + p2[1]);
	};
	sort(begin(problems), end(problems), cmp);*/

	// only study
	Ans = max(0, goalAlp - alp) + max(0, goalCop - cop);
	
	dfs(problems, 0, alp, cop);

	answer = Ans;
	return answer;
}

int main() {
	// T1
	// vector<vector<int>> problems{ {10,15,2,1,2}, {20,20,3,3,4} };
	// int alp{ 10 }, cop{ 10 };

	// T2
	vector<vector<int>> problems{ {0,0,2,1,2}, {4,5,3,1,2},{4,11,4,0,2},{10,4,0,4,2} };
	int alp{ 0 }, cop{ 0 };
	cout << solution(alp,cop,problems) << '\n';
	return 0;
}