/*
위상정렬로도 가능할까? 했는데
간단히 그래프가 2개로 나누어지고 각 그래프의
2번째 방문하는 점과 3번째 방문하는 점을 비교하게 되면 비교 불가라는 결과가 나와야 하나..
간단히 방문 순서체크를 통해서는 그러한 반례 해결이 불가능함.
어딘가에서 왔는지를 다 저장해두면 되지만 굳이..?

사건의 개수가 n(400개) => 100개쯤 => O(N^3) 가능.
floyd-warshall => O(N^3)
2680KB, 88ms
*/
#include <bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	
	int n, m; // 사건의 개수, 사건의 전후 관계의 개수
	cin >> n >> m;
	vector<vector<int>> dist(n + 1, vector<int>(n+1, INF)); // 1 ~ n
	for (int i = 1; i <= n; ++i) {
		dist[i][i] = 0; // 자기 자신으로 가는 가중치 = 0
	}
	for (int i = 0; i < m; ++i) { // m개의 전후 관계 개수
		int a, b; // a가 b보다 먼저 일어남.
		cin >> a >> b;
		dist[a][b] = 1;
		// dist[b][a] = -1;
	}

	for (int k = 1; k <= n; ++k) { // 경유
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	int s;
	cin >> s;

	for (int i = 0; i < s; ++i) {
		int a, b;
		cin >> a >> b;
		if (dist[a][b] == INF) {
			if (dist[b][a] == INF) cout << "0\n";
			else cout << "1\n";
		}
		else if (dist[a][b] > 0) cout << "-1\n";
	}

	return 0;
}