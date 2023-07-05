/*
1번 문제가 가장 쉬운 문제이고 N번 문제가 가장 어려운 문제가 된다
다음의 세 가지 조건에 따라 문제를 풀 순서를 정하기로 하였다
	N개의 문제는 모두 풀어야 한다.
	먼저 푸는 것이 좋은 문제가 있는 문제는, 먼저 푸는 것이 좋은 문제를 반드시 먼저 풀어야 한다.
	가능하면 쉬운 문제부터 풀어야 한다.
3944KB, 32ms
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int N, M;  // 문제 수, 정보 개수
	cin >> N >> M;
	vector<int> indegrees(N + 1, 0); // 1 ~ N
	vector<vector<int>> graph(vector<vector<int>>(N + 1));
	// 항상 문제를 모두 풀 수 있는 경우만 입력으로 주어진다.
	for (int m = 0; m < M; ++m) {
		int a, b; // a가 b보다 앞서야 한다.
		cin >> a >> b;
		indegrees[b]++;
		graph[a].emplace_back(b);
	}

	// 이후 들어오는 문제에 대해서도 더 쉽다면 앞으로 가도록 pq
	priority_queue<int, vector<int>, greater<int>> q;
	for (int n = 1; n <= N;++n) {
		if (indegrees[n] == 0) q.push(n);
	}

	while (!q.empty()) {
		int now = q.top(); q.pop();
		cout << now << ' ';
		for (int& next : graph[now]) {
			indegrees[next]--;
			if (indegrees[next] == 0) q.push(next);
		}
	}
	cout << '\n';

	return 0;
}