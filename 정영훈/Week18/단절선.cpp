/*
https://m.blog.naver.com/kks227/220802704686
http://bowbowbow.tistory.com/3
단절선 찾기. => 다른 우회로가 있는지 없는지
15044KB, 180ms
*/

#include <bits/stdc++.h>
// vector, algorithm, iostream, utility

using namespace std;
using pii = pair<int, int>;

vector<vector<int>> graph;
vector<int> visited;
int visitIndex;
vector<pii> answer;

int DFS(int curr, int prev = -1) {
	visited[curr] = ++visitIndex; // 1부터 시작
	int ret = visited[curr];

	for (int& next : graph[curr]) {
		if (prev == next) continue; // 단절점에서는 >= 비교여서 빼도 되지만 (단절선에서는 필요함)
		if (visited[next]) ret = min(ret, visited[next]);
		else { // 새로 방문
			int temp = DFS(next, curr);
			ret = min(ret, temp);
			if (temp > visited[curr]) { // 등호 포함하면 틀림. (현재 정점 다음 정점이어야 함)
				// curr을 통해서만 갈 수 있는 점이 있다는 뜻임.
				answer.emplace_back(min(curr, next), max(curr, next)); // 단절선 출력 ( A < B 를 만족하도록 간선 출력)
			}
		}
	}
	
	return ret;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int V, E;
	cin >> V >> E;
	const int SIZE = V + 1;
	graph = vector<vector<int>>(SIZE); // 1 ~ V
	visited = vector<int>(SIZE, 0);
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

	sort(begin(answer), end(answer)); //  단절선을 사전순으로 한 줄에 하나씩 출력한다
	// pair - operator< => first 먼저 비교하고 second 비교함
	
	cout << answer.size() << '\n'; // 단절선의 개수
	for (auto& a : answer) {
		cout << a.first << ' ' << a.second << '\n';
	}

	return 0;
}