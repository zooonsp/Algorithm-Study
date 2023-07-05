#include <iostream>
#include <vector>

#define INF 2100000000

using namespace std;

vector<pair<int, int>> v[501];

long long dist[501];

int main() {

	int TC; 
	cin >> TC;
	while (TC--) {
		int n, m, w;
		cin >> n >> m >> w;

		// 양방향 이동 가능
		for (int i = 0; i < m; i++) {
			int S, E, T;
			cin >> S >> E >> T;
			v[S].push_back({ E, T });
			v[E].push_back({ S, T });
		}

		// 웜홀은 단방향 -cost
		for (int i = 0; i < w; i++) {
			int S, E, T;
			cin >> S >> E >> T;
			T *= -1;
			v[S].push_back({ E, T });
		}

		for (int i = 1; i <= n; i++) {
			dist[i] = INF;
		}

		int flag = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k < v[j].size(); k++) {
					int nextNode = v[j][k].first;
					int nextCost = v[j][k].second;

					if (dist[nextNode] > dist[j] + nextCost) {
						dist[nextNode] = dist[j] + nextCost;

						// 음의 순환 발견!
						if (i == n) flag = 1;
					}

				}
			}
		}

		// 시작지점이 따로 지정되어 있지 않아서
		// 음의 순환이 하나라도 발견되면 출발할 때보다
		// 시간이 돌아가는 게 가능한 상태!
		if (flag == 1) cout << "YES\n";
		else cout << "NO\n";

		for (int i = 1; i <= n; i++) {
			v[i].clear();
		}
	}


	return 0;
}
