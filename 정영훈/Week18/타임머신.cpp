/*
간선 cost가 음수일 수 있음. => dijkstra 못 씀.
Bellman-Ford
2152KB, 8ms
*/
#include <iostream>
#include <vector>

using namespace std;
constexpr long long INF = 1LL << 60;
constexpr int START = 1;

struct Edge {
	int to, weight;
	Edge(int t, int w) : to(t), weight(w) {}
};

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int N, M;
	cin >> N >> M;// 도시의 개수, 버스 노선의 개수
	vector<vector<Edge>> graph(N+1); // 1  ~ N
	for (int m = 0; m < M; ++m) {
		int a, b, c;
		cin >> a >> b >> c; // a -> b (비용 = c)
		graph[a].emplace_back(b, c);
	}

	// 1번 도시(START) -> 각 도시
	bool negCycle = false;
	vector<long long> dist(N + 1, INF);
	dist[START] = 0;
	for (int t = 0; t < N; ++t) {
		bool nowUpdate = false;
		for (int now = 1; now <= N; ++now) {
			if (dist[now] == INF) continue; // 아직 갈 수 없음.
			for (auto& e : graph[now]) {
				if (dist[e.to] > dist[now] + e.weight) {
					dist[e.to] = dist[now] + e.weight;
					nowUpdate = true;
				}
			}
		}
		if (!nowUpdate) break; // 더 이상 가중치 업데이트가 없으니 종료
		if (t == N - 1 && nowUpdate) negCycle = true; // N번째 가중치 업데이트 -> negative cycle 존재
	}
	
	if (negCycle) cout << "-1\n";
	else {
		for (int d = 2; d <= N; ++d) {
			if (dist[d] == INF) cout << "-1\n";
			else cout << dist[d] << '\n';
		}
	}

	return 0;
}