#include <iostream>
#include <algorithm>

using namespace std;

// 최대와 최소의 차이
// N : 3 ~ 12
// 모든 연산자 카드를 사용해야 함.
// 왼쪽에서 오른쪽으로 순차 계산
// 숫자 순서 변경 x
// 소숫점 이하는 버림(나눗셈)
// 연산 중의 값은 -1억 ~ 1억 -> int로 충분

int N;
// 각 연산자 +, -, *, /
int op_cnt[4]{};
int Numbers[12]{};
int ans_max{}, ans_min{};

void dfs(int now, int res) {
	if (now == N) {
		ans_max = max(ans_max, res);
		ans_min = min(ans_min, res);
		return;
	}
	for (int i = 0; i < 4; ++i) { // +, -, *, /
		if (op_cnt[i] > 0) {
			op_cnt[i]--;
			if (i == 0) dfs(now + 1, res + Numbers[now]);
			if (i == 1) dfs(now + 1, res - Numbers[now]);
			if (i == 2) dfs(now + 1, res * Numbers[now]);
			if (i == 3) dfs(now + 1, res / Numbers[now]); // 0으로 나누는 경우는 없음
			op_cnt[i]++;
		}
	}
}

int main()
{
	int test_case;
	int T;
	// freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		ans_max = static_cast<int>(-2e9), ans_min = static_cast<int>(2e9);
		// ans_max = -2e18, ans_min = 2e18; (e18이면 int 넘어감..)

		for (int j = 0; j < 4; ++j) cin >> op_cnt[j];
		for (int j = 0; j < N; ++j) cin >> Numbers[j];

		dfs(1, Numbers[0]);

		cout << "#" << test_case << ' ' << ans_max - ans_min << '\n';
	}
	return 0;
}