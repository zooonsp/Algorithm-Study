#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int N;	// N: 정점의 수
std::vector<int> v[100'001];	// v[i]: i 정점과 연결된 정점 번호
bool visited[100'001];	// visited[i]: 연결된 간선 true
std::vector<int> sparseTable[100'001];

int M;	// M: 공통 조상을 알고 싶은 쌍의 개수
std::vector<std::pair<int, int>> AB;	// AB[i]: first와 second의 공통 조상을 알고싶은 i 번째 상

int bs(int A, int B) {	// A, B: 정점 A와 정점 B의 공통 조상 찾기
	int left = 0;	// left: 루트에서 가장 먼 정점
	int right = sparseTable[A].size() - 1;	// right: 루트 정점
	int rtn = 1;	// rtn: 공통 조상

	while (left <= right) {
		int mid = (left + right) / 2;	// mid: 이진 탐색할 정점의 깊이

		if (sparseTable[A][mid] == sparseTable[B][mid]) {	// 두 정점이 같은 값을 갖으면
			rtn = sparseTable[A][mid];	// 공통 조상 갱신
            if(left == right) return rtn;	// 최소 공통 조상
			right = mid - 1;	// 루트와 더 먼 공통 조상 찾기
            
		}
		else {
			left = mid + 1;	// 두 정점이 다른 값을 갖기 때문에 공통 조상은 루트와 더 가까움
		}
	}

	return rtn;
}

void LCA() {

	for (int i = 0; i < M; i++) {
		// nodeA, nodeB: 공통 조상을 찾을 정점
		int nodeA = AB[i].first;
		int nodeB = AB[i].second;

		int depth = std::min(sparseTable[nodeA].size(), sparseTable[nodeB].size());	// depth: 두 정점의 깊이 중 더 작은 깊이를 기준으로 삼음

		nodeA = sparseTable[nodeA][sparseTable[nodeA].size() - depth];
		nodeB = sparseTable[nodeB][sparseTable[nodeB].size() - depth];

		std:: cout << bs(nodeA, nodeB) << std::endl;		
	}

	return;
}

void findParent() {
	std::queue<int> q;	// q: 탐색할 정점

	// 루트는 1
	q.push(1);
	visited[1] = true;
	sparseTable[1].push_back(1);

	while (!q.empty()) {
		int cur = q.front();	// cur: 탐색할 정점
		q.pop();

		int edgeNum = v[cur].size();	// cur 정점과 연결되어있는 간선의 수
		for (int i = 0; i < edgeNum; i++) {
			int next = v[cur][i];	// next: cur 정점과 연결되어있는 정점
			
			if (visited[next] == true) continue;	// 이미 연결 정보를 확인했다면 continue

			visited[next] = true;
			sparseTable[next].push_back(next);
			std::vector<int>::iterator it = sparseTable[next].insert(sparseTable[next].end(), sparseTable[cur].begin(), sparseTable[cur].end());	// 현재 노드에서 루트까지의 경로 저장
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
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

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