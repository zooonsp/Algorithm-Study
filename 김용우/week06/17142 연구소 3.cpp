#include <iostream>
#include <algorithm>
#include <queue>

struct Coordinate {	// 좌표
	int y, x;
};

int N, M;	// N: 연구소의 크기, M: 놓을 수 있는 바이러스의 개수
int MAP[52][52];	// MAP[i][j]: 연구소 i 행 j 열의 상태
Coordinate virus[12];	// virus[i]: i 바이러스의 위치
int virusNum;	// virusNum: 총 바이러스의 개수
int visited[12];	// visited[i]: i 바이러스 활성화 여부, 1 활성화 0 비활성화
int ans = 21e8;	// ans: 모든 빈 칸에 바이러스가 있게 되는 최소 시간

// 방향 벡터
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

int spread() {
	int tmpMAP[52][52] = { 0, };	// tmpMAP[i][j]: i행 j열의 바이러스 정보
	std::queue<Coordinate> q;	// q: 퍼지기 전의 활성화 바이러스

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (MAP[j][i] == 1) {	// 벽인 경우
				tmpMAP[j][i] = -1;	// 벽 -1
			}
			else if (MAP[j][i] == 2) {	// 바이러스인 경우
				tmpMAP[j][i] = 0;	// 0
			}
			else {
				tmpMAP[j][i] = 0;
			}			
		}
	}

	for (int i = 0; i < 12; i++) {
		if (visited[i] == 1) {	// 활성화 바이러스인 경우
			q.push(virus[i]);	// q에 넣음
			tmpMAP[virus[i].y][virus[i].x] = 1;	// BFS를 사용하기 위해 1로 설정
		}
	}

	while (!q.empty()) {
		Coordinate now = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {	// 4가지 방향으로 바이러스 퍼짐
			int newY = now.y + dirY[dir];
			int newX = now.x + dirX[dir];

			if (newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어나면 continue;

			if (tmpMAP[newY][newX] != 0) continue;	// 벽이거나 바이러스가 있다면 continue;

			tmpMAP[newY][newX] = tmpMAP[now.y][now.x] + 1;	// 현재 칸에 비해 다음칸 시간 증가

			q.push({ newY, newX });
		}
	}

	for (int i = 0; i < virusNum; i++) {	// 비활성화 된 바이러스의 경우도 "빈칸"이 아니므로 1로 설정
		tmpMAP[virus[i].y][virus[i].x] = 1;
	}

	int max = -1;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (tmpMAP[j][i] == 0) {	// 빈칸이 있다면 -1
				return -1;
			}
			max = std::max(max, tmpMAP[j][i] - 1);	// 최대 시간 갱신 -> 1부터 시작했기 때문에 -1
		}
	}

	return max;	// 최대값 return
}

void DFS(int cur, int num) {	// num개의 바이러스 활성화

	if (num == M) {
		int min = spread();
		if (min != -1)	// 바이러스가 모든 칸에 퍼질 수 있는 경우에 대하여
			ans = std::min(ans, min);	// 최대값 갱신

		return;
	}


	for (int i = cur + 1; i < virusNum; i++) {
		if (visited[i] == 1) continue;

		visited[i] = 1;

		DFS(i, num+1);

		visited[i] = 0;
	}
	
	return;
}

void sol() {
	DFS(-1, 0);

	return;
}

void input() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> MAP[j][i];
			if (MAP[j][i] == 2) {	// 바이러스가 있는 곳은 virus 배열에 정보 삽입
				virus[virusNum] = { j, i };
				virusNum++;	// 총 바이러스 개수 ++
			}
		}
	}

	return;
}

int main() {
	input();
	sol();
	if (ans == 21e8)	// 모든 경우에 대하여 시도해도 모든 칸에 퍼트릴 수 없으면 -1
		std::cout << -1;
	else
		std::cout << ans;
	return 0;
}