#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
	int from, to;	// from, to: from 정점과 to 정점이 연결되어 있음
	int tmp;	// tmp: 두 정점의 간선 온도
};

int n, m, Q;	// n: 점점의 개수, m: 간선의 개수, Q: 쿼리의 개수
int parent[100001];	// parent[i]: i 정점의 부모 정점 번호
int size[100001];	// size[i]: i 정점과 연결되어있는 정점의 수
std::vector<Edge> v;	// v[i]: i 정점과 연결되어 있는 간선 정보
std::pair<int, int> query[100001];	// query[i]: i 번째 쿼리의 두 정점
std::pair<int, int> ans[100001];	// ans[i]: i 번째 쿼리를 실행하였을 때의 결과 -> 경로가 없을 경우 -1

int Find(int now) {	// now: 소속을 알고 싶은 정점
	if (parent[now] == now) return now;
	return parent[now] = Find(parent[now]);
}

void Union(int A, int B) {	// A, B: 연결하고자 하는 두 정점
	int pa = Find(A);	// pa: A 정점의 소속
	int pb = Find(B);	// pb: B 정점의 소속

	if (pa == pb) return;;

	parent[pa] = pb;
	size[pb] += size[pa];	// 소속을 합치면서 연결 개수도 갱신

	return;
}

bool cmp(Edge left, Edge right) {	// left, right: left 간선과 right 간선을 온도 순서 오름차순 정렬
	if (left.tmp < right.tmp) return true;
	if (left.tmp > right.tmp) return false;

	return false;
}

void sol() {

	for (int i = 1; i <= n; i++) {	// 소속 정보 초기화
		parent[i] = i;
		size[i] = 1;
	}

	std::sort(v.begin(), v.end(), cmp);	// 간선의 온도를 기준으로 오름차순 정렬

	for (int i = 0; i < m; i++) {
		Edge cur = v[i];	// cur: 연결하고자 하는 간선 정보

		if (Find(cur.from) == Find(cur.to)) continue;	// 이미 연결되어 있다면 continue

		Union(cur.to, cur.from);	// 두 정점을 cur 간선으로 연결

		for (int j = 0; j < Q; j++) {
			if (ans[j].first != 0) continue;	// 이미 질의가 완료된 쿼리는 continue

			int from, to;	// from, to: 연결 여부를 확인하고자 하는 두 정점
			from = query[j].first;
			to = query[j].second;

			if (Find(from) != Find(to)) continue;	// 두 정점이 같은 소속이 아니면 continue -> 두 정점이 연결되어 있지 않음

			ans[j].first = cur.tmp;
			ans[j].second = size[Find(to)];
		}
	}

	return;
}

void input() {
	std::cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from, to, tmp;	// from, to: 연결되어 있는 두 정점, tmp: 두 정점을 연결하는 간선의 온도
		std::cin >> from >> to >> tmp;
		v.push_back({ from, to, tmp });
	}
	std::cin >> Q;
	for (int i = 0; i < Q; i++) {
		int from, to;	// from, to: 연결 여부를 확인하고자 하는 두 정점
		std::cin >> from >> to;
		query[i] = { from, to };
	}

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	for (int i = 0; i < Q; i++) {
		if (ans[i].first != 0)
			std::cout << ans[i].first << ' ' << ans[i].second << '\n';
		else
			std::cout << "-1\n";	// 두 정점이 연결되어 있지 않음
	}

	return 0;
}