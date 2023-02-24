#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N;
int S[16][16];
int path[16];
int remain[16];
int ans;

void dfs(int level) {
	if (level >= N / 2) {
		int p_idx = 0, r_idx = 0;
		
		for (int i = 0; i < N; i++) {
			if (i == path[p_idx])
				p_idx++;
			else
				remain[r_idx++] = i;
		}

		int A = 0, B = 0;

		for (int i = 0; i < N / 2; i++) {
			for (int j = i + 1; j < N / 2; j++) {
				A += S[path[i]][path[j]];
				B += S[remain[i]][remain[j]];
			}
		}

		ans = min(ans, abs(A - B));

		return;
	}

	for (int i = path[level - 1] + 1; i < N; i++) {
		path[level] = i;
		dfs(level + 1);
		path[level] = 0;
	}
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N;
		ans = 21e8;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> S[i][j];

		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				S[i][j] += S[j][i];

		dfs(1);

		cout << ans << '\n';
	}

	return 0;
}
