#include <iostream>
#include <queue>

using namespace std;

int arr[501][501];


int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;

	while (T--) {
		// n = 팀의 수, m = 상대적으로 등수가 바뀐 팀의 쌍 수
		int n, m;
		cin >> n;

		// 인덱스 번호가 등수인 배열
		int index_rank[501] = { 0 };

		// 인덱스가 팀 이름이고, 도달하기 위한 개수(??)
		int indegree[501] = { 0 };

		for (int i = 1; i <= n; i++)
		{
			cin >> index_rank[i];

			// 입력 받으면서 동시에 arr 2차원 배열 초기화
			for (int j = 1; j <= n; j++) {
				arr[i][j] = 0;
			}
		}

		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j <= n; j++) {
				// 1등 -> 2등,,, n등
				// 2등 -> 3등,, n등
				// n - 1등 -> n등
				arr[index_rank[i]][index_rank[j]] = 1;
				indegree[index_rank[j]]++;
			}
		}

		cin >> m;

		while (m--) {
			int a, b;
			cin >> a >> b;

			// a가 b보다 순위가 더 높을 때!
			if (arr[a][b] == 1) {
				// a의 순위가 b보다 낮아짐
				arr[a][b] = 0;
				arr[b][a] = 1;

				indegree[a]++;
				indegree[b]--;
			}

			// 반대일 때
			else {
				arr[a][b] = 1;
				arr[b][a] = 0;

				indegree[a]--;
				indegree[b]++;
			}
		}

		queue<int> q;
		queue<int> ans;
		int ipflag = 0;

		for (int team = 1; team <= n; team++) {
			// 말단 노드 탐색
			if (indegree[team] == 0) q.push(team);
		}

		while (!q.empty()) {
			// 말단 노드가 2개로 시작하면 어우 쉣
			if (q.size() >= 2) {
				ipflag = 1;
				break;
			}

			int now = q.front();
			q.pop();
			ans.push(now);

			for (int next = 1; next <= n; next++) {
				if (arr[now][next] == 1) {
					// 다음 등수로 갈 준비가 되었다면
					if (--indegree[next] == 0) {
						q.push(next);
					}
				}
			}
		}

		if (ipflag) {
			cout << "?\n";
			continue;
		}

		if (ans.size() != n) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		else {
			while (!ans.empty()) {
				cout << ans.front() << ' ';
				ans.pop();
			}
			cout << '\n';
		}

	}
	return 0;
}
