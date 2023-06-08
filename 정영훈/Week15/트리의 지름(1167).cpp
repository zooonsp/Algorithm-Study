// 1167
// 9428KB, 76ms
#include <bits/stdc++.h>

using namespace std;

inline void FASTIO() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
}

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
using Graph = vector<vector<Edge>>;

int answer{-1};

int main() {
	FASTIO();
	int V{}; cin >> V;
	Graph graph(V+1); // 1 ~ V
	for(int i{};i<V;++i) {
		int n; cin >> n; // 정점 번호
		while(1) {
			int to, weight; cin >> to;
			if(to == -1) break;
			cin >> weight;
			graph[n].emplace_back(to, weight);
		}
	}

	// 1번 정점에서 가장 먼 정점(far) 찾기
	vector<int> visited(V + 1, 0);
	visited[1] = 1;
	stack<int> S;
	S.push(1);
	int farNode{1}, farDist{-1};
	while(!S.empty()) {
		int now = S.top(); S.pop();
		for(Edge& next : graph[now]) {
			if(visited[next.to]) continue;
			visited[next.to] = visited[now] + next.weight;
			S.emplace(next.to);
			if(visited[next.to] > farDist) {
				farDist = visited[next.to];
				farNode = next.to;
			}
		}
	}

	// far에서 가장 먼 정점 찾기 = 트리의 지름
	visited.assign(V+1,0);
	visited[farNode] = 1;
	while(!S.empty()) S.pop();
	S.push(farNode);
	farDist = -1;
	while(!S.empty()) {
		int now = S.top(); S.pop();
		for(Edge& next : graph[now]) {
			if(visited[next.to]) continue;
			visited[next.to] = visited[now] + next.weight;
			S.emplace(next.to);
			farDist = max(farDist, visited[next.to]);
		}
	}

	cout << farDist - 1 << '\n';
	return 0;
}