/*
도시 개수가 n * 100개 쯤.
floyd-warshall => O(N^3)
2152KB, 24ms
*/
#include <bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	
	int n;
	cin >> n; // 도시의 개수
	vector<vector<int>> dist(n, vector<int>(n, INF));
	for (int i = 0; i < n; ++i) {
		dist[i][i] = 0; // 자기 자신으로 가는 비용 = 0
	}
	int m;
	cin >> m; // 버스의 개수
	for (int i = 0; i < m; ++i) {
		int a, b, c; // a -> b (비용 = c)
		cin >> a >> b >> c;
		--a, --b;
		// 시작 도시와 도착 도시를 연결하는 노선은 하나가 아닐 수 있다.
		dist[a][b] = min(dist[a][b], c);
	}

	// floyd-warshall
	for (int k = 0; k < n; ++k) { // 경유
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (auto& row : dist) {
		for (auto& v : row) {
			// 만약, i에서 j로 갈 수 없는 경우에는 그 자리에 0을 출력한다. - 빼먹었네
			if (v == INF) cout << 0 << ' ';
			else cout << v << ' ';
		}
		cout << '\n';
	}

	return 0;
}