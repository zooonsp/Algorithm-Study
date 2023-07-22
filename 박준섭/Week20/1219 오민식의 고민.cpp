#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 987654321;

vector<pair<int, int>> v[51];

int main() {
	int income[51] = { 0 };
	long long dist[51] = { 0 };
	int visited[51] = { 0 };
	int n, sc, ec, m;

	cin >> n >> sc >> ec >> m;

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		// 모든 교통 수단은 입력으로 주어진 방향으로만 이용할 수 있으며
		v[a].push_back({ b, c });
	}

	for (int i = 0; i < n; ++i) {
		cin >> income[i];
		dist[i] = INF;
	}

	dist[sc] = -income[sc];

	int flag = 0;
	queue<int> q;
	// 이해를 못함,,,
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < v[j].size(); ++k) {
				int nextNode = v[j][k].first;
				int nextCost = v[j][k].second;

				if (dist[j] != INF && dist[nextNode] > dist[j] + nextCost - income[nextNode]) {
					dist[nextNode] = dist[j] + nextCost - income[nextNode];
					if (i == n) {
						visited[j] = 1;
						q.push(j);
					}
				}
			}
		}
	}

	// 도착하지 못했으면
	if (dist[ec] == INF) {
		cout << "gg";
		return 0;
	}

	while (!q.empty()) {
		int now = q.front(); q.pop();

		for (int i = 0; i < v[now].size(); ++i) {
			int next = v[now][i].first;
			if (visited[next]) continue;
			visited[next] = 1;
			q.push(next);
		}
	}

	if (visited[ec]) cout << "Gee";
	else cout << -dist[ec];
	return 0;
}
