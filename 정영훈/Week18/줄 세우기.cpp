/*
N명의 학생들을 키 순서대로 줄 세우기.
일부 학생들의 키를 비교한 결과가 주어졌을 때, 줄을 세우는 프로그램 작성하기. => Topological sort
3944KB, 36ms
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int N, M;  // 학생 수, 비교 횟수
	cin >> N >> M;
	vector<int> indegrees(N + 1, 0); // 1 ~ N
	vector<vector<int>> graph(vector<vector<int>>(N + 1));
	for (int m = 0; m < M; ++m) {
		int a, b; // a가 b보다 앞서야 한다.
		cin >> a >> b;
		indegrees[b]++;
		graph[a].emplace_back(b);
	}

	queue<int> q;
	for (int n = 1; n <= N;++n) {
		if (indegrees[n] == 0) q.push(n);
	}

	while (!q.empty()) {
		int now = q.front(); q.pop();
		cout << now << ' ';
		for (int& next : graph[now]) {
			indegrees[next]--;
			if (indegrees[next] == 0) q.push(next);
		}
	}
	cout << '\n';

	return 0;
}