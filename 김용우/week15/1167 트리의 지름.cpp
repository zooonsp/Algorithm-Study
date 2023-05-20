#include <iostream>
#include <vector>

struct Edge {
	int to;	// to: 연결되어 있는 노드
	int length;	// length: 연결되어 있는 노드까지의 간선의 길이
};

int V;	// V: 노드의 개수
int E; // E: 간선의 개수
std::vector<Edge> v[100'001];	// v[i]: i 노드와 연결된 노드의 번호와 루트부터의 간선의 길이 (단방향)
std::vector<Edge> linked[100'001];	// linked[i]: i 노드와 연결된 노드의 번호와 연결된 두 노드간의 간선의 길이 (양방향)
bool visited[100'001];	// visited[i]: i 노드 방분 체크

int maxLength, maxLengthNodeNum;	// maxLength: 루트부터 가장 먼 거리 값, maxLengthNodeNum: 루트부터 가장 거리가 먼 노드 번호
int ans;	// ans: 트리의 지름

void DFS2(int nodeNum, int length) {	// nodeNum: 현재 노드 번호, length: 현재 노드 까지의 거리

	for (int i = 0; i < linked[nodeNum].size(); i++) {
		Edge cur = { nodeNum, length };	// cur: 현재 노드의 번호와 가장 거리가 먼 노드부터의 간선의 길이
		Edge next = linked[nodeNum][i];	// next: 다음 노드의 번호와 간선의 길이

		if (visited[next.to] != false) continue;	// 이미 확인한 노드면 continue

		visited[next.to] = true;	// 방문 체크

		next.length = cur.length + next.length;	// 가장 거리가 먼 노드부터의 간선의 길이 갱신
		linked[nodeNum][i].length = next.length;

		if (ans < next.length) {	// 길이가 더 먼 간선의 거리가 발견된다면
			ans = next.length;
		}

		DFS2(next.to, next.length);	}
	
	return;
}

void calEdgeLength() {

	for (int i = 0; i <= V; i++)
		visited[i] = false;	// 방문 체크 초기화

	visited[maxLengthNodeNum] = true;	// 가장 거리가 먼 노드부터 시작
	DFS2(maxLengthNodeNum, 0);

	return;
}

void DFS1(int nodeNum, int length) {	// nodeNum: 현재 노드 번호, length: 현재 노드 까지의 거리

	for (int i = 0; i < v[nodeNum].size(); i++) {
		Edge cur = { nodeNum, length };	// cur: 현재 노드의 번호와 로트 노드로 부터의 간선의 길이
		Edge next = v[nodeNum][i];	// next: 다음 노드의 번호와 간선의 길이

		if (visited[next.to] != false) continue;	// 이미 확인한 노드면 continue

		visited[next.to] = true;	// 방문 체크

		next.length = cur.length + next.length;	// 루트부터의 거리 갱신
		v[nodeNum][i].length = next.length;

		if (maxLength < next.length) {	// 루트부터 가장 거리가 먼 노드의 번호와 거리 갱신
			maxLength = next.length;
			maxLengthNodeNum = next.to;			
		}

		DFS1(next.to, next.length);
	}

	return;
}

void findLongestNode() {

	visited[1] = true;	// 루트 노드 방문 체크
	DFS1(1, 0);

	return;
}

void sol() {

	// 루트 부터 가장 거리가 먼 노드 탐색
	findLongestNode();

	// 루트부터 가장 거리가 먼 노드부터 가장 거리가 먼 노드 탐색
	calEdgeLength();

	return;
}

void input() {
	std::cin >> V;

	for (int i = 0; i < V; i++) {
		int from;	// from: 노드 번호
		std::cin >> from;
		while (true) {
			int to, length;	// to: 연결되어 있는 노드 번호, length: 연결되어 있는 노드와의 간선의 길이
			std::cin >> to;

			if (to == -1) break;	// -1 이면 break

			std::cin >> length;
			E++;

			v[from].push_back({ to, length });

			linked[from].push_back({ to, length });
			linked[to].push_back({ from, length });	// 양방향
		}
	}

	return;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	std::cout << ans;

	return 0;
}