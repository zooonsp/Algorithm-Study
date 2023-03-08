// 마을의 수 N : [4, 8]
// 유권자 수 Pi : [1, 20]
// 양방향 간선
// 모든 마을들은 서로 인접하거나 인접한 마을을 통해 연결되어 있음.


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct UnionFind {
	vector<int> par;

	UnionFind(int n) : par(n, -1) {}

	int Find(int a) {
		if (par[a] == -1) return a;
		return par[a] = Find(par[a]);
	}

	void Union(int a, int b) {
		a = Find(a);
		b = Find(b);

		if (a == b) return;

		par[b] = a; // a 밑 b
	}
};


vector<vector<int>> am; // adjency matrix
struct edge {
	int from;
	int to;
	edge(int f, int t) : from(f), to(t) {}
};

int N{};
int ans{};
int peopleSum{};
vector<edge> edges;
vector<int> peoples;
vector<int> edgeSelected;

inline int Abs(int s1, int s2) {
	return s1 - s2 <= 0 ? s2 - s1 : s1 - s2;
}

// now - 현재 edge에 대해 union 여부 결정
void dfs(int now, UnionFind uf, int groupCnt) {
	if (now == edges.size()) {

		if (groupCnt != N - 2) return; // 그룹 개수가 2개가 아니면 볼 필요 없음

		int firstIndex = -1;
		int firstSum{};
		for (int i = 0; i < N; ++i) {
			int parIndex = uf.Find(i);
			if (firstIndex == -1 || parIndex == firstIndex) { // firstIndex와 같은 애들만 누적
				firstIndex = parIndex;
				firstSum += peoples[i];
			}
		}

		ans = min(ans, Abs(peopleSum-firstSum, firstSum)); // 답 갱신
		return;
	}
	
	// 의미 없음(묶든 안 묶든)
	if(uf.Find(edges[now].to) == uf.Find(edges[now].from)) return;

	// 현재 edge union하지 x
	dfs(now + 1, uf, groupCnt);

	if (groupCnt == N - 2) return; // 더 이상 할 필요 없음
	// 현재 edge union
	vector<int> origin(begin(uf.par), end(uf.par)); // 복구용

	uf.Union(edges[now].to, edges[now].from); 
	dfs(now + 1, uf, groupCnt+1);
	uf.par.assign(begin(origin), end(origin));
}

int main() {
	int T;
	cin >> T;
	for (int tc{ 1 }; tc <= T; ++tc) {
		// reset
		edges.clear();
		peoples.clear();
		edgeSelected.clear();
		ans = static_cast<int>(21e8);
		peopleSum = 0;

		// input
		cin >> N; // 마을 개수
		edges.reserve(N * N);
		am = vector<vector<int>>(N, vector<int>(N, 0));
		for (int i = 0; i < N;++i) {
			for (int j = 0; j < N;++j) {
				cin >> am[i][j];
				if (!am[i][j]) continue; // 0
				if (i < j) { // upper triangle
					edges.push_back(edge(i, j));
				}
			}
		}
		edgeSelected.assign(edges.size(), 0);

		peoples.assign(N, 0);
		for (int& p : peoples) {
			cin >> p;
			peopleSum += p; // 답 갱신을 위해 더해놓음.
		}

		// solve
		UnionFind uf(N); // 0 ~ N
		dfs(0, uf, 0);

		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}
