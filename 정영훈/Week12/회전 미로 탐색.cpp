#include <iostream>
#include <queue>

using namespace std;

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};
coord start(0, 0);

struct QInfo {
	coord c;
	int rotate;
	QInfo(coord c, int rotate) : c(c), rotate(rotate) {}
};

char Map[4][500][500]; // 회전횟수 당 Map
int visited[4][500][500];


int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int k;
	cin >> k;
	const int SIZE = 4 * k;
	
	for (int i{}; i < SIZE; ++i) {
		for (int j{}; j < SIZE; ++j) {
			cin >> Map[0][i][j];
			Map[1][i][j] = Map[2][i][j] = Map[3][i][j] = Map[0][i][j];
			if (Map[0][i][j] == 'S') start = { i,j };
		}
	}

	// 회전횟수당 각 구역 별 맵 만들기
	for (int r{ 1 }; r < 4; ++r) {
		for (int i{}; i < SIZE; i += 4) {
			for (int j{}; j < SIZE; j += 4) {
				int X = (i / 4) * 4, Y = (j / 4) * 4; // 각 구역 시작
				for (int x{}; x < 4; ++x) {
					for (int y{}; y < 4; ++y) {
						Map[r][X + x][Y + y] = Map[r - 1][X + 3 - y][Y + x];
					}
				}
			}
		}
	}

	queue<QInfo> q;
	q.push(QInfo(start, 0));
	visited[0][start.x][start.y] = 1;
	int ans{ -1 };

	while (!q.empty()) {
		QInfo now = q.front(); q.pop();
		int startX = (now.c.x / 4) * 4, startY = (now.c.y / 4) * 4;

		if (Map[now.rotate][now.c.x][now.c.y] == 'E') {
			ans = visited[now.rotate][now.c.x][now.c.y] - 1;
			break;
		}

		for (int i = 0; i < 5; ++i) {
			int nx = now.c.x + "02111"[i] - '1';
			int ny = now.c.y + "11021"[i] - '1';
			if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE) continue; // 범위
			// 구역
			int startNX = (nx / 4) * 4;
			int startNY = (ny / 4) * 4;
			// 회전 후 좌표
			int rotateNX = startNX + (ny % 4);
			int rotateNY = startNY + 3 - (nx % 4);
			if (startX == startNX && startY == startNY) { // 새좌표가 같은 영역
				if (Map[now.rotate][nx][ny] == '#') continue; // 벽
				if (visited[(now.rotate + 1) % 4][rotateNX][rotateNY] &&
					visited[(now.rotate + 1) % 4][rotateNX][rotateNY] <= visited[now.rotate][now.c.x][now.c.y] + 1) continue; // 갈 필요 없음
				visited[(now.rotate + 1) % 4][rotateNX][rotateNY] = visited[now.rotate][now.c.x][now.c.y] + 1;
				q.push(QInfo(coord(rotateNX, rotateNY), (now.rotate + 1) % 4)); // 회전 카운팅 유지
			}
			else { // 새 좌표가 다른 영역
				if (Map[0][nx][ny] == '#') continue; // 벽
				if (visited[1][rotateNX][rotateNY] &&
					visited[1][rotateNX][rotateNY] <= visited[now.rotate][now.c.x][now.c.y] + 1) continue; // 갈 필요 없음
				visited[1][rotateNX][rotateNY] = visited[now.rotate][now.c.x][now.c.y] + 1;
				q.push(QInfo(coord(rotateNX, rotateNY), 1)); // 새 회전
			}
		}
	}

	cout << ans << '\n';
	return 0;
}