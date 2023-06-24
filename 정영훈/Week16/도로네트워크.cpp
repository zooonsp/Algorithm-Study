/*
N개의 도시와 그 도시를 연결하는 N-1개의 도로 
모든 도시의 쌍에는 그 도시를 연결하는 유일한 경로가 있다
=> 트리 형태의 그래프이다.
두 도시를 연결하는 경로 사에서 가장 짧은 도로의 길이와 가장 긴 도로의 길이를 구하시오~
30128KB, 144ms
*/

#include <bits/stdc++.h>

using namespace std;
constexpr int MAXSTEP = 18;
constexpr int MAX = 1 << 30;
constexpr int MIN = -1;

struct Edge {
	int to, cost;
	Edge(int to, int cost) : to(to), cost(cost) {}
};


int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	int N;
	cin >> N;
	vector<vector<Edge>> graph(N+1); // 1 ~ N
	for (int n = 1; n < N; ++n) {
		int a, b, c;
		cin >> a >> b >> c; // a - b 사이에 길이가 C인 도로.
		graph[a].emplace_back(b, c);
		graph[b].emplace_back(a, c);
	}

	queue<int> q;
	vector<int> depth(N + 1, 0);
	vector<vector<int>> sparseT(MAXSTEP, vector<int>(N + 1, 0)); // parent
	vector<vector<int>> sparseTMin(MAXSTEP, vector<int>(N + 1, 0)); 
	vector<vector<int>> sparseTMax(MAXSTEP, vector<int>(N + 1, 0));
	depth[1] = 1;
	sparseT[0][1] = 0; // 안해도 됨
	q.push(1);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (Edge& e : graph[curr]) {
			if (depth[e.to]) continue;
			sparseT[0][e.to] = curr; // parent
			depth[e.to] = depth[curr] + 1;
			sparseTMin[0][e.to] = sparseTMax[0][e.to] = e.cost;
			q.push(e.to);
		}
	}

	for (int jump = 1; jump < MAXSTEP; ++jump) { // ( 1 << 17 = 131072)
		for (int n = 1; n <= N; ++n) {
			sparseT[jump][n] = sparseT[jump - 1][sparseT[jump - 1][n]];
			sparseTMin[jump][n] = min(sparseTMin[jump - 1][sparseT[jump - 1][n]], sparseTMin[jump - 1][n]);
			sparseTMax[jump][n] = max(sparseTMax[jump - 1][sparseT[jump - 1][n]], sparseTMax[jump - 1][n]);
		}
	}

	int K;
	cin >> K; // DFS(N) * K => (100'000) * (100'000) => TLE
	// DFS말고 logN만에 가능하도록 해야 함.
	// => sparse table 이용해야 함. (혹은 다른 방법이나..)
	while (K--) {
		int a, b;
		cin >> a >> b;
		if (depth[a] > depth[b]) swap(a, b);

		int minW = MAX, maxW = MIN;
		int diff = depth[b] - depth[a];
		for (int d = 0; diff != 0; diff >>= 1, ++d) {
			if (diff & 1) {
				minW = min(minW, sparseTMin[d][b]);
				maxW = max(maxW, sparseTMax[d][b]);
				b = sparseT[d][b];
			}
		}

		while (a!=b) {
			int d;
			for (d = 0; d < MAXSTEP; ++d) {
				if (sparseT[d][a] == sparseT[d][b]) break;
			}
			if (d) d--;
			minW = min(minW, sparseTMin[d][a]);
			minW = min(minW, sparseTMin[d][b]);
			maxW = max(maxW, sparseTMax[d][a]);
			maxW = max(maxW, sparseTMax[d][b]);
			a = sparseT[d][a];
			b = sparseT[d][b];
		}

		cout << minW << ' ' << maxW << '\n';
	}
	return 0;
}