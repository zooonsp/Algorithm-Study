#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> v[32323];
int check[32323];
int visited[32323];

// 쉬운 문제부터 풀어야함(오름차순 정렬)
priority_queue<int, vector<int>, greater<int>> pq;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i{}; i < m; i++) {
		int a, b;
		cin >> a >> b;

		// a번 문제는 b번 문제보다 먼저 풀어야 함!
		v[a].push_back(b);

		// b를 풀기 위한 선행학습 친구들 cnt 해주기!
		check[b]++;
	}

	// 선행학습할 친구들이 없는 친구들을 우선순위 큐에 넣기!
	for (int i = 1; i <= n; i++) {
		if (check[i] == 0) pq.push(i);
	}

	while (!pq.empty()) {
		int now = pq.top();

		// 먼저 풀어야하는 것 출력!
		cout << now << " ";
		pq.pop();

		// 출력했으니깐 체크
		visited[now] = 1;

		if (v[now].size() == 0) continue;

		for (int i{}; i < v[now].size(); i++) {
			// 선행학습 완료!
			check[v[now][i]]--;
			if (check[v[now][i]] == 0) {

				// 다음 학습으로 넘어갈 수 있음
				pq.push(v[now][i]);
			}
		}
	}
	return 0;
}
