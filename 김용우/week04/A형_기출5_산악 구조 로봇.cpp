#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>

struct Node {	// 좌표 정보
	int y, x;
};

struct Tunnel {	// 터널 비용을 포함한 터널 정보
	int y, x, c;
};

int N;	// N: 지도의 한 변의 길이
int M; // M: 터널의 개수
int MAP[31][31];	// MAP: 지도
int cost[31][31];	// cost: 연료 소모
std::vector<Tunnel> tunnel[31][31];	// tunnel: 터널 정보

// 방향 벡터
int dirY[] = { -1,1,0,0 };
int dirX[] = { 0,0,-1,1 };


void sol() {
	std::queue<Node> q;

	q.push({ 0,0 });
	cost[0][0] = 0;

	while (!q.empty()) {
		Node cur = q.front();
		q.pop();

		int newY;	// newY: 이동할 y 좌표
		int newX;	// newX: 이동할 x 좌표
		int tunnelCost;	// tunnelCost: 터널 사용 비용

		if (!tunnel[cur.y][cur.x].empty()) {	// 현재 위치에 사용할 수 있는 터널이 있는가?
			for (int i = 0; i < tunnel[cur.y][cur.x].size(); i++) {	// 터널이 있다면 터널 수 만큼 시도
				newY = tunnel[cur.y][cur.x][i].y;	// 터널로 이동한 y 좌표
				newX = tunnel[cur.y][cur.x][i].x;	// 터널로 이동한 x 좌표
				tunnelCost = tunnel[cur.y][cur.x][i].c;	// 터널 사용 비용

				if (cost[newY][newX] > cost[cur.y][cur.x] + tunnelCost) {	// 터널을 사용한 것이 더 저렴한가?
					cost[newY][newX] = cost[cur.y][cur.x] + tunnelCost;	// 갱신
					q.push({ newY, newX });
				}
			}
		}

		for (int dir = 0; dir < 4; dir++) {	// 4가지 방향으로 진행
			newY = cur.y + dirY[dir];
			newX = cur.x + dirX[dir];

			if (newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어남

			int tempCost;
			if (MAP[cur.y][cur.x] < MAP[newY][newX]) {	// 오르막길
				tempCost = (MAP[newY][newX] - MAP[cur.y][cur.x]) * 2;
			}
			else if (MAP[cur.y][cur.x] == MAP[newY][newX]) {	// 평지
				tempCost = 1;
			}
			else {	// 내리막길
				tempCost = 0;
			}
			
			if (cost[newY][newX] > cost[cur.y][cur.x] + tempCost) {	// 이번에 이동한 경로가 더 저렴한가?
				cost[newY][newX] = cost[cur.y][cur.x] + tempCost;	// 갱신
				q.push({ newY, newX });
			}
		}
	}
}

void input() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> MAP[j][i];
		}
	}
	for (int i = 0; i < M; i++) {
		int y1, x1, y2, x2, c;	// 터널 좌표와 비용 -> index가 1부터 시작하기 때문에 1씩 빼서 사용
		std::cin >> y1 >> x1 >> y2 >> x2 >> c;
		tunnel[y1-1][x1-1].push_back({ y2-1, x2-1, c });
		tunnel[y2-1][x2-1].push_back({ y1-1, x1-1, c });	// 터널은 양방향이 가능
	}

	return;
}

void reset() {	// 초기화
	N = 0;
	M = 0;
	memset(MAP, 0, sizeof(MAP));
	for (int j = 0; j < 31; j++) {
		for (int i = 0; i < 31; i++) {
			cost[j][i] = 21e8;
			tunnel[j][i].clear();
		}
	}
	

	return;
}

int main() {
	int T;	// T: 테스트 케이스

	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		sol();				
		std::cout << "#" << tc << " " << cost[N-1][N-1] << std::endl;	// 조난자 좌표의 비용
	}

	return 0;
}