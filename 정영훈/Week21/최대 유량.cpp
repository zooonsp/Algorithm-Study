// https://m.blog.naver.com/kks227/220804885235 참고
// Ford-Fulkerson

#include <bits/stdc++.h>

using namespace std;
constexpr int SIZE = 52; // 0 ~ 51
constexpr int START = 0; // A
constexpr int GOAL = 25; // Z
constexpr int INF = 1 << 30;

bitset<SIZE> visited;

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

int fodfs(int v, int t, int f) {
	if (v == t) return f; // 도달

	visited[v] = 1;
	for (Edge* e : graph[v]) {
		if (visited[e->to]) continue; // 이미 감

		int remain = e->RemainCap();
		if (remain == 0) continue; // 남은 cap 확인

		int flow = fodfs(e->to, t, min(f, remain));

		if (flow == 0) continue;

		e->AddFlow(flow); // flow 만큼 흘리기

		return flow; // s - t path
	}
	return 0; // not find
}

int CharToInt(char c) {
	if (c & ' ') return c - 'a' + 26;
	else return c - 'A';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N;
	cin >> N;

	graph.assign(SIZE, vector<Edge*>()); // 존재하는 간선만을 인접 리스트로 저장

	for (int n = 0; n < N; ++n) {
		char cA, cB;
		int a,b,f;
		cin >> cA >> cB >> f;
		a = CharToInt(cA);
		b = CharToInt(cB);
		Edge *ori = new Edge(b, f), *rev = new Edge(a, f); // 앙방향 그래프임..
		ori->dual = rev;
		rev->dual = ori;
		graph[a].push_back(ori);
		graph[b].push_back(rev);
	}

	int answer = 0;
	while (1) {
		visited.reset();
		int flow = fodfs(START, GOAL, INF);

		if (flow == 0) break;
		answer += flow;
	}
	cout << answer << '\n';

	return 0;
}