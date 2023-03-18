// 정확성(50) + 효율성(50)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = static_cast<int>(21e8);
int goalAlp, goalCop;

int solution(int alp, int cop, vector<vector<int>> problems) {
	int answer = 0;
	goalAlp = -1, goalCop = -1;
	// for(_Vector_iterator<_Vector_val<_Vector_alloc<_Vec_base_types<vector<int>, allocator<vector<int>>>>::_Val_types>>::value_type& problem : problems) {
	for (auto& problem : problems) {
		goalAlp = max(goalAlp, problem[0]);
		goalCop = max(goalCop, problem[1]);
	}
	vector<vector<int>> DP(goalAlp + 1, vector<int>(goalCop + 1, INF));
	// DP[alp][cop] = value that can be minimum days to reach alp and cop.
	// only study - from (alp, cop) to DP[alp][cop]
	alp = min(alp, goalAlp);
	cop = min(cop, goalCop);
	DP[alp][cop] = 0;

	// Make DP table 
	for (int i = alp; i <= goalAlp; ++i) {
		for (int j = cop; j <= goalCop; ++j) {
			
			// study
			int newi = min(i + 1, goalAlp);
			int newj = min(j + 1, goalCop);
			DP[newi][j] = min(DP[newi][j], DP[i][j] + 1);
			DP[i][newj] = min(DP[i][newj], DP[i][j] + 1);

			// problem solve
			// [alp_req, cop_req, alp_rwd, cop_rwd, cost]
			for (auto& problem : problems) {
				if (i >= problem[0] && j >= problem[1]) { // can solve
					int newAlp = min(i + problem[2], goalAlp);
					int newCop = min(j + problem[3], goalCop);
					DP[newAlp][newCop] = min(DP[newAlp][newCop], DP[i][j] + problem[4]);
				}
			}
		}
	}

	answer = DP[goalAlp][goalCop];
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