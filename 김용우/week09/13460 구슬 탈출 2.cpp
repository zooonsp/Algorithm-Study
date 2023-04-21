#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

struct Coordinate{
	int y, x;	// y, x: 좌표
};

int N, M;	// N: 보드의 세로 크기, M: 보드의 가로 크기
int MAP[10][10];	// MAP[i][j]: 보드 i행 j열의 정보 > -1: 벽, 0: 빈 공간, 1: 빨간 구슬, 2: 파란 구슬
Coordinate ball[3];	// ball[i]: i 번 구슬: 1: 빨간 구슬, 2: 파란 구슬
Coordinate hole;	// hole: 구멍
int ans = 21e8;	// ans: 빨간 구슬을 구멍을 통해 빼낼 수 있는 최소 동작 수, 불가능하거나 10번 초과는 -1

// 방향 벡터 > 좌 우 상 하
int dirY[] = {0, 0, -1, 1};
int dirX[] = {-1, 1, 0, 0};

void ballMove(int dir){	// dir: 구슬 이동 방향
	int ballFlag = 1;	// ballFlag: 먼저 움직여야하는 구슬 번호 > 1: 빨간 구슬, 2: 파란 구슬

	if(dir == 0){	// 왼쪽으로 기울이기 > 왼쪽에 있는 구슬 먼저 움직여야함
		if(ball[1].x > ball[2].x)
			ballFlag = 2;
	}
	else if(dir == 1){	// 오른쪽으로 기울이기 > 오른쪽에 있는 구슬 먼저 움직여야함
		if(ball[1].x < ball[2].x)
			ballFlag = 2;
	}
	else if(dir == 2){	// 위쪽으로 기울이기 > 위쪽에 있는 구슬 먼저 움직여야함
		if(ball[1].y > ball[2].y)
			ballFlag = 2;
	}
	else if(dir == 3){	// 아래로 기울이기 > 아래쪽에 있는 구슬 먼저 움직여야함
		if(ball[1].y < ball[2].y)
			ballFlag = 2;
	}

	for(int i=0; i<2; i++){	// 두 개의 구슬 움직이기
		Coordinate cur = ball[ballFlag];	// cur: 현재 움직여야 하는 구슬의 위치
		MAP[cur.y][cur.x] = 0;	// 움직여야하는 구슬이 있던 위치 빈 공간 표시
		while(true){
			Coordinate next = {cur.y + dirY[dir], cur.x+dirX[dir]};

			if(hole.y == next.y && hole.x == next.x){	// 구슬이 구멍에 빠짐
				ball[ballFlag] = {-1, -1};	// 구멍에 빠진 구슬의 위치 (-1, -1)로 표시
				break;
			}
			if(MAP[next.y][next.x] != 0) break;	// 빈 공간이 아니면 종료 > 벽이 있거나 다른 구슬이 있음

			cur = next;
		}
		if(ball[ballFlag].y != -1){	// 구슬이 구멍에 빠지지 않았다면
			MAP[cur.y][cur.x] = ballFlag;	// 보드에 움직인 구슬 위치 표시
			ball[ballFlag] = cur;	// 구슬의 위치 정보 갱신
		}

		ballFlag ^= 0b11;	// 다음 구슬 > 0b01 구슬 -> 0b10 구슬, 0b10 구슬 > 0b01 구슬
	}

	return;
}

void DFS(int depth){	// depth: 기울이는 동작 수

	if(depth > 10) return;	// 10번 보다 많은 동작 return
	if(ball[1].y == -1 && ball[1].x == -1 && ball[2].y != -1){	// 빨간 구슬은 구멍에 빠지고 파란 구슬은 구멍에 빠지지 않음
		ans = std::min(ans, depth);	// 최소 동작 수 갱신
		return;
	}
	if(ball[2].y == -1)	return;	// 파란 구슬이 구멍에 빠지면 return

	int tmpMAP[10][10];	// tmpMAP: 현재 보드 상태
	Coordinate tmpBall[3];	// tmpBall: 현재 구슬 위치
	memcpy(tmpMAP, MAP, sizeof(MAP));
	memcpy(tmpBall, ball, sizeof(ball));

	for(int dir=0; dir<4; dir++){	// 4가지 방향 탐색
		ballMove(dir);
		DFS(depth + 1);
		memcpy(MAP, tmpMAP, sizeof(MAP));	// 보드 원복
		memcpy(ball, tmpBall, sizeof(ball));	// 구슬 원복
	}
}

void sol(){
	DFS(0);
	if(ans == 21e8)	// 가능한 경우가 없으면 -1
		ans = -1;

	return;
}

void input(){
	std::cin >> N >> M;
	for(int j=0; j<N; j++){
		std::string s;	// s: 보드의 모양 한 행
		std::cin >> s;
		for(int i=0; i<M; i++){
			if(s[i] == '#')	// 벽: # -> -1
				MAP[j][i] = -1;
			if(s[i] == 'R'){	// 빨간 구슬: R -> 1
				MAP[j][i] = 1;
				ball[1] = {j, i};
			}
			if(s[i] == 'B'){	// 파란 구슬: B -> 2
				MAP[j][i] = 2;
				ball[2] = {j, i};
			}
			if(s[i] == 'O'){	// 구멍: O -> 3
				MAP[j][i] = 3;	// 보드에 표시할 필요는 없음
				hole = {j, i};
			}
		}
	}

	return;
}

int main(){
	input();
	sol();

	std::cout << ans;
	return 0;
}