#include <iostream>
#include <algorithm>
using namespace std;

int dx[2][6]{
	{0, 1, 1, 0, -1, -1},  // U, RU, RD, D, LD, LU
	{0, 1, 1, 0, -1, -1}
};
int dy[2][6]{
	{-1, -1, 0, 1, 0, -1},
	{-1, 0, 1, 1, 1, 0}
};

int N, M;
int MAP[15][15];
int visited[15][15];
int ans;

void dfs(int y, int x, int level, int sum) {
	if (level >= 4) {
		ans = max(ans, sum);
		return;
	}

	for (int i = 0; i < 6; i++) {
		int ny = y + dy[x % 2][i];
		int nx = x + dx[x % 2][i];

		if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
		if (visited[ny][nx] == 1) continue;

		visited[ny][nx] = 1;

		dfs(y, x, level + 1, sum + MAP[ny][nx]);
		dfs(ny, nx, level + 1, sum + MAP[ny][nx]);

		visited[ny][nx] = 0;
	}
}

int main(void) {
	cin >> N >> M;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			cin >> MAP[y][x];

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			visited[y][x] = 1;
			dfs(y, x, 1, MAP[y][x]);
			visited[y][x] = 0;
		}
	}

	cout << ans << '\n';

	return 0;
}
