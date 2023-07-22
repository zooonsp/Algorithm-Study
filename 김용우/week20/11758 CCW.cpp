#include <iostream>

struct Coordinate{	// 점의 좌표
	int y, x;	// y, x: 좌표
};

Coordinate P[3];	// P[i]: i 점의 좌표
int ans;	// ans: 순서대로 이은 선분이 반시계 방향을 나타내면 1, 시계 방향이면 -1, 일직선이면 0

int cross(int x1, int y1, int x2, int y2){	// x1, y1: P1과 P2의 벡터, x2, y2: P1과 P3의 벡터
	return x1 * y2 - x2 * y1;	// 두 벡터의 외적
}

void solution(){

	int c = cross(P[1].x - P[0].x, P[1].y - P[0].y, P[2].x - P[0].x, P[2].y - P[0].y);	// c: 두 벡터의 외적

	if(c > 0) ans = 1;	// 외적의 값이 0보다 크면 반시계 방향
	else if(c < 0) ans = -1;	// 외적의 값이 0보다 작으면 시계 방향
	else ans = 0;	// 외적의 값이 0이면 일직선 -> c == 0

	return;
}

void input(){

	std::cin >> P[0].x >> P[0].y;
	std::cin >> P[1].x >> P[1].y;
	std::cin >> P[2].x >> P[2].y;

	return;
}

int main(){

	input();

	solution();

	std::cout << ans;

	return 0;
}