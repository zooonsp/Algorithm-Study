#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;
int N, M, C; // 크기, 벌통 개수, 채취 최대 양
vector<vector<int>> Honey;
// N : 3 ~ 10
// M : 1 ~ 5
// C : 10 ~ 30
int squareSum{};

void dfs(int i, int j, int index, int sum, int sq_sum) {
	if (index == M) {
		if (sum <= C) {
			squareSum = max(sq_sum, squareSum);
		}
		return;
	}

	dfs(i, j, index + 1, sum + Honey[i][j + index], sq_sum + Honey[i][j + index] * Honey[i][j + index]);  // 선택
	dfs(i, j, index + 1, sum, sq_sum); // 미선택
}

int main() {
	int T;
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> M >> C;
		Honey.assign(N, vector<int>(N, 0));
		for (auto& row : Honey) {
			for (int& i : row) {
				cin >> i;
			}
		}
		// 해당 칸에서 벌통 선택 시 구할 수 있는 최대량 구해서 넣기
		vector<vector<int>> MaxHoney(N,vector<int>(N,0));
		for (int i = 0; i < N; ++i) { // row
			for (int j = 0; j <= N - M; ++j) { // 가능한 column
				squareSum = -1;
				dfs(i, j, 0, 0, 0);
				MaxHoney[i][j] = squareSum;
			}
		}

		int answer{};
		for (int i = 0; i < N; ++i) {
			
			for (int j = 0; j <= N - M; ++j) { // 가능한 column
				// 한 행에서 나오는 경우
				for (int k = j + M; k < N; ++k) { // 가능한 column
					answer = max(answer, MaxHoney[i][j] + MaxHoney[i][k]);
				}

				// 서로 다른 행에서 나오는 경우
				for (int nexti = i + 1; nexti < N; ++nexti) {
					for (int nextj = 0; nextj <= N - M; ++nextj) {
						answer = max(answer, MaxHoney[i][j] + MaxHoney[nexti][nextj]);
					}
				}
			}
		}

		cout << "#" << tc << ' ' << answer << endl;
	}
	return 0;
}