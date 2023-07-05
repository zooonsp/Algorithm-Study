#include <iostream>

using namespace std;

int dist[401][401];

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		// a = b보다 더 과거, b = a 보다 미래
		int a, b;
		cin >> a >> b;
		// 먼 과거에서 덜 과거는 -1
		dist[a][b] = -1;
		// 덜 과거에서 먼 과거로는 1
		dist[b][a] = 1;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				// 만약 (현재) i -> k -> j (과거) 라면
				if (dist[i][k] == 1 && dist[k][j] == 1) {
					dist[i][j] = 1; dist[j][i] = -1;
				}
			}
		}
	}

	int s;
	cin >> s;
	
	while (s--) {
		int a, b;
		cin >> a >> b;
		cout << dist[a][b] << '\n';
	}

	return 0;
}
