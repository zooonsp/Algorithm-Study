// 하나의 자석이 1 칸 회전될 때, 붙어 있는 자석은 서로 붙어 있는 날의 자성과 다를 경우에만 인력에 의해 반대 방향으로 1 칸 회전된다.
// i번 자석의 빨간색 화살표 위치에 있는 극이 S 극이면 1 << (i-1) 점
// 

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
int K;

vector<vector<int>> magnets;

/*
각 자석의 날 자성정보는 빨간색 화살표 위치의 날부터 시계방향 순서대로 주어진다.
N극 : 0, S극 : 1
0 0 1 0 0 1 0 0
1 0 0 1 1 1 0 1
0 0 1 0 1 1 0 0
0 0 1 0 1 1 0 1

점수 -> i번 자석의 0
1번 자석의 2 - 2번 자석의 6
2번 자석의 2 - 3번 자석의 6
3번 자석의 2 - 4번 자석의 6
*/

void RotateClockwise(int row) {
	// 시계 방향(1)이면 magnets[i][0]->magnets[i][1]
	int tmp = magnets[row][7];
	for (int i = 7; i > 0; --i) {
		magnets[row][i] = magnets[row][i - 1];
	}
	magnets[row][0] = tmp;

}

void RotateCounterClockwise(int row) {
	// 반시계 방향(-1)이면 magnets[i][1] -> magnets[i][0]
	int tmp = magnets[row][0];
	for (int i = 1; i < 8; ++i) {
		magnets[row][i - 1] = magnets[row][i];
	}
	magnets[row][7] = tmp;
}

void Rotate(int choice, int row) {
	if (choice == 1) RotateClockwise(row);
	else RotateCounterClockwise(row);
}

int main() {
	int T;
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> K; // 회전 횟수
		magnets.assign(4, vector<int>(8, 0));
		for (auto& row : magnets) {
			for (int& i : row) {
				cin >> i;
			}
		}
		int m{}, dir{}; // dir : 1(시계) / -1(반시계)
		for (int k = 0; k < K; ++k) {
			cin >> m >> dir; // 어느 자석을 어느 방향으로
			m--;

			int turn[4]{};
			turn[m] = dir;
			for (int i = 1; i < 4; ++i) {
				if (m - i >= 0) {
					if (magnets[m - i][2] != magnets[m - i + 1][6]) {
						if (turn[m - i + 1] == 1) turn[m - i] = -1;
						else turn[m - i] = 1;
					}
					else turn[m - i] = 0;
				}
				if (m + i < 4) {
					if (magnets[m + i][6] != magnets[m + i - 1][2]) {
						if (turn[m + i - 1]== 1) turn[m + i] = -1;
						else turn[m + i] = 1;
					}
					else turn[m + i] = 0;
				}
			}

			if (dir == 1) {
				Rotate(1, m);
				for (int o = m + 1; o < 4; ++o) { // 큰 방향 전파
					if (!turn[o]) break;
					Rotate(turn[o], o);
				}
				for (int o = m - 1; o >= 0; --o) { // 작은 방향 전파
					if (!turn[o]) break;
					Rotate(turn[o], o);
				}
			}
			else {
				Rotate(-1, m);
				for (int o = m + 1; o < 4; ++o) { // 큰 방향 전파
					if (!turn[o]) break;
					Rotate(turn[o], o);
				}
				for (int o = m - 1; o >= 0; --o) { // 작은 방향 전파
					if (!turn[o]) break;
					Rotate(turn[o], o);
				}
			}
		}
		int score{};
		for (int row = 0; row < 4; ++row) {
			if (magnets[row][0] == 1) {
				score += 1 << row;
			}
		}
		cout << "#" << tc << ' ' << score << endl;
	}
	return 0;
}