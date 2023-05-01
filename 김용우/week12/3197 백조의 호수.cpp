#include <iostream>
#include <string>
#include <queue>

int R, C;	// R: 행의 수, C: 열의 수
int MAP[1501][1501];	// MAP[i][j]: 호수의 i행 j열의 정보 -> 0 물, 1 얼음
bool visitedWater[1501][1501];	// visitedWater[i][j]: i행 j열의 물 체크
bool visitedSwan[1501][1501];	// visitedSwan[i][j]: i행 j열의 백조 체크
int ans;	// ans: 두 백조가 만나기 까지 지나간 일 수

struct Coordinate {
	int y, x;	// y, x: 좌표
};

Coordinate swanA = { -1, - 1 }, swanB = { -1, -1 };	// swanA, swanB: 백조의 좌표

std::queue<Coordinate> waterQ, waterTmpQ, swanQ, swanTmpQ;	// waterQ, swanQ: 확인할 좌표, waterTmpQ, swanTmpQ: 다음에 확인할 좌표

// 방향 벡터
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

void movingSwan() {

	while (!swanQ.empty()) {
		Coordinate cur = swanQ.front();	// cur: 백조가 갈 수 있는 좌표
		swanQ.pop();

		for (int dir = 0; dir < 4; dir++) {
			Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 다음에 백조가 갈 수 있는 좌표

			if (next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 벗어나면 continue
			if (visitedSwan[next.y][next.x] != false) continue;	// 이미 확인했다면 continue

			if (MAP[next.y][next.x] != 0) swanTmpQ.push(next);	// 얼음이 있다면 다음에 백조가 위치할 수 있으므로 swanTmpQ에 넣음
			else swanQ.push(next);	// 물이라면 백조가 계속하여 이동할 수 있도록 swanQ에 넣음

			visitedSwan[next.y][next.x] = true;	// 방문 체크
		}
	}

	while (!swanTmpQ.empty()) {
		Coordinate tmp = swanTmpQ.front();	// tmp: 다음 백조 방문 위치
		swanTmpQ.pop();

		swanQ.push(tmp);
	}

	return;
}

void meltingIce() {

	while (!waterQ.empty()) {
		Coordinate cur = waterQ.front();	// cur: 녹을 얼음 좌표
		waterQ.pop();

		MAP[cur.y][cur.x] = 0;	// 얼음 녹음

		for (int dir = 0; dir < 4; dir++) {
			Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 다음에 녹을 얼음 좌표

			if (next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 벗어나면 continue
			if (visitedWater[next.y][next.x] != false) continue;	// 이미 확인 했다면 continue

			if (MAP[next.y][next.x] != 0) waterTmpQ.push(next);	// 다음 좌표가 얼음이라면 다음에 녹을 수 있도록 waterTmpQ에 넣음
			else waterQ.push(next);	// 다음 좌표가 물이라면 계속해서 탐색할 수 있도록 waterQ에 넣음

			visitedWater[next.y][next.x] = true;	// 방문 체크
		}
	}

	while (!waterTmpQ.empty()) {
		Coordinate tmp = waterTmpQ.front();	// tmp: 다음에 녹을 얼음 좌표
		waterTmpQ.pop();

		waterQ.push(tmp);
	}

	return;
}

void init() {	// 초기값 세팅

	// 얼음 사이에 물이 있는 경우도 있으므로 모든 칸을 돌면서 확인
	for (int j = 0; j < R; j++) {
		for (int i = 0; i < C; i++) {
			if (visitedWater[j][i] != false) continue;	// 이미 확인 했으면 continue
			if (MAP[j][i] != 0) continue;	// 물이 아니라면 continue

			waterQ.push({j, i});
			visitedWater[j][i] = 1;

			while (!waterQ.empty()) {	// 모든 물을 확인할 때 까지 반복
				Coordinate cur = waterQ.front();	// cur: 현재 확인 좌표
				waterQ.pop();
				
				for (int dir = 0; dir < 4; dir++) {
					Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 다음 확인 좌표

					if (next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 밖으로 나가면 continue
					if (visitedWater[next.y][next.x] != false) continue;	// 이미 확인했다면 continue
					
					if (MAP[next.y][next.x] != 0) waterTmpQ.push(next);	// 얼음 위치는 다음에 녹을 수 있도록 waterTmpQ에 넣음
					else waterQ.push(next);	// 물 위치는 계속해서 탐색할 수 있도록 waterQ에 넣음

					visitedWater[next.y][next.x] = true;	// 방문 체크
				}
			}
		}
	}

	while (!waterTmpQ.empty()) {
		Coordinate tmp = waterTmpQ.front();	// tmp: 다음에 녹을 얼음 좌표
		waterTmpQ.pop();

		waterQ.push(tmp);
	}


	swanQ.push(swanA);	// 백조 A의 좌표 넣음 -> 한 백조부터 탐색하여 다른 백조를 만날때 까지 반복하면 두 백조가 만날 수 있음
	visitedSwan[swanA.y][swanA.x] = true;

	while (!swanQ.empty()) {
		Coordinate cur = swanQ.front();	// cur: 현재 확인 좌표
		swanQ.pop();
		

		for (int dir = 0; dir < 4; dir++) {
			Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 다음 확인 좌표

			if (next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 벗어나면 continue
			if (visitedSwan[next.y][next.x] != false) continue;	// 이미 확인했다면 continue

			if (MAP[next.y][next.x] != 0) swanTmpQ.push(next);	// 얼음이 있다면 다음에 갈 수 있는 위치 이므로 swanTmpQ에 넣음
			else swanQ.push(next);	// 물이 있다면 계속해서 탐색

			visitedSwan[next.y][next.x] = true;	// 방문 체크
		}
	}

	while (!swanTmpQ.empty()) {
		Coordinate tmp = swanTmpQ.front();	// tmp: 다음 백조 좌표
		swanTmpQ.pop();

		swanQ.push(tmp);
	}

	return;
}

void sol() {

	
	init();
	if (visitedSwan[swanB.y][swanB.x] == true) return;	// 얼음이 녹지 않아도 두 백조가 만날 수 있음

	while (true) {
		ans++;	// 하루 지남

		meltingIce();	// 얼음 녹음
		movingSwan();	// 백조 이동

		if (visitedSwan[swanB.y][swanB.x] == true) return;	// 두 백조 만남
	}

	return;
}

void input() {
	std::cin >> R >> C;
	for (int j = 0; j < R; j++) {
		std::string s;	// s: 한 행의 정보
		std::cin >> s;
		for (int i = 0; i < C; i++) {
			if (s[i] == 'X') MAP[j][i] = -1;	// 얼음
			if (s[i] == 'L') {	// 백조
				if (swanA.y == -1) swanA = { j, i };
				else swanB = { j, i };
			}
		}
	}

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	std::cout << ans;

	return 0;
}