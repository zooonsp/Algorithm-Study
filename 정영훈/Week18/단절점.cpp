/*
https://m.blog.naver.com/kks227/220802704686
http://bowbowbow.tistory.com/3
단절점 찾기. => 다른 우회로가 있는지 없는지
정점 A가 루트 노드 일때
	: 자식 수가 2이상일때 절단점
정점 A가 루트 노드가 아닐 때
	: 정점 A의 자식 노드가 정점 A이전에 방문한 노드에  정점 A를 거치지 않고 도달할 수 없으면 절단점
4600KB, 24ms
*/

#include <bits/stdc++.h>
// vector, algorithm, iostream

using namespace std;

vector<vector<int>> graph;
vector<int> visited, cutVertex;
int visitIndex;

int DFS(int curr, int prev = -1) {
	visited[curr] = ++visitIndex; // 1부터 시작
	int ret = visited[curr];

	int childCnt = 0;
	for (int& next : graph[curr]) {
		// if (prev == next) continue;
		if (visited[next]) ret = min(ret, visited[next]);
		else { // 새로 방문
			int temp = DFS(next, curr);
			ret = min(ret, temp);
			++childCnt;
			if (prev != -1 && temp >= visited[curr]) {
				// curr을 통해서만 갈 수 있는 점이 있다는 뜻임.
				cutVertex[curr] = 1;
			}
		}
	}

	// root인 경우 따로 처리
	if (prev == -1 && childCnt >= 2) {
		cutVertex[curr] = 1;
	}
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph = vector<vector<int>>(SIZE); // 1 ~ V
	visited = vector<int>(SIZE, 0);
	cutVertex = vector<int>(SIZE, 0);
	for (int e = 0; e < E; ++e) {
		int a, b;
		cin >> a >> b; // 무방향
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int v = 1; v <= V; ++v) {
		if (visited[v] == 0) {
			DFS(v);
		}
	}

	vector<int> answer;
	answer.reserve(SIZE);
	for (int v = 1; v <= V; ++v) {
		if (cutVertex[v]) answer.push_back(v);
	}

	cout << answer.size() << '\n'; // 단절점의 개수
	for (int& a : answer) { //  단절점의 번호를 공백으로 구분해 오름차순으로 출력
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}