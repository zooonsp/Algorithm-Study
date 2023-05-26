#include <iostream>
#include <vector>
#include <algorithm>

struct Loc {
	int coordinate, planetNum;	// coordinate: 행성 위치, plantNum: 행성 번호
};

struct Edge {
	int from, to, distance;	// from: 출발 행성, to: 도착 행성, distance: 출발 행성과 도착 행성 간의 거리
};

int N;	// N: 행성의 개수
std::vector<Loc> xLoc, yLoc, zLoc;	// xLoc, yLoc, zLoc: 각 좌표에 해당하는 행성의 위치와 번호
std::vector<Edge> edge;	// edge: 두 행성의 번호와 두 행성 간의 한 좌표에 해당하는 거리
int parent[100'001];	// parent[i]: 행성의 소속 정보
int totalCost;	// totalCost: 모든 행성을 터널로 연결하는데 필요한 최소 비용

int Find(int now) {	// now: 소속을 찾을 행성 번호
	if (parent[now] == now) return now;
	return parent[now] = Find(parent[now]);
}

void Union(int A, int B) {	// A, B: 하나의 소속으로 합칠 두 행성의 번호
	// pa, pb: 두 행성의 소속
	int pa = Find(A);
	int pb = Find(B);

	if (pa == pb) return;

	parent[pa] = pb;

	return;
}

bool cmp2(Edge left, Edge right) {	// 두 행성 사이의 거리를 기준으로 오름차순
	
	if (left.distance != right.distance) return left.distance < right.distance;

	return false;
}

bool cmp1(Loc left, Loc right) {	// 한 좌표를 기준으로 오름차순

	if (left.coordinate != right.coordinate) return left.coordinate < right.coordinate;

	return false;
}

void calDistance(std::vector<Loc> &v) {

	for (int i = 0; i < N - 1; i++) {
		int from, to, distance;	// from, to: 연결할 두 행성, distance: 두 행성간의 거리

		from = v[i].planetNum;
		to = v[i + 1].planetNum;
		distance = v[i + 1].coordinate - v[i].coordinate;	// 거리를 기준으로 오름차순 정렬하였기 때문에 항상 양의 값을 갖음

		edge.push_back({ from, to, distance });
	}	

	return;
}

void sol() {

	// 각 좌표에 대하여 오름차순 정렬 -> 정렬된 값에서의 최소 거리는 i + 1 번째 행성과 i 번째 행성에서 구할 수 있음
	std::sort(xLoc.begin(), xLoc.end(), cmp1);
	std::sort(yLoc.begin(), yLoc.end(), cmp1);
	std::sort(zLoc.begin(), zLoc.end(), cmp1);

	// 각 좌표에서 최소거리가 나오는 조건은 정렬 후, 다음 행성의 거리와 연결하는 것이 최소 거리
	calDistance(xLoc);
	calDistance(yLoc);
	calDistance(zLoc);

	// 두 행성간의 거리를 기준으로 오름차순 정렬
	std::sort(edge.begin(), edge.end(), cmp2);

	for (int i = 0; i < N; i++) parent[i] = i;	// 소속 정보 초기화

	for (int i = 0; i < edge.size(); i++) {
		Edge cur = edge[i];	// cur: 최소 스패팅 트리를 적용할 행성들의 번호와 거리 정보
		if (Find(cur.from) == Find(cur.to)) continue;	// 이미 같은 소속이면 continue

		Union(cur.from, cur.to);	// 하나의 소속으로 연결

		totalCost += cur.distance;	// 비용 추가
	}

	return;
}

void input() {

	std::cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y, z;	// x, y, z: 행성의 위치 좌표
		std::cin >> x >> y >> z;

		// 두 행성의 거리는 각 좌표의 최소 거리이므로 서로 다른 벡터에 추가
		xLoc.push_back({ x, i });
		yLoc.push_back({ y, i });
		zLoc.push_back({ z, i });
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << totalCost;

	return 0;
}