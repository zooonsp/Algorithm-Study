#include <iostream>
#include <algorithm>
using namespace std;

int N;
int oper_cnt[4];
int num[12];
int result;
int max_result, min_result;

void dfs(int level) {
	if (level >= N - 1) {
		max_result = max(max_result, result);
		min_result = min(min_result, result);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (oper_cnt[i] == 0) continue;

		oper_cnt[i]--;
		int temp = result;

		if (i == 0)
			result += num[level + 1];
		else if (i == 1)
			result -= num[level + 1];
		else if (i == 2)
			result *= num[level + 1];
		else if (i == 3)
			result /= num[level + 1];

		dfs(level + 1);

		result = temp;
		oper_cnt[i]++;
	}
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N;

		max_result = -21e8, min_result = 21e8;

		for (int i = 0; i < 4; i++)
			cin >> oper_cnt[i];

		for (int i = 0; i < N; i++)
			cin >> num[i];

		result = num[0];

		dfs(0);

		cout << max_result - min_result << '\n';
	}
	return 0;
}
