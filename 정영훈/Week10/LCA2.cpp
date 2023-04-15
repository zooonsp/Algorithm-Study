#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// const
constexpr int INF = static_cast<int>(21e8);
constexpr int SIZE = 17;

// graph
using Graph = vector<vector<int>>;
Graph graph;

void MakeSparseTableAndDepth(int N, vector<int>& depth, vector<vector<int>>& sparseTable) {
	queue<int> q;
	q.push(1);
	// root = 1
	depth[1] = 0;
	sparseTable[1][0] = 0;

	while (!q.empty()) {
		int now = q.front(); q.pop();
		int& nowDepth = depth[now];
		for (int& next : graph[now]) {
			if (depth[next] != INF)  continue; // TREE -> 가는 경로 한 개 뿐
			depth[next] = nowDepth + 1;
			sparseTable[next][0] = now; // next의 바로 윗 부모 = now
			q.push(next);
		}
	}

	for (int i{ 1 }; i < SIZE; ++i) {
		for (int j{ 1 }; j <= N; ++j) {
			sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
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

	// 2^17 = 131,072
	vector<int> depth(N + 1, INF);
	vector<vector<int>> sparseTable(vector<vector<int>>(N + 1, vector<int>(SIZE, 0))); // 0으로 초기화
	MakeSparseTableAndDepth(N, depth, sparseTable);

	cin >> M;
	for (int m{}; m < M; ++m) {
		int s, e;
		cin >> s >> e;
		if (depth[s] < depth[e]) swap(s, e);
		
		int diff{ depth[s] - depth[e] };
		int index{ 0 };
		while (diff >= (1 << index)) {
			if (diff & (1 << index)) s = sparseTable[s][index];
			index++;
		}

		while (s != e) {
			int i{};
			for (; i < SIZE; ++i) {
				if (sparseTable[s][i] == sparseTable[e][i]) break;
			}
			if (i > 0) --i; // i - 1 번째로 이동 후 다시 찾아야 함.
			s = sparseTable[s][i];
			e = sparseTable[e][i];
		}
		cout << s << '\n';
	}

	return 0;
}