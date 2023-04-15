#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// const
constexpr int INF = static_cast<int>(21e8);

// graph
using Graph = vector<vector<int>>;
Graph graph;

void GetDepth(vector<int>& depth) {
	queue<int> q;
	q.push(1);
	depth[1] = 0;

	while (!q.empty()) {
		int now = q.front(); q.pop();
		int& nowDepth = depth[now];
		for (int& next : graph[now]) {
			if (depth[next] != INF)  continue; // TREE -> 가는 경로 한 개 뿐
			depth[next] = nowDepth + 1;
			q.push(next);
		}
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N{}, M{};
	cin >> N;
	
	graph = vector<vector<int>>(N + 1);
	for (int n{}; n < N - 1; ++n) { // tree 간선 -> N - 1개, 루트는 1번
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> depth(N + 1, INF);
	GetDepth(depth);

	cin >> M;
	for (int m{}; m < M; ++m) {
		int s, e;
		cin >> s >> e;
		if (depth[s] < depth[e]) swap(s, e);
		
		// depth 맞추기
		while (depth[s] != depth[e]) {
			for (int& next : graph[s]) {
				if (depth[next] < depth[s]) {
					s = next;
					break;
				}
			}
		}
		while (s != e) {
			for (int& next : graph[s]) {
				if (depth[next] < depth[s]) {
					s = next;
					break;
				}
			}
			for (int& next : graph[e]) {
				if (depth[next] < depth[e]) {
					e = next;
					break;
				}
			}
		}
		cout << s << '\n';
	}

	return 0;
}