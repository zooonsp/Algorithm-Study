#include <iostream>
#include <vector>
#include <queue>

int N;	// N: 정점의 수
std::vector<int> v[50'001];	// v[i]: i 정점과 연결된 정점 번호
bool visited[50'001];	// visited[i]: 연결된 간선 true
int depth[50'001];	// depth[i]: i 정점의 깊이, 0 ~ 
int parent[50'001];	// patent[i]: i 정점의 부모 번호

int M;	// M: 공통 조상을 알고 싶은 쌍의 개수
std::vector<std::pair<int, int>> AB;	// AB[i]: first와 second의 공통 조상을 알고싶은 i 번째 상

void LCA() {

	for (int i = 0; i < M; i++) {
		// nodeA, nodeB: 공통 조상을 찾을 정점
		int nodeA = AB[i].first;
		int nodeB = AB[i].second;

		// nodeA의 depth를 nodeB의 depth보다 크거나 같도록 설정
		if (depth[nodeA] < depth[nodeB])
			std::swap(nodeA, nodeB);

		// nodeA와 nodeB의 depth를 같게 함 -> nodeA의 부모를 타고 올라감
		while (depth[nodeA] != depth[nodeB]) {
			nodeA = parent[nodeA];
		}

		// nodeA와 nodeB가 같아질 때 까지 부모 찾음
		while (nodeA != nodeB) {
			nodeA = parent[nodeA];
			nodeB = parent[nodeB];
		}

		std::cout << nodeA << std::endl;	// 공통 조상 출력
	}
}

void findParent() {
	std::queue<int> q;	// q: 탐색할 정점

	// 루트는 1
	q.push(1);
	visited[1] = true;
	depth[1] = 0;	// 1번 정점의 깊이는 0으로 설정
	parent[1] = 1;

	while (!q.empty()) {
		int cur = q.front();	// cur: 탐색할 정점
		q.pop();

		int edgeNum = v[cur].size();	// cur 정점과 연결되어있는 간선의 수
		for (int i = 0; i < edgeNum; i++) {
			int next = v[cur][i];	// next: cur 정점과 연결되어있는 정점
			
			if (visited[next] == true) continue;	// 이미 연결 정보를 확인했다면 continue

			int nextDepth = depth[cur] + 1;	// nextDepth: next 정점의 깊이
			int nextParent = cur;	// nextParent: next 정점의 부모 cur

			visited[next] = true;
			depth[next] = nextDepth;
			parent[next] = nextParent;
			q.push(next);
		}
	}

	return;
}

void sol() {
	// 연결 정보 탐색
	findParent();

	// 가장 가까운 공통 조상 출력
	LCA();

	return;
}

void input() {
	std::cin >> N;

	for (int i = 0; i < N - 1; i++) {
		int nodeA, nodeB;	// nodeA, nodeB: 연결할 두 정점
		std::cin >> nodeA >> nodeB;
		v[nodeA].push_back(nodeB);
		v[nodeB].push_back(nodeA);	// 양방향 연결
	}

	std::cin >> M;
	for (int i = 0; i < M; i++) {
		int nodeA, nodeB;	// nodeA, nodeB: 가장 가까운 공통 조상을 찾을 두 정점
		std::cin >> nodeA >> nodeB;
		AB.push_back({ nodeA, nodeB });
	}

	return;
}

int main() {
	input();
	sol();

	return 0;
}