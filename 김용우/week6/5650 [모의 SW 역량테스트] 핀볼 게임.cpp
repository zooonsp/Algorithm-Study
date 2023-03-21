#include <iostream>
#include <algorithm>

int N;	// N: 한 변의 길이
int MAP[101][101];	// MAP: 지도
int ans;	// ans: 정답

// 방향 벡터: 우 하 좌 상
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

void func(int startY, int startX, int curY, int curX, int dir, int depth, int score) {	// 시작 위치 y, x, 현재 위치 y, x, 방향 dir, 깊이, 점수

	while (1) {
		if (depth != 0) {	// 처음에 시작할 때 시작 위치 현재 위치인 것을 거르기 위함
			if (startY == curY && startX == curX) {	// 시작 위치로 돌아옴
				ans = std::max(ans, score);
				return;
			}
			if (MAP[curY][curX] == -1) {	// 웜홀 만남
				ans = std::max(ans, score);
				return;
			}
		}

		int newY = curY + dirY[dir];	// newY: 다음 y 좌표
		int newX = curX + dirX[dir];	// newX: 다음 x 좌표

		if (newY < 0 || newX < 0 || newY >= N || newX >= N) {	// 외벽에 부딪히는 경우
			score++;	// 벽에 부딪히면 점수 얻음
			dir = (dir + 2) % 4;	// 방향은 반대
			if (newY == -1)	newY = 0;
			if (newX == -1) newX = 0;
			if (newX == N) newX = N - 1;
			if (newY == N) newY = N - 1;
		}
		if (MAP[newY][newX] >= 1 && MAP[newY][newX] <= 5) {	// 블록
			score++;	// 블록에 부딪히면 점수 얻음
			if (MAP[newY][newX] == 1) {
				if (dir == 0) dir = 2;	// 왼쪽에서 오면 -> 왼쪽으로 감
				else if (dir == 1) dir = 0;	// 위쪽에서 오면 -> 오른쪽으로 감 
				else if (dir == 2) dir = 3;	// 오른쪽에서 오면 -> 위쪽으로 감
				else if (dir == 3) dir = 1;	// 아래에서 오면 -> 아래로 감
			}
			if (MAP[newY][newX] == 2) {
				if (dir == 0) dir = 2;	// 왼쪽에서 오면 -> 왼쪽으로 감
				else if (dir == 1) dir = 3;	// 위쪽에서 오면 -> 위쪽으로 감 
				else if (dir == 2) dir = 1;	// 오른쪽에서 오면 -> 아래쪽으로 감
				else if (dir == 3) dir = 0;	// 아래쪽에서 오면 -> 오른쪽로 감
			}
			if (MAP[newY][newX] == 3) {
				if (dir == 0) dir = 1;	// 왼쪽에서 오면 -> 아래쪽으로 감
				else if (dir == 1) dir = 3;	// 위쪽에서 오면 -> 위쪽으로 감 
				else if (dir == 2) dir = 0;	// 오른쪽에서 오면 -> 오른쪽으로 감
				else if (dir == 3) dir = 2;	// 아래에서 오면 -> 왼쪽으로 감
			}
			if (MAP[newY][newX] == 4) {
				if (dir == 0) dir = 3;	// 왼쪽에서 오면 -> 위쪽으로 감
				else if (dir == 1) dir = 2;	// 위에서 오면 -> 왼쪽으로 감 
				else if (dir == 2) dir = 0;	// 오른쪽에서 오면 -> 오른쪽으로 감
				else if (dir == 3) dir = 1;	// 아래에서 오면 -> 아래쪽로 감
			}
			if (MAP[newY][newX] == 5) {
				if (dir == 0) dir = 2;	// 왼쪽에서 오면 -> 왼쪽으로 감
				else if (dir == 1) dir = 3;	// 위쪽에서 오면 -> 위쪽으로 감 
				else if (dir == 2) dir = 0;	// 오른쪽에서 오면 -> 오른쪽으로 감
				else if (dir == 3) dir = 1;	// 아래에서 오면 -> 아래쪽로 감
			}
		}
		if (MAP[newY][newX] >= 6 && MAP[newY][newX] <= 10) {	// 웜홀
			int flag = 0;
			for (int j = 0; j < N; j++) {
				for (int i = 0; i < N; i++) {
					if (MAP[newY][newX] == MAP[j][i]) {	// 같은 번호의 웜홀 찾기
						if (newY != j || newX != i) {
							flag = 1;
							newY = j;	// 웜홀 이동 y
							newX = i;	// 움홀 이동 x
							break;
						}
					}
					
				}
				if (flag == 1) break;
			}
		}
		curY = newY;
		curX = newX;
		depth++;	// 계속 증가시켜줄 필요는 없음
	}

	return;
}

void sol() {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (MAP[j][i] != 0) continue;

			for (int d = 0; d < 4; d++) {
				func(j, i, j, i, d, 0, 0);
			}
		}
	}
}

void input() {	// 입력
	std::cin >> N;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> MAP[j][i];
		}
	}
	return;
}

void reset() {	// 리셋
	ans = 0;
	return;
}

int main() {
	int T;	// T: 테스트 케이스

	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		sol();
		std::cout << '#' << tc << ' ' << ans << std::endl;
	}
	return 0;
}