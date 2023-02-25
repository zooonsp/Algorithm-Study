#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int Ms, Ma;
int N, L;
int price[15][20];  // [item][month]

int stockTrading() {
	int money = Ms;

	for (int month = 0; month <= L; month++) {
		if (month != 0)
			money += Ma;

		vector<pair<double, int>> v;

		for (int i = 0; i < N; i++) {
			if (price[i][month] >= price[i][month + 1]) continue;
			v.push_back({ (price[i][month + 1] - price[i][month]) / (double)price[i][month], i });
		}

		sort(v.begin(), v.end(), greater<pair<double, int>>());

		int profit = 0;
		int remain = money;

		for (int i = 0; i < v.size(); i++) {
			if (remain == 0) break;

			int item = v[i].second;
			int cnt = remain / price[item][month];

			if (cnt == 0) continue;

			profit += cnt * (price[item][month + 1] - price[item][month]);
			remain -= cnt * price[item][month];
		}

		money += profit;
	}

	return money - (Ms + Ma * L);
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';

		memset(price, 0, sizeof(price));

		cin >> Ms >> Ma >> N >> L;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < L + 1; j++)
				cin >> price[i][j];

		cout << stockTrading() << '\n';
	}

	return 0;
}
