#include <iostream>
using namespace std;

int N, X;
int MAP[20][20];

int construct() {
	int ans = 0;

	for (int y = 0; y < N; y++) {
		int flag = 1;
		int check[20]{};

		// right
		for (int x = 1; x < N; x++) {
			if (MAP[y][x] < MAP[y][x - 1]) {
				for (int i = 0; i < X; i++) {
					if (x + i >= N || MAP[y][x + i] != MAP[y][x - 1] - 1) {
						flag = 0;
						break;
					}
					check[x + i] = 1;
				}
				if (flag == 0)
					break;
			}
		}

		// left
		for (int x = N - 2; x >= 0; x--) {
			if (MAP[y][x] < MAP[y][x + 1]) {
				for (int i = 0; i < X; i++) {
					if (x - i < 0 || check[x - i] == 1 || MAP[y][x - i] != MAP[y][x + 1] - 1) {
						flag = 0;
						break;
					}
				}
				if (flag == 0)
					break;
			}
		}

		ans += flag;
	}

	for (int x = 0; x < N; x++) {
		int flag = 1;
		int check[20]{};

		// down
		for (int y = 1; y < N; y++) {
			if (MAP[y][x] < MAP[y - 1][x]) {
				for (int i = 0; i < X; i++) {
					if (y + i >= N || MAP[y + i][x] != MAP[y - 1][x] - 1) {
						flag = 0;
						break;
					}
					check[y + i] = 1;
				}
				if (flag == 0)
					break;
			}
		}

		// up
		for (int y = N - 2; y >= 0; y--) {
			if (MAP[y][x] < MAP[y + 1][x]) {
				for (int i = 0; i < X; i++) {
					if (y - i < 0 || check[y - i] == 1 || MAP[y - i][x] != MAP[y + 1][x] - 1) {
						flag = 0;
						break;
					}
				}
				if (flag == 0)
					break;
			}
		}

		ans += flag;
	}

	return ans;
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';

		cin >> N >> X;
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				cin >> MAP[y][x];

		cout << construct() << '\n';
	}

	return 0;
}
