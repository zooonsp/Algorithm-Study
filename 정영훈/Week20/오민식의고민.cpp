/*
오민식의 여행은 A도시에서 시작해서 B도시에서 끝난다.

또, 같은 도시를 여러 번 방문할 수 있으며, 그 도시를 방문할 때마다 돈을 벌게 된다. 
모든 교통 수단은 입력으로 주어진 방향으로만 이용할 수 있으며, 여러 번 이용할 수도 있다. => 단방향

만약 오민식이 도착 도시에 도착하는 것이 불가능 => gg
오민식이 도착 도시에 도착했을 때 돈을 무한히 많이 가지고 있을 수 있다면 => Gee
그 외의 경우에는 돈의 액수의 최대값을 출력
2024KB, 0ms
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
struct Edge {
	int to;
	ll weight;
	Edge(int to, ll weight) : to(to), weight(weight) {}
};
constexpr ll INF = 1LL << 61;

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	int N, A, B, M; // 도시의 수, 시작 도시, 도착 도시, 교통 수단 개수
	cin >> N >> A >> B >> M;
	vector<vector<Edge>> graph(N); // 0 ~ N
	for (int m{}; m < M; ++m) {
		int a, b, c; // a -> b (cost = c)
		cin >> a >> b >> c;
		graph[a].emplace_back(b, static_cast<ll>(c));
	}

	vector<int> earning(N, 0);
	for (int& e : earning) {
		cin >> e;
	}

	// 기존 edge에 earning 반영
	for (int n{}; n < N; ++n) {
		for (Edge& e : graph[n]) {
			e.weight -= earning[e.to]; // 도착점에서 벌 수 있는 돈을 빼주기.
		}
	}

	// Bellman-Ford
	vector<ll> dist(N, INF);
	vector<int> negVertex; // negative cycle이 생기는 정점들 표시
	negVertex.reserve(N);
	bool negCycle{ false };
	dist[A] = -earning[A];
	for (int t{ 1 }; t <= N; ++t) { 
		bool nowUpdate{ false };
		for (int n{}; n < N; ++n) {
			if (dist[n] == INF) continue; // 아직 방문하지 않았으니 skip
			for (Edge& e : graph[n]) {
				if (dist[e.to] > dist[n] + e.weight) {
					dist[e.to] = dist[n] + e.weight;
					nowUpdate = true;
					if (t == N) { // N번째 update => neg cycle
						negVertex.push_back(n);
						negCycle = true;
					}
				}
			}
		}
		if (!nowUpdate) break; // 지금 업데이트가 없으면 앞으로도 없음 => 조기 종료 가능
	}

	if (dist[B] == INF) cout << "gg\n"; // 도달 불가능
	else if (negCycle) { // negCycle이 생기는 경우, 해당 cycle에서 도착점 도달 가능 여부 확인 필요
		bool chk{ false };
		for (int& v : negVertex) { // negCycle이 생기는 정점들 표시
			// BFS를 통해 해당하는 정점에서 B(도착점)에 도달가능한지 확인
			auto result = [&graph, v, B, N]() -> bool {
				vector<int> visited(N, 0);
				queue<int> q;
				q.push(v);
				visited[v] = 1;
				while (!q.empty()) {
					int now = q.front(); q.pop();
					for (Edge& e : graph[now]) {
						if (e.to == B) return true; // 도달 가능
						if (!visited[e.to]) {
							q.push(e.to);
							visited[e.to] = 1;
						}
					}
				}
				return false; // 도달 불가능
			} ();
			if (result) {
				chk = true;
				break;
			}
		}
		if (chk) cout << "Gee\n"; // negCycle에서 B가 도달 가능
		else cout << -dist[B] << '\n';
	}
	else cout << -dist[B] << '\n';

	return 0;
}