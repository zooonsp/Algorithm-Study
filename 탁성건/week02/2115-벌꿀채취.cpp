#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M, C, H;
int MAP[10][10];
int honey[10][10];
int sy, sx;
int ans;

void calc_honey(int x, int amount, int pay) {
	if (x == sx + M) {
		honey[sy][sx] = max(honey[sy][sx], pay);
		return;
	}

	calc_honey(x + 1, amount, pay);

	if (amount + MAP[sy][x] <= C)
		calc_honey(x + 1, amount + MAP[sy][x], pay + MAP[sy][x] * MAP[sy][x]);
}

void select_honey(int y, int x, int pay, int cnt) {
	if (x >= H) {
		y++;
		x = 0;
	}

	if (cnt == 2) {
		ans = max(ans, pay);
		return;
	}

	if (y >= N) return;

	select_honey(y, x + 1, pay, cnt);
	select_honey(y, x + M, pay + honey[y][x], cnt + 1);
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N >> M >> C;
		
		H = N - M + 1;

		ans = 0;
		memset(honey, 0, sizeof(honey));

		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				cin >> MAP[y][x];

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < H; x++) {
				sy = y, sx = x;
				calc_honey(x, 0, 0);
			}
		}

		select_honey(0, 0, 0, 0);

		cout << ans << '\n';
	}

	return 0;
}
