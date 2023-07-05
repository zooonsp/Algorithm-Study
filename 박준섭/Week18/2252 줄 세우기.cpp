#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> v[32323];
int visited[32323];

void dfs(int node) {
	// 출력한 학생은 패스~
	if (visited[node] == 1) return;

	// 현재 학생과 비교한 학생들에 대해서 확인
	for (int i : v[node]) {
		if (visited[i] == 0) {
			dfs(i);
		}
	}

	visited[node] = 1;
	cout << node << " ";
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i{}; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[b].push_back(a);
	}

	queue<int> q;

	for (int i = 1; i <= n; i++) {
		// 키 비교에 포함되지 않는 학생은 바로 출력해버림
		if (v[i].empty()) {
			visited[i] = 1;
			cout << i << " ";
		}
		// 키 비교 당한사람들은 Queue에 넣어준다!
		else q.push(i);
	}
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		// 출력당하지 않은 학생만 dfs 탐색
		if (visited[now] == 0) dfs(now);
	}

	return 0;
}
