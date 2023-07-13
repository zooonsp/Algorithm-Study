// kosaraju
// 4416KB, 28ms

#include <bits/stdc++.h>
// iostream, vector, stack, algorithm

using namespace std;
vector<vector<int>> graph, transposeGraph;
vector<bool> visited;

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 정점 번호들.
stack<int> S;

void FillStack(int curr) {
	visited[curr] = true;

	for (int& next : graph[curr]) {
		if (!visited[next]) FillStack(next);
	}

	S.push(curr);
}

void FindSCC(int curr, vector<int>& components) {
	visited[curr] = true;
	components.push_back(curr);

	for (int& next : transposeGraph[curr]) {
		if (!visited[next]) {
			FindSCC(next, components);
		}
	}
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	int V, E;
	cin >> V >> E;
	graph.assign(V + 1, {});
	transposeGraph.assign(V + 1, {});
	visited.assign(V + 1, false);

	for (int e{}; e < E; ++e) {
		int a, b;
		cin >> a >> b; // 방향성 존재
		graph[a].push_back(b); // 원본 그래프
		transposeGraph[b].push_back(a); // 전치 그래프
	}

	// Stack에 방문한 순서대로 저장
	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FillStack(v);
		}
	}

	visited.assign(V + 1, false);
	while (!S.empty()) {
		int now = S.top(); S.pop();
		if (!visited[now]) {
			vector<int> components;
			FindSCC(now, components);
			sort(begin(components), end(components)); // 각각의 SCC를 출력할 때 그 안에 속한 정점들은 오름차순으로 출력
			SCC.emplace_back(components);
		}
	}

	// 여러 개의 SCC에 대해서는 그 안에 속해있는 가장 작은 정점의 정점 번호 순으로 출력
	sort(begin(SCC), end(SCC));

	cout << SCC.size() << '\n';
	for (auto& scc : SCC) {
		for (auto& v : scc) {
			cout << v << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}

