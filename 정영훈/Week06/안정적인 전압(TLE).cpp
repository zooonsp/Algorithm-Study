// TLE 1983ms
// 진짜 매번 다 누적해가면서 계산하기
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using plli = pair<ll, int>; // {합, 개수}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N{}, ans{1};
	cin >> N;
	vector<int> volt(N, 0);
	for (int& v : volt) cin >> v;
	
	vector<plli> notChanged;
	vector<plli> changed;
	if (volt[0]) { // volt[0] != 0
		notChanged.push_back({ volt[0], 0 });
		changed.push_back({ 0,1 });
	}
	else {
		notChanged.push_back({ 0,1 });
	}

	for (int n{1}; n < N - 1; ++n) {
		vector<plli> tmpNotChanged;
		vector<plli> tmpChanged;
		for (plli& p : notChanged) {
			ll tmpSum = p.first + volt[n];
			if (tmpSum) { // tmpSum != 0
				tmpNotChanged.push_back({ tmpSum, p.second });
				tmpChanged.push_back({ 0, p.second + 1 }); // 0으로 바꾸기
			}
			else {
				tmpNotChanged.push_back({ 0, p.second + 1 });
			}
		}
		for (plli& p : changed) {
			ll tmpSum = p.first + volt[n];
			if (tmpSum) { // tmpSum != 0
				tmpChanged.push_back({ tmpSum, p.second });
			}
			else {
				tmpChanged.push_back({ 0, p.second + 1 });
			}
		}
		notChanged = move(tmpNotChanged);
		changed = move(tmpChanged);
	}

	// 마지막 답
	if (N > 1) {
		int ans{ -1 }, n{ N - 1 };
		for (plli& p : notChanged) {
			ll tmpSum = p.first + volt[n];
			if (tmpSum) { // tmpSum != 0
				ans = max(ans, p.second + 1);
			}
			else {
				ans = max(ans, p.second + 1);
			}
		}
		for (plli& p : changed) {
			ll tmpSum = p.first + volt[n];
			if (!tmpSum) { // tmpSum == 0
				ans = max(ans, p.second + 1);
			}
		}
	}

	cout << ans << '\n';
	return 0;
}