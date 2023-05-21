// 2788KB, 4ms
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
	for(int i{1};i<V;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		graph[a].emplace_back(b,c);
		graph[b].emplace_back(a,c);
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

	if( V == 1 ) cout << 0 << '\n';
	else cout << farDist - 1 << '\n';
	return 0;
}