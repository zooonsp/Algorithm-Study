#include<iostream>

#define INF 987654321

using namespace std;

int dist[101][101];

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = INF;
			// 자기 자신으로 가는 길은 0으로 초기화
			if (i == j) dist[i][j] = 0;
		}
	 }

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		// 똑같은 경로에 대해서도 최솟값을 찾아줘야 한다!
		dist[a][b] = min(c, dist[a][b]);
	}

	// i에서 j로 가는데 경유지가 k인 경우에 대한 최소 비용 갱신
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			// 방문하지 않은 곳이라면 0을 출력
			if (dist[i][j] == INF) cout << "0 ";
			else cout << dist[i][j] << " ";
		}
		cout << '\n';
	}

	return 0;
}
