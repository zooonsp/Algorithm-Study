#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 987654321;
int N;  // 마을의 수
int adj[8][8];  // 마을 연결 정보
int P[8];  // 마을의 유권자 수
int visited[8];  // 마을의 지역구 분리(0지역, 1지역)
int parent[8];
int ans;  // 두 지역구 간 유권자 수 차이의 최소값

int Find(int x) {
	if (parent[x] == x) return x;
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
}

// 두 개의 지역구로 분리하는데 문제가 없는가?
bool isValid() {
    // parent 초기화
	for (int i = 0; i < N; i++)
		parent[i] = i;

    // 두 마을이 같은 지역구이며 연결된 길이 있을 경우 같은 소속으로 Union
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (visited[i] == visited[j] && adj[i][j])
				Union(i, j);

    // 소속의 개수
	int cnt = 0;

    // parent를 확인하며 소속의 개수 count
	for (int i = 0; i < N; i++)
		if (parent[i] == i)
			cnt++;

    // 소속의 개수가 2개인가?
	return cnt == 2;
}

// 마을을 두 개의 지역구로 분리하는 모든 경우의 수를 확인
void dfs(int now) {
    // 만약 두 개의 지역구로 분리하는데 문제가 없다면
	if (isValid()) {
		int diff = 0;

        // 유권자 수 차이 계산
		for (int i = 0; i < N; i++)
			diff += (visited[i] ? P[i] : -P[i]);

        // 정답 갱신
		ans = min(ans, abs(diff));
	}

	for (int i = now + 1; i < N; i++) {
		visited[i] = 1;
		dfs(i);
		visited[i] = 0;
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = MAX;

		cin >> N;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> adj[i][j];

		for (int i = 0; i < N; i++)
			cin >> P[i];

		dfs(0);

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
