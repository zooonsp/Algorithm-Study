/*
RGB거리에는 집이 N개 있다. 거리는 선분으로 나타낼 수 있고, 1번 집부터 N번 집이 순서대로 있다.
집은 빨강, 초록, 파랑 중 하나의 색으로 칠해야 한다. 
각각의 집을 빨강, 초록, 파랑으로 칠하는 비용이 주어졌을 때, 아래 규칙을 만족하면서 모든 집을 칠하는 비용의 최솟값을 구해보자.

1번 집의 색은 2번, N번 집의 색과 같지 않아야 한다.
N번 집의 색은 N-1번 집의 색과 같지 않아야 한다.
i(2 ≤ i ≤ N-1)번 집의 색은 i-1번, i+1번 집의 색과 같지 않아야 한다.
2168KB, 0ms
*/

#include <bits/stdc++.h>

constexpr int INF = (int)10e8;
using namespace std;

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	int N;
	cin >> N;
	vector<vector<int>> colors(N, vector<int>(3,0));
	vector<vector<int>> DP;
	for(vector<int>& row : colors) {
		cin >> row[0] >> row[1] >> row[2];
	}

	int ans = INF;
	for(int color = 0; color < 3; ++ color) { // 시작별로 따로따로 계산하기
		DP.assign(begin(colors), end(colors));
		DP[0][0] = DP[0][1] = DP[0][2] = INF;
		DP[0][color] = colors[0][color];
		for(int i=1;i<N;++i) {
			DP[i][0] += min(DP[i-1][1], DP[i-1][2]);
			DP[i][1] += min(DP[i-1][0], DP[i-1][2]);
			DP[i][2] += min(DP[i-1][0], DP[i-1][1]);
		}

		for(int i = 0; i < 3; ++i) {
			if(i==color) continue;
			ans = min(ans, DP[N-1][i]);
		}

	}

	cout << ans << '\n';

	return 0;
}