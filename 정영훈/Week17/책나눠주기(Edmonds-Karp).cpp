// 34376KB, 1724ms
/*
N : 1 ~ 1000, M : 1 ~ 1000
백준이가 책을 줄 수 있는 최대 학생 수를 구하시오.
*/

#include <bits/stdc++.h>

using namespace std;

// SRC(0) -> 학생(1 ~ 1000) -> 책(1001 ~ 2000) -> SINK(2001)

constexpr int SRC = 0;
constexpr int SINK = 2001;
constexpr int BOOK = 1000;
constexpr int SIZE = 2002;
constexpr int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int T; 
	cin >> T;
	while (T--) {
		graph = vector<vector<Edge>>(SIZE);
		int N, M;  // 책 수, 학생 수
		cin >> N >> M;
		
		for (int m = 1; m <= M; ++m) { 
			// 1. SRC -> 각 학생 연결
			int srcRev = static_cast<int>(graph[SRC].size());
			int studentRev = static_cast<int>(graph[m].size());
			graph[SRC].emplace_back(studentRev, SRC, m, 1); // cap = 1
			graph[m].emplace_back(srcRev, m, SRC, 0); // cap = 0(가상 간선)

			// 2. 각 학생 -> 선호하는 책 정점들 연결
			int a, b;
			cin >> a >> b; // a 이상 b 이하
			for (int s = a; s <= b; ++s) {
				int bookIndex = s + BOOK;
				int bookRev = static_cast<int>(graph[bookIndex].size());
				studentRev = static_cast<int>(graph[m].size());
				graph[m].emplace_back(bookRev, m, bookIndex, INF); // cap = INF(아무 값이든지 ok)
				graph[bookIndex].emplace_back(studentRev, bookIndex, m, 0); // cap = 0(가상 간선)
			}
		}

		for (int n = 1; n <= N; ++n) { // 3. 책들 -> SINK 연결
			int bookIndex = n + BOOK;
			int sinkRev = static_cast<int>(graph[SINK].size());
			int bookRev = static_cast<int>(graph[bookIndex].size());
			graph[bookIndex].emplace_back(sinkRev, bookIndex, SINK, 1); // cap = 1
			graph[SINK].emplace_back(bookRev, SINK, bookIndex, 0); // cap = 0(가상 간선)
		}

		int s = SRC, d = SINK;
		int maxFlow = 0;
		while (1) {
			vector<int> prevVisited(SIZE, -1);
			vector<int> prevVisitedIndex(SIZE, -1);

			queue<int> Q;
			Q.push(s);

			while (!Q.empty() && prevVisited[d] == -1) {
				int now = Q.front(); Q.pop();
				int index{};
				for (Edge& e : graph[now]) {
					if (e.cap > 0 && prevVisited[e.to] == -1) {
						prevVisited[e.to] = now;
						prevVisitedIndex[e.to] = index;
						Q.push(e.to);
						if (e.to == d) break;
					}
					++index;
				}
			}

			if (prevVisited[d] == -1) break;

			int flow = INF;
			for (int i{ d }; i != s; i = prevVisited[i]) {
				flow = min(flow, graph[prevVisited[i]][prevVisitedIndex[i]].cap);
			}
			for (int i{ d }; i != s; i = prevVisited[i]) {
				Edge& e = graph[prevVisited[i]][prevVisitedIndex[i]];
				e.cap -= flow;
				graph[e.to][e.rev].cap += flow;
			}
			maxFlow += flow;

		}
		
		cout << maxFlow << '\n';
	}
	
	return 0;
}