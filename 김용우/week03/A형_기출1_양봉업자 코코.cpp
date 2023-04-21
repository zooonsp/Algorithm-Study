#include <iostream>
#include <algorithm>

int N, M;	// N: 세로 크기, M: 가로 크기
int MAP[16][16];	// 벌집 정보
int dirY[2][6] = { {-1,0,0,1,1,1},{-1,-1,-1,0,0,1} }, dirX[2][6] = { {0,-1,1,-1,0,1}, {-1,0,1,-1,1,0} };
int visited[16][16];	// 방문 했는지
int maxCost = -21e8;	// 정답

void funcY(int y, int x) {	// y자 모양이나 뒤집어진 y자 모양은 DFS를 사용하여 탐지가 불가능...
	int cost = 0;

	if (y < 1 || x < 1 || y >= N - 1 || x >= M - 1) return;	// y나 뒤집어진 y를 만들 수 없는 경우 return

	// y 모양
	if (x % 2 == 0) {	// x가 짝수일 경우
		cost += MAP[y][x];
		cost += MAP[y - 1][x - 1];
		cost += MAP[y - 1][x + 1];
		cost += MAP[y + 1][x];
	}
	else {	// x가 홀수일 경우
		cost += MAP[y][x];
		cost += MAP[y][x - 1];
		cost += MAP[y][x + 1];
		cost += MAP[y + 1][x];	
	}
	maxCost = std::max(maxCost, cost);

	cost = 0;
	// 뒤집어진 y 모양
	if (x % 2 == 0) {	// x가 짝수일 경우
		cost += MAP[y][x];
		cost += MAP[y - 1][x];
		cost += MAP[y][x - 1];
		cost += MAP[y][x + 1];
	}
	else {	// x가 홀수일 경우
		cost += MAP[y][x];
		cost += MAP[y - 1][x];
		cost += MAP[y + 1][x - 1];
		cost += MAP[y + 1][x + 1];
	}
	maxCost = std::max(maxCost, cost);

	return;
}

void func(int y, int x, int d, int cost) {	// 현재 y 좌표, 현재 x 좌표, 선택된 수 d, 현재까지 비용 cost

	if (d == 3) {	// d가 0부터 시작하였기 때문에 d = 3이면 4칸 선택한 것
		maxCost = std::max(maxCost, cost);	// 4개 다 선택했으면 maxCost에 비교하여 저장
		return;
	}

	for (int i = 0; i < 6; i++) {
		int newY = y + dirY[(x+1)%2][i];	// 이동할 y좌표
		int newX = x + dirX[(x+1)%2][i];	// 이동할 x좌표
		int newCost;	// 이동한 곳까지의 비용

		if (newY < 0 || newX < 0 || newY >= N || newX >= M) continue;	// 범위 벗어남
		if (visited[newY][newX] != 0) continue;	// 이미 방문함

		newCost = cost + MAP[newY][newX];	// 금액 갱신
		visited[newY][newX] = 1;	// 방문 체크
		func(newY, newX, d + 1, newCost);
		visited[newY][newX] = 0;	// 방문 복구
	}

	return;
}

int main() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {	// 벌집 정보 입력
		for (int i = 0; i < M; i++) {
			std::cin >> MAP[j][i];
		}
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			visited[j][i] = 1;
			func(j, i, 0, MAP[j][i]);	// (j,i)에서부터 4개
			funcY(j, i);	// (j, i)에서의 y자와 뒤집어진 모양
			visited[j][i] = 0;
		}
	}
	std::cout << maxCost;
	return 0;
}