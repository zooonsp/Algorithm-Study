/*
개미왕국은 1번 정점에,  코끼리왕국은 N번 정점에
적당한 도로하나를 파괴했을 때 1번 정점에서 N번 정점으로의 최단거리의 최댓값을 출력한다.
두 정점사이에는 두 개 이상의 길이 존재하지 않고 모든 도로는 양방향임.
한 도로를 파괴하는 것은 양방향의 길 모두를 파괴하는 것
9248KB, 76ms
*/
#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
auto compare = [](const Edge& e1, const Edge& e2) {
	return e1.weight > e2.weight; // min heap용 compare
};
using pii = pair<int, int>; // from - to (간선 정보 저장용)
constexpr int INF = 1 << 29;

int GetMaximum(vector<vector<Edge>>& graph, vector<pii>& edges, int N) {
	int ret{ -1 };
	for (auto&[from, to] : edges) {
		// from -> to 간선 무시하고 dijkstra 진행
		vector<int> dist(N + 1, INF);
		dist[1] = 0;
		priority_queue<Edge, vector<Edge>, decltype(compare)> pq(compare); // to, weight
		// Edge를 저장하지만 실제로는 to(해당 정점)까지의 weight(거리) 저장
		pq.emplace(1, 0);

		while (!pq.empty()) {
			Edge now = pq.top(); pq.pop();

			if (dist[now.to] < now.weight) continue;

			for (Edge& e : graph[now.to]) { // now.to -> e.to
				// 무시해야 할 간선
				if (e.to == to && now.to == from) continue;
				if (now.to == to && e.to == from) continue;

				if (dist[e.to] > dist[now.to] + e.weight) {
					dist[e.to] = dist[now.to] + e.weight;
					pq.emplace(e.to, dist[e.to]);
				}
			}
		}
		ret = max(ret, dist[N]);
	}
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // 정점 개수, 도로 개수

	vector<vector<Edge>> graph(N + 1); // 1 ~ N
	for (int m{}; m < M; ++m) {
		int x, y, z;
		cin >> x >> y >> z;
		graph[x].emplace_back(y, z);
		graph[y].emplace_back(x, z);
	}

	const int s{ 1 }, f{ N }; // s -> f인 최단 경로 구하기

	// dijkstra(모든 간선 이용)
	vector<int> dist(N + 1, INF);
	vector<int> from(N + 1, 0); // from[v] : 어디에서 v정점으로 왔는지
	dist[s] = 0;
	from[s] = -1; // start

	priority_queue<Edge, vector<Edge>, decltype(compare)> pq(compare); // to, weight
	// Edge를 저장하지만 실제로는 to(해당 정점)까지의 weight(거리) 저장
	pq.emplace(s, 0);
	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();

		if (dist[now.to] < now.weight) continue;

		for (Edge& e : graph[now.to]) {
			if (dist[e.to] > dist[now.to] + e.weight) {
				dist[e.to] = dist[now.to] + e.weight;
				from[e.to] = now.to;
				pq.emplace(e.to, dist[e.to]);
			}
		}
	}

	// 최단 경로에 사용한 간선 정보 저장
	vector<pii> edges;
	edges.reserve(N); // 최단 경로의 경우 최대 N - 1개의 간선
	int to{ N };
	while (from[to] != -1) {
		edges.emplace_back(from[to], to);
		to = from[to];
	}

	int answer = GetMaximum(graph, edges, N);
	cout << answer << '\n';

	return 0;
}