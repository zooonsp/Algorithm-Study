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

int dfs(int now) { // now : 지금 있는 달(몇 달인가?)
	// 반환값 : now에서 '끝까지' 갔을 때의 결과(최소 비용)
	// 한번 구한 반환값은 바뀌지 않는다. - 기록하자

	// 1. 끝부터 작성하자!
	if (now > 12) {
		return 0; // 12월 밖은 없는 달이므로 비용이 없다 결과
	}

	if (dp[now]) return dp[now]; // 이미 구한 거 있으면 그냥 그거 써라!

	// dfs(now + 1) : now + 1월부터 12월까지 비용이 얼마나 들어가나?
	// dfs(now + 3) : now + 3월부터 ```

	//int oneDay = dfs(now + 1) + cost[0] * days[now]; // 1일권으로 이용
	//int oneMon = dfs(now + 1) + cost[1]; // 1개월권으로 이용
	//int threeMon = dfs(now + 3) + cost[2]; // 3개월권으로 이용
	//int oneYear = dfs(now + 12) + cost[3]; // 12개월권으로 이용
	//int ret = min({ oneDay, oneMon, threeMon, oneYear }); // 이거 된다

	int ret = dfs(now + 1) + cost[0] * days[now]; // 1일권으로 이용
	for (int i = 1; i <= 3; ++i) {
		ret = min(ret, dfs(now + diff[i]) + cost[i]);
	}

	return dp[now] = ret;
}

//1. dfs구성
//2. dfs에서 '반환'받아서 계산
//   -> now에서부터 '끝까지'갔을 때의 결과
//3. 기록하고 기저에서 바로 반환


int main() {
	int tc;
	cin >> tc;
	for (int test_case = 1; test_case <= tc; ++test_case) {
		input();
		cout << "#" << test_case << " " << dfs(1) << '\n';
	}
	return 0;
}