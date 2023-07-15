// tarjan
// https://m.blog.naver.com/kks227/220802519976
// 3580KB, 24ms

#include <bits/stdc++.h>
// iostream, vector, stack, algorithm

using namespace std;
vector<vector<int>> graph;
vector<int> dfsN; // 방문 순서
int dfsNIndex;

vector<bool> finished; // SCC 분리가 끝난 정점만 true

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 정점 번호들.
stack<int> S;

int DFS(int curr) {
	dfsN[curr] = ++dfsNIndex;
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값을 result에 저장
	int result = dfsN[curr];
	for (int& next : graph[curr]) {
		if (dfsN[next] == 0) { // 아직 방문하지 않은 이웃
			result = min(result, DFS(next));
		}
		else if (!finished[next]) { // 방문은 했으나 아직 SCC로 추출되지는 않은 이웃.
			result = min(result, dfsN[next]);
		}
	}

	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (result == dfsN[curr]) {
		vector<int> currSCC;
		while (true) {
			int t = S.top(); S.pop();
			currSCC.push_back(t);
			finished[t] = true;
			if (t == curr) break;
		}
		sort(begin(currSCC), end(currSCC)); // 각각의 SCC를 출력할 때 그 안에 속한 정점들은 오름차순으로 출력
		SCC.push_back(currSCC);
	}
	
	return result;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph.assign(SIZE, {});
	dfsN.assign(SIZE, {});
	finished.assign(SIZE, false);

	for (int e{}; e < E; ++e) {
		int a, b;
		cin >> a >> b; // 방향성 존재
		graph[a].push_back(b); 
	}

	// 각 정점마다 DFS하면서 SCC 추출.
	// 연결 그래프가 아닐 수도 있기 때문에 반복문이 필요함.
	for (int v{ 1 }; v <= V; ++v) {
		if (!dfsN[v]) { // dfsN[v] == 0 -> v는 미방문
			DFS(v);
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
