#include <iostream>
#include <vector>

#define INF 987654321

using namespace std;

int n, m;

vector<pair<int, int>> v[501];
// 한 사이클에 최대 절대값 6천만, 이 과정 N번 반복하면서 곱함
long long dist[501];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie();

	cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		// a = 현재노드, b = 다음노드, c = cost
		int a, b, c;
		cin >> a >> b >> c;
		v[a].push_back({ b, c });
	}

	// dist 배열 무한대로 초기화
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}

	// 출발지점 거리 갱신
	dist[1] = 0;

	// n - 1 만큼 반복하고 n번째때 음의 순환 판단
	for (int i = 1; i <= n; i++) {
		// 모든 간선에 대해 확인해서 최단 거리 테이블 갱신
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < v[j].size(); k++) {
				int nextNode = v[j][k].first;
				int nextCost = v[j][k].second;
				// 현재 노드의 최단 거리 테이블이 한번이라도 갱신됐고
				// 다음 노드의 최단 거리보다 지금 계산하는 거리가 더 작은경우
				if (dist[j] != INF && dist[nextNode] > dist[j] + nextCost) {
					dist[nextNode] = dist[j] + nextCost;
					// 만약 n번째 반복하는데 값이 갱신된다면
					if (i == n) {
						cout << -1;
						return 0;
					}
				}
			}
		}
	}
	
	// 2번부터 끝번호까지
	for (int i = 2; i <= n; i++) {
		// 1번으로 출발해서 도달할 수 있다면
		if (dist[i] != INF) {
			cout << dist[i] << '\n';
		}
		// 갈 방법이 없다면
		else {
			cout << "-1\n";
		}
	}

	return 0;
}
