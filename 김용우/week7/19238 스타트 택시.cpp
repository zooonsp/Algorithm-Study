#include <iostream>
#include <queue>

struct Coordinate{	// 좌표
	int y, x;
};

struct Passenger{	// 승객의 출발 위치와 도착 위치
	Coordinate start, end;
};

struct Distance{	// 위치와 거리
	Coordinate point;
	int distance;

	bool operator < (Distance next) const {
		// 현재 위에 최단거리가 가장 짧은 승객
		if(distance < next.distance) return false;
		if(distance > next.distance) return true;

		// 행 번호가 가장 작은 승객
		if(point.y < next.point.y) return false;
		if(point.y > next.point.y) return true;

		// 열 번호가 가장 작은 승객
		if(point.x < next.point.x) return false;
		if(point.x > next.point.x) return true;

		return false;
	}
};

int N, M, F;	// N: 격자 한 변의 길이, M: 승객의 수, F: 초기 연료
int MAP[20][20];	// MAP[i][j]: 격자 i행 j열 정보 -> 빈칸 0, 벽 1
Coordinate baekjoon;	// baekjoon: 택시 기사 최백준의 위치
Passenger passenger[400];	// passenger[i]: i 승객의 출발지와 도착지
int passengerDAT[400];	// passengerDAT[i]: i 승객의 완료 여부 -> 완료 0, 미완료 1
int ans;	// ans: 남은 연료의 양 -> 이동 도중 연료가 바닥나는 등 모든 손님을 이동시킬 수 없는 경우 -1

// 방항 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

