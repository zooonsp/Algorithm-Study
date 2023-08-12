// 이분 매칭 - Network Flow로 바꿔서..
// Ford-Fulkerson
/*
축사를 M개의 칸으로 구분하고, 한 칸에는 최대 한 마리의 소만 들어가게 계획
SRC(0) -> 소들(1~N(<=200)) -> 축사(201~201+M(<=400)) -> SINK(401))
SRC -> 소 : cap = 1 (한 마리만 존재)
소 -> 축사 : cap = INF(값 상관 없음)
축사 -> SINK : cap = 1 (한 마리만 들어 갈 수 있음)
3476KB, 4ms
*/

#include <bits/stdc++.h>

using namespace std;

constexpr int SIZE = 450;
constexpr int INF = 1 << 29;
constexpr int BARN = 200;
constexpr int SRC = 0;
constexpr int SINK = 401;

bitset<SIZE> visited; // 널널하게

struct Edge {
	int to, c, f;
	Edge* dual;
	Edge() : Edge(-1, 0) {}
	Edge(int to, int c, int f = 0) : to(to), c(c), f(f), dual(nullptr) {}
	int RemainCap() { // 현재 간선의 여유 용량
		return c - f;
	}
	void AddFlow(int flow) {  // flow만큼 흘려주기
		f += flow;
		dual->f -= flow;
	}
};
vector<vector<Edge*>> graph;

int FordFulkerson(int v, int t, int f) {
	if (v == t) return f;
	visited[v] = 1;

	for (auto e : graph[v]) { // Edge*
		if (visited[e->to]) continue;

		int remain = e->RemainCap();
		if (remain == 0) continue;

		int flow = FordFulkerson(e->to, t, min(f, remain));
		if (flow == 0) continue;
		e->AddFlow(flow);
		return flow;
	}
	return 0;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // 소의 수, 축사의 수
	// 각 소가 들어가기 원하는 축사에 대한 정보

	graph.assign(SIZE, vector<Edge*>()); // 존재하는 간선만을 인접 리스트로 저장

	for (int n = 1; n <= N; ++n) {
		int S;
		cin >> S; // n번째 소가 들어가길 원하는 축사 개수

		// SRC(0) -> 소(n)
		Edge *ori = new Edge(n, 1), *rev = new Edge(0, 0); 
		ori->dual = rev;
		rev->dual = ori;
		graph[0].push_back(ori); // SRC -> n (진짜 간선, cap = 1)
		graph[n].push_back(rev); // n -> SRC (가상, cap = 0)

		for (int s{}; s < S; ++s) {
			int a; // 축사 번호
			cin >> a;
			a += BARN;

			// 소(n) -> 축사(a)
			Edge *ori = new Edge(a, INF), *rev = new Edge(n, 0);
			ori->dual = rev;
			rev->dual = ori;
			graph[n].push_back(ori); // SRC -> n (진짜 간선, cap = INF)
			graph[a].push_back(rev); // n -> SRC (가상, cap = 0)
		}
	}

	for (int m = 1; m <= M; ++m) {
		// 축사(BARN + m) -> SINK(N+M+1)
		int barnIdx = BARN + m;
		Edge *ori = new Edge(SINK, 1), *rev = new Edge(barnIdx, 0);
		ori->dual = rev;
		rev->dual = ori;
		graph[barnIdx].push_back(ori); // SRC -> n (진짜 간선, cap = 1)
		graph[SINK].push_back(rev); // n -> SRC (가상, cap = 0)
	}

	int answer{};

	while (1) {
		visited.reset();
		int flow = FordFulkerson(SRC, SINK, INF);
		if (flow == 0) break;
		answer += flow;
	}

	cout << answer << '\n';

	return 0;
}