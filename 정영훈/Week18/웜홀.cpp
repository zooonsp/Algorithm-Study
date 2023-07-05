/*
N개의 지점이 있고 N개의 지점 사이에는 M개의 도로와 W개의 웜홀이 있다
단 도로는 방향이 없으며 웜홀은 방향이 있다.
출발을 하였을 때보다 시간이 되돌아가 있는 경우가 있는지 없는지 궁금해졌다.

웜홀을 제외한 도로는 방향성이 없기 때문에 시작점에서 negative cycle에 도달이 가능하다면,
negative cycle에서 웜홀까지 도달하는 것도 당연히 가능함.
또한 시작점도 정해져 있지 않으니 negative cycle 존재만 알 수 있으면 됨.

negative cycle 파악을 위해 
모든 정점에 대해 bellman-ford를 해야 한다고 생각할 수 있으나
(모든 정점에 대해 bellman-ford(O(VE)) 수행 시 T * V * VE => 3,125,000,000 (TLE)
하나의 정점(아무거나 잡아도)에서 시작해도
dist[d] != INF를 제거함으로써 negative cycle 판단이 가능해짐.
https://www.acmicpc.net/board/view/72995
2152KB, 32ms
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
	int T;
	cin >> T;
	while (T--) {
		int N, M, W;
		cin >> N >> M >> W; // 지점의 개수, 도로의 개수, 웜홀의 개수
		vector<vector<Edge>> graph(N + 1); // 1 ~ N
		for (int m = 0; m < M; ++m) { // 도로는 방향이 없으며
			int s, e, t;
			cin >> s >> e >> t;
			graph[s].emplace_back(e, t);
			graph[e].emplace_back(s, t);
		}

		for (int w = 0; w < W; ++w) { // 웜홀은 방향이 있다
			int s, e, t;
			cin >> s >> e >> t;
			graph[s].emplace_back(e, -t);
		}

		bool negCycle = false;
		vector<long long> dist(N + 1, INF);
		dist[1] = 0;
		for (int c = 0; c < N; ++c) {
			bool nowUpdate = false; // neg cycle 찾기 전에 종료될 수 있어서 필요 없음.
			for (int now = 1; now <= N; ++now) {
				// if (dist[now] == INF) continue;
				for (auto& e : graph[now]) {
					if (dist[e.to] > dist[now] + e.weight) {
						dist[e.to] = dist[now] + e.weight;
						nowUpdate = true;
					}
				}
			}
			// neg cycle 찾기 전에 종료될 수 있어서 필요 없음.
			// if (!nowUpdate) break; // 더 이상 가중치 업데이트가 없으니 종료
			if (c == N - 1 && nowUpdate) negCycle = true; // N번째 횟수에서 가중치 업데이트 -> negative cycle 존재.
		}

		if (negCycle) cout << "YES\n";
		else cout << "NO\n";
	}
	

	return 0;
}