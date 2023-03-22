#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N{};
	cin >> N;
	vector<int> volt(N + 1, 0);
	vector<ll> accumulateSum(N + 1, 0);
	vector <int> zeroCounts(N + 1, 0);
	unordered_map<ll, int> DAT;
	for (int n{1}; n <= N; ++n) {
		cin >> volt[n];
		accumulateSum[n] = accumulateSum[n-1] + volt[n];
		zeroCounts[n] = zeroCounts[n - 1];
		if (accumulateSum[n] == 0) ++zeroCounts[n];
		if (DAT.find(accumulateSum[n]) != DAT.end()) DAT[accumulateSum[n]]++;
		else DAT[accumulateSum[n]] = 1; // insert
	}
	int ans{ 1 };
	vector<int> cand;
	for (int n{ 1 }; n <= N; ++n) { // n번째 자리에서 전압을 0으로 바꾸기
		// zeroCounts[n - 1] : 현재 나의 위치까지 발생한 누적합이 0인 개수들 (나까지 더했을 때 0인 경우도 포함)
		// DAT[volt[n]] : 나를 0으로 바꿈으로 이 위치(나는 포함 x) 뒤에서 발생할 수 있는 누적합이 0인 개수들
		ans = max(ans, zeroCounts[n - 1] + DAT[volt[n]]);
		cand.push_back(zeroCounts[n - 1] + DAT[volt[n]]);
		DAT[accumulateSum[n]]--; // 나는 지났으니까 하나 빼주기
	}
	cout << ans << '\n';

	return 0;
}