void sol(){

	while(F>=0){	// 이동하는 도중에 연료가 바닥나면 실패

		// 승객 고르기
		int pY, pX, pN, pD;	// pY, pX: 승객의 위치, pN: 승객 번호, pD: 택시 기사에서 승객까지의 거리
		int tmpMAP[20][20] = {0, };	// tmpMAP[i][j]: 격자 정보 복사
		std::priority_queue<Distance> pq;	// pq: 승객 까지의 거리

		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				tmpMAP[j][i] = MAP[j][i];
			}
		}
		int flag = 0;
		for(int i=0; i<M; i++){
			if(passengerDAT[i] == 0) continue;	// 이미 목적지에 도착한 승객 continue
			flag = 1;
			Coordinate startPoint = passenger[i].start;
			tmpMAP[startPoint.y][startPoint.x] = 1000 + i;	// 승객은 최대 400명 이므로 승객 ID를 저장하기 위해 1000번 부터 tmpMAP에 표시
		}
		if(flag == 0){	// 모든 승객이 도착한 상태라면
			ans = F;	// 남은 연료 return
			return;
		}
		
		pq.push({baekjoon.y, baekjoon.x, 0});	// 택시 기사 위치 pq에 넣음
		if(tmpMAP[baekjoon.y][baekjoon.x] == 0)	// 택시 기사 위치에 승객이 있는 경우도 있으므로 빈 칸일 경우에만 1로 표시
			tmpMAP[baekjoon.y][baekjoon.x] = 1;

		pD = -1;	// pD가 -1인 상태로 아래의 while문이 종료된다면 택시 기사가 태울 수 있는 승객 없음
		while(!pq.empty()){
			int curY = pq.top().point.y;	// curY: 현재 y 좌표
			int curX = pq.top().point.x;	// curX: 현재 x 좌표
			int curD = pq.top().distance;	// curD: 택시 기사부터 승객까지의 거리
			pq.pop();

			if(tmpMAP[curY][curX] >= 1000){	// 현재 위치에 승객이 있다면
				pN = tmpMAP[curY][curX] % 1000;	// 승객 번호
				pY = curY;	// 승객 y 좌표
				pX = curX;	// 승객 x 좌표
				pD = curD;	// 승객까지의 거리
				break;
			}

			for(int dir=0; dir<4; dir++){
				int newY = curY + dirY[dir];	// newY: 확인할 y좌표
				int newX = curX + dirX[dir];	// newX: 확인할 x좌표
				int newD = curD + 1;	// newD: (newY, newX) 까지의 최단 거리

				if(newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어나면 continue
				if(tmpMAP[newY][newX] == -1) continue;	// 벽이면 continue
				if(tmpMAP[newY][newX] == 1) continue;	// 이미 방문한 곳이면 continue
				
				if(tmpMAP[newY][newX] == 0)	// 빈 칸일 경우 1로 방문 표시 -> 승객 ID가 있을 수 있으므로
					tmpMAP[newY][newX] = 1;
				
				pq.push({{newY, newX}, newD});
			}
		}
		if(pD == -1){	// 현재 위치에서 손님을 태우지 못하는 경우
			ans = -1;
			return;
		}
		if(F < pD){	// 현재 위치에서 손님의 위치까지 연료가 모자른 경우
			ans = -1;
			return;
		}

		F -= pD;	// 연료 갱신
		baekjoon.y = pY;	// 택시 기사 y좌표 갱신
		baekjoon.x = pX;	// 택시 기사 x좌표 갱신
		passengerDAT[pN] = 0;	// 승객을 태웠으므로 승객 완료 여부 표시

		// 승객 목적지까지
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				tmpMAP[j][i] = MAP[j][i];
			}
		}
		while(!pq.empty()){	// pq 초기화
			pq.pop();
		}

		pq.push({baekjoon.y, baekjoon.x, 0});	// 택시 기사 위치 pq에 넣음
		tmpMAP[baekjoon.y][baekjoon.x] = 1;	// 위치 1로 표시

		pD = -1;	// pD가 -1인 상태로 아래의 while문이 종료된다면 승객의 목적지로 갈 수 없음
		while(!pq.empty()){
			int curY = pq.top().point.y;	// curY: 현재 y좌표
			int curX = pq.top().point.x;	// curX: 현재 x좌표
			int curD = pq.top().distance;	// curD: 현재 위치에서 승객의 목적지 까지의 거리
			pq.pop();

			if(curY == passenger[pN].end.y && curX == passenger[pN].end.x) {	// 목적지 도착
				pD = curD;
				break;
			}

			for(int dir=0; dir<4; dir++){
				int newY = curY + dirY[dir];	// newY: 확인해 볼 y좌표
				int newX = curX + dirX[dir];	// newX: 확인해 볼 x좌표
				int newD = curD + 1;	// newD: (newY, newX) 까지의 거리

				if(newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어나면 continue

				if(tmpMAP[newY][newX] != 0) continue;	// 빈칸이 아니면 continue

				tmpMAP[newY][newX] = 1;	// 방문 표시

				pq.push({{newY, newX}, newD});
			}

		}
		if(pD == -1){
			ans = -1;
			return;
		}
		if(F < pD){
			ans = -1;
			return;
		}

		F -= pD;	// 연료 감소
		// 택시 기사 위치 이동
		baekjoon.y = passenger[pN].end.y;
		baekjoon.x = passenger[pN].end.x;

		// 승객을 태우고 이동한 거리의 2배 만큼 연료 추가
		F += pD * 2;		
	}

	return;
}

void input(){
	std::cin >> N >> M >> F;
	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			std::cin >> MAP[j][i];
			if(MAP[j][i] == 1)	// 벽은 MAP에 -1로 표시
				MAP[j][i] = -1;
		}
	}
	// 문제에서의 좌표는 (1, 1) ~ (N, N)으로 표시하기 때문에 y 좌표와 x 좌표 1씩 감소
	std::cin >> baekjoon.y >> baekjoon.x;
	baekjoon.y--;
	baekjoon.x--;
	for(int i=0; i<M; i++){
		std::cin >> passenger[i].start.y >> passenger[i].start.x >> passenger[i].end.y >> passenger[i].end.x;
		passenger[i].start.y--;
		passenger[i].start.x--;
		passenger[i].end.y--;
		passenger[i].end.x--;
		passengerDAT[i] = 1;
	}

	return;
}

int main(){
	input();
	sol();
	std::cout << ans;

	return 0;
}