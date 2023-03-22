/*
-1 : 블랙홀
0 : 빈 공간
1 ~ 5 : 블록
6 ~ 10 : 웜홀

5
10
0 1 0 3 0 0 0 0 7 0
0 0 0 0 -1 0 5 0 0 0
0 4 0 0 0 3 0 0 2 2
1 0 0 0 1 0 0 3 0 0
0 0 3 0 0 0 0 0 6 0
3 0 0 0 2 0 0 1 0 0
0 0 0 0 0 1 0 0 4 0
0 5 0 4 1 0 7 0 0 5
0 0 0 0 0 1 0 0 0 0
2 0 6 0 0 4 0 0 0 4
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
int N;
// vector<vector<int>> Map;
int Map[102][102];

struct coord { // 좌표 표현
	int x, y;
};

struct WormHole {
	coord from, to; // 두 점 표현
};
// vector<WormHole> wormholes(5); // 5개
WormHole wormholes[5];

struct Info {
	coord pos; // 현재 위치
	int dir; // 방향
};

int GetHighScoreAtPos(int sx, int sy) {
	int ret{}; // 현재 시작점에서 구할 수 있는 최대점수 리턴
	// sx, sy : 시작점
	int dx[]{ -1,1,0,0 };
	int dy[]{ 0,0,-1,1 };

	for (int i = 0; i < 4; ++i) {
		// Info now({ {sx,sy}, i }); 간접 참조가 잘못되었습니다.???
		Info now;
		now.pos.x = sx;
		now.pos.y = sy;
		now.dir = i;
		int tmpScore{};
		while (1) {
			// 다음 점
			int nx = now.pos.x + dx[now.dir];
			int ny = now.pos.y + dy[now.dir];

			if (nx <= 0 || ny <= 0 || nx > N || ny > N) { 	// 벽
				now.pos.x = nx;
				now.pos.y = ny;
				tmpScore++;
				if (now.dir & 1) {
					now.dir--;
				}
				else {
					now.dir++;
				}
			}
			else if (nx == sx && ny == sy) break; // 시작점
			else if (Map[nx][ny] == -1) break; // 블랙홀
			else if (1 <= Map[nx][ny] && Map[nx][ny] <= 5) { // 블록
				now.pos.x = nx;
				now.pos.y = ny;
				tmpScore++;
				// dir : 상하좌우 순서
				if (1 == Map[nx][ny]) {
					if (0 == now.dir) now.dir = 1; // 상 -> 하
					else if (1 == now.dir) now.dir = 3; // 하 -> 우
					else if (2 == now.dir) now.dir = 0; // 좌 -> 상
					else if (3 == now.dir) now.dir = 2; // 우 -> 좌
				}
				else if (Map[nx][ny] == 2) {
					if (0 == now.dir) now.dir = 3; // 상 -> 우
					else if (1 == now.dir) now.dir = 0; // 하 -> 상
					else if (2 == now.dir) now.dir = 1; // 좌 -> 하
					else if (3 == now.dir) now.dir = 2; // 우 -> 좌
				}
				else if (Map[nx][ny] == 3) {
					if (0 == now.dir) now.dir = 2; // 상 -> 좌
					else if (1 == now.dir) now.dir = 0; // 하 -> 상
					else if (2 == now.dir) now.dir = 3; // 좌 -> 우
					else if (3 == now.dir) now.dir = 1; // 우 -> 하
				}
				else if (Map[nx][ny] == 4) {
					if (0 == now.dir) now.dir = 1; // 상 -> 하
					else if (1 == now.dir) now.dir = 2; // 하 -> 좌
					else if (2 == now.dir) now.dir = 3; // 좌 -> 우
					else if (3 == now.dir) now.dir = 0; // 우 -> 상
				}
				else if (Map[nx][ny] == 5) {
					if (now.dir & 1) {
						// 하 -> 상
						// 우 -> 좌
						now.dir--;
					}
					else {
						// 상 -> 하
						// 좌 -> 우
						now.dir++;
					}
				}
			}
			else if (6 <= Map[nx][ny] && Map[nx][ny] <= 10) { // 웜홀
				int wormHoleIndex = Map[nx][ny] - 6;
				if (wormholes[wormHoleIndex].from.x == nx && wormholes[wormHoleIndex].from.y == ny) {
					now.pos.x = wormholes[wormHoleIndex].to.x;
					now.pos.y = wormholes[wormHoleIndex].to.y;
				}
				else {
					now.pos.x = wormholes[wormHoleIndex].from.x;
					now.pos.y = wormholes[wormHoleIndex].from.y;
				}
			}
			else if (Map[nx][ny] == 0 ) {
				now.pos.x = nx;
				now.pos.y = ny;
			}
		}
		ret = max(ret, tmpScore);
	}
	return ret;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc{ 1 }; tc <= T; ++tc)
	{
		for (int i = 0; i < 5; ++i) {
			wormholes[i].from.x = -1;
			wormholes[i].from.y = -1;
			wormholes[i].to.x = -1;
			wormholes[i].to.y = -1;
		}
		cin >> N;
		// Map.assign(N + 2, vector<int>(N + 2, -2));
		// 매번 vector 동적 할당 -> TLE(Time Limit Exceeded) (48개까지 맞음)
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				cin >> Map[i][j];
				if (6 <= Map[i][j] && Map[i][j] <= 10) { // 웜홀
					int wormHoleIndex = Map[i][j] - 6;
					if (wormholes[wormHoleIndex].from.x == -1 && wormholes[wormHoleIndex].from.y == -1) {
						wormholes[wormHoleIndex].from.x = i;
						wormholes[wormHoleIndex].from.y = j;
					}
					else {
						wormholes[wormHoleIndex].to.x = i;
						wormholes[wormHoleIndex].to.y = j;
					}
				}
			}
		}

		int score{ -1 };

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (Map[i][j] == 0) {
					int ret = GetHighScoreAtPos(i, j);
					score = max(score, ret);
				}
			}
		}

		cout << "#" << tc << ' ' << score << '\n';
	}
	return 0;
}