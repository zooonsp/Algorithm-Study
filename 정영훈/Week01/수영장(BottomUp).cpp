#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// 0 : 하루권, 1 : 1개월권, 2 : 3개월권, 3 : 12개월권
int cost[4]{};
int diff[4] = { -1,1,3,12 }; // 달(하루권은 -1)

int days[13]{}; // 각 달별로 이용하고자 하는 '일'수

int dp[13]{}; // 각 달별로 12월까지 이용하는데 들어가는 최소 비용
// 다시 계산하는 것을 방지하는 것이 가장 크다!

void input() {
	for (int i = 0; i < 4; ++i) cin >> cost[i];
	for (int i = 1; i <= 12; ++i) {
		cin >> days[i];
		dp[i] = 0;
	}
}

// dp[now] : 시작부터 now까지의 계산 결과
int solution() {
	// dp[now] : now 달까지의 계산 결과
	//dp[now - 1] + days[0] * cost[0]; // 1일권
	//dp[now - 1] + cost[1]; // 1개월권
	//dp[now - 3] + cost[2]; // 3개월권
	//dp[now - 12] + cost[3]; // 3개월권

	dp[0] = 0; // 시작점은 'prev'가 없으므로 직접 세팅하기~
	for (int month{ 1 }; month <= 12; ++month) {
		int now{ month };
		// dp table 만들기

		int tmp = dp[now - 1] + days[now] * cost[0]; // 1일권
		// 반복문을 통한 일반화
		for (int i = 1; i <= 3; ++i) {
			if (now - diff[i] < 0) continue; // 문제될 수 있는 부분 처리
			tmp = min(tmp, dp[now - diff[i]] + cost[i]);
		}
		dp[now] = tmp;
	}

	return dp[12]; // 결과
}

int main() {
	int tc;
	cin >> tc;
	for (int test_case = 1; test_case <= tc; ++test_case) {
		input();
		cout << "#" << test_case << " " << solution() << '\n';
	}
	return 0;
}