/*
https://mapocodingpark.blogspot.com/2020/03/BOJ3665.html 참고.
모든 정점 간에 간선이 생성됨. => 팀의 수가 maximum 500
Adjacency Matrix로 edge 정보 만들어도 괜찮음.
- 팀의 개수가 그렇게 많지 않음.
- matrix로 구성해도 절반을 무조건 채움.

만약, 확실한 순위를 찾을 수 없다면 "?"를 출력 => 그런 경우가 없다..
3068KB, 36ms
*/
#include <bits/stdc++.h>
// iostream, vector, queue

using namespace std;

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> teams(n, 0);
		for (int& t : teams) {
			cin >> t;
		}
		vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
		vector<int> indegree(n + 1, 0);

		// 기존 간선 만들기
		for (int i{}; i < n; ++i) {
			for (int j{ i + 1 }; j < n; ++j) {
				adj[teams[i]][teams[j]] = 1; 
				indegree[teams[j]]++;
			}
		}

		// 정보 - 기존 간선 바꾸기
		int m; 
		cin >> m;
		for (int i{}; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			if (adj[a][b]) {
				swap(a, b);
			}
			adj[b][a] = false;
			adj[a][b] = true;
			indegree[a]--;
			indegree[b]++;
		}

		queue<int> Q;
		for (int i{ 1 }; i <= n; ++i) {
			if (indegree[i] == 0)Q.push(i);
		}

		vector<int> answer;
		while(!Q.empty()) { // 무조건 N번
			int now = Q.front(); Q.pop();
			answer.push_back(now);
			
			for (int next{ 1 }; next <= n; ++next) {
				if (adj[now][next]) {
					indegree[next]--;
					if (indegree[next] == 0) Q.push(next);
				}
			}
		}
		if ((int)answer.size() == n) {
			for (int& a : answer) cout << a << ' ';
			cout << '\n';
		}
		else {
			cout << "IMPOSSIBLE\n";
		}
	}

	return 0;
}
