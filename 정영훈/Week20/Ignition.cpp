/*
그래프를 최대한 빠른 시간 안에 전부 태우고 싶어한다.
서훈이를 도와 어떤 정점에 불을 붙일지 구하는 프로그램을 작성
2444KB, 36ms
*/

#include <bits/stdc++.h>
// vector, iostream, climits(INT_MAX), cstring(memset)

using namespace std;
struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
constexpr int MAXV = 201;
int mat[MAXV][MAXV]{};

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	int N, M; // 정점 수, 간선 수
	cin >> N >> M;
	
	vector<vector<Edge>> graph(N + 1);
	memset(mat, 60,sizeof(mat)); // 10억 쯤
	for (int n{ 1 }; n <= N; ++n) {
		mat[n][n] = 0;
	}

	for (int m{}; m < M; ++m) {
		int a, b, length;
		cin >> a >> b >> length;
		mat[a][b] = min(mat[a][b], length);
		mat[b][a] = min(mat[b][a], length);
		graph[a].emplace_back(b, length);
		// graph[b].push_back({ a, length });
	}

	// Floyd - Warshall
	for (int k{ 1 }; k <= N; ++k) {
		for (int i{ 1 }; i <= N; ++i) {
			for (int j{ 1 }; j <= N; ++j) {
				mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
			}
		}
	}

	double answer = static_cast<double>(INT_MAX);
	for (int s{ 1 }; s <= N; ++s) {
		double nowAnswer{ -1 };

		for (int n{ 1 }; n <= N; ++n) {
			for (Edge& e : graph[n]) { // to, weight
				// n-> e.to
				int first{ n }, second{ e.to };
				if (mat[s][first] > mat[s][second]) {
					swap(first, second);
				}
				double time = mat[s][first] + (mat[s][second] - mat[s][first]) + static_cast<double>(e.weight - mat[s][second] + mat[s][first]) / 2;
				nowAnswer = max(nowAnswer, time);
			}
		}
		answer = min(answer, nowAnswer);
	}

	cout << fixed;
	cout.precision(1);
	cout << answer << '\n';

	return 0;
}