#include <iostream>
#include <queue>

int R, C;	// R: 행의 크기, C: 열의 크기
int MAP[101][101];	// MAP[i][j]: i행 j열의 치즈 정보
bool visited[101][101];	// visited[i][j]: i행 j열의 방문 정보
int T, S;	// T: 치즈가 모두 녹아서 없어지는 데 걸리는 시간, S: 모두 녹기 한 시간 전에 남아있는 치즈조각이 놓여 있는 칸의 개수

// 방향 벡터
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

struct Coordinate {
	int y, x;	// y, x: 좌표
};

void BFS() {
	std::queue<Coordinate> q;	// q: 탐색할 칸의 좌표
	std::queue<Coordinate> tmpQ;	// tmpQ: 다음에 탐색할 칸의 좌표

	// (0, 0)은 항상 치즈가 없으므로 시작점
	q.push({ 0, 0 });
	visited[0][0] = true;

	while (!q.empty()) {
		S = q.size();
		while (!q.empty()) {
			Coordinate cur = q.front();	// cur: 현재 좌표
			q.pop();

			for (int dir = 0; dir < 4; dir++) {
				Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 탐색할 좌표

				if (next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 벗어나면 continue

				if (visited[next.y][next.x] == true) continue;	// 이미 방문 했으면 continue

				if (MAP[next.y][next.x] == 1) tmpQ.push(next);	// 치즈가 있는 칸이면 tmpQ에 좌표 넣음
				else q.push(next);	// 치즈가 없는 칸이면 q에 좌표 넣음 -> 치즈가 없는 칸부터 모든 탐색이 완료

				visited[next.y][next.x] = true;	// 방문 체크
			}
		}

		// 현재 가능한 좌표에 대하여 모든 탐색을 완료
		while (!tmpQ.empty()) {
			q.push(tmpQ.front());	// 다음에 탐색할 좌표를 q에 넣음
			tmpQ.pop();
		}
		T++;	// 시간 증가
	}

	return;
}

void sol() {

	BFS();

	return;
}

void input() {
	std::cin >> R >> C;
	for (int j = 0; j < R; j++) {
		for (int i = 0; i < C; i++)
			std::cin >> MAP[j][i];
	}

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	std::cout << T - 1 << '\n' << S;

	return 0;
}