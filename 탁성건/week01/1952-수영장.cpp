#include <iostream>
#include <algorithm>
using namespace std;

int charge[4];
int plan[13];
int dp[13];

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';

		for (int i = 0; i < 4; i++)
			cin >> charge[i];

		for (int i = 1; i <= 12; i++)
			cin >> plan[i];

		for (int month = 1; month <= 12; month++) {
			dp[month] = min(dp[month - 1] + charge[0] * plan[month], dp[month - 1] + charge[1]);

			if (month - 3 < 0) continue;

			dp[month] = min(dp[month], dp[month - 3] + charge[2]);
		}

		cout << min(dp[12], charge[3]) << '\n';
	}
	return 0;
}
