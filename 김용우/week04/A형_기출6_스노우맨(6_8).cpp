#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

struct Edge {
	int y, x;	// y, x: 다음 갈 수 있는 곳
	int cost;	// cost: 가는데 드는 비용
};

int N, M;	// N: 맵의 세로크기, M: 맵의 가로 크기
int MAP[51][51];	// MAP[j][i]: j행 i열의 값
std::vector<Edge> v[51][51];	// v[j][i]: j행 i열의 칸에서 연결되는 칸 -> 최대 4개
int sy, sx;	// sy: 스노우맨의 시작 y위치, sx: 스노우맨의 시작 x위치
int dy, dx;	// dy: 보석의 y위치, dx: 보석의 x위치
int limit = 21e8;	// limit: 수직상승 게이지의 LIMIT
int visited[51][51];	// visited: 방문 체크

void DFS(int nowY, int nowX, int cost) {

	if (nowY == dy && nowX == dx) {	// 보석의 위치에 도착 했다면
		limit = std::min(limit, cost);	// 지금까지의 거리와 비교하여 더 적으면 변경
		return;
	}
	
	for (int i = 0; i < v[nowY][nowX].size(); i++) {
		int newY = v[nowY][nowX][i].y;	// newY: 다음 이동할 y 좌표
		int newX = v[nowY][nowX][i].x;	// newX: 다음 이동할 x 좌표

		if (visited[newY][newX] == 1) continue;	// 이미 방문 헀다면 continue
		

		int newCost = v[nowY][nowX][i].cost;	// newCost: newY, newX로 가기위한 비용
		if (newCost >= limit) continue;	// 이미 구한 최소값 보다 같거나 더 먼 거리는 갈 필요 없으니 continue
				
		visited[newY][newX] = 1;		
		DFS(newY, newX, std::max(cost, newCost));	// 지금까지 경로 중 가장 먼 거리 넘겨점
		visited[newY][newX] = 0;
	}
}

void sol() {
	memset(visited, 0, sizeof(visited));
	visited[sy][sx] = 1;
	DFS(sy, sx, 0);
}

void input() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			std::cin >> MAP[j][i];
			if (MAP[j][i] == 2) {	// 시작 위치 저장
				sy = j;
				sx = i;
			}
			if (MAP[j][i] == 3) {	// 도착 위치 저장
				dy = j;
				dx = i;
			}
		}
	}
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			if (MAP[j][i] == 0) continue;
			int leftFlag = 0, rightFlag = 0;
			int upFlag = 0, downFlag = 0;

			int left = i - 1;	// 왼쪽 한 칸
			int right = i + 1;	// 오른쪽 한 칸
			int up, down;	// 위와 아래는 몇 칸을 가야하는지 모름

			if (left >= 0 && MAP[j][left] != 0)	// 왼쪽이 범위를 벗어나지 않고, 땅이 있다면
				v[j][i].push_back({ j, left, 0 });

			if (right < M && MAP[j][right] != 0)	// 오른쪽이 범위를 벗어나지 않고, 땅이 있다면
				v[j][i].push_back({ j, right, 0 });

			for (int d = 1; d <= N; d++) {	// 1칸부터 시작해 위로 최대한 가봄
				up = j - d;
				if (up < 0) break;	// 범위를 벗어나면 반복 종료
				if (MAP[up][i] != 0) {	// 땅이 있다면 넣고 종료
					v[j][i].push_back({ up, i, d });
					break;
				}
			}
			
			for (int d = 1; d <= N; d++) {	// 1칸부터 시작해 아래로 최대한 가봄
				down = j + d;
				if (down >= N) break;	// 범위를 벗어나면 반복 종료
				if (MAP[down][i] != 0) {	// 땅이 있다면 넣고 종료
					v[j][i].push_back({ down, i, d });
					break;
				}
			}

		}
	}
}

int main() {
	input();
	sol();	
	std::cout << limit;

	int da = 1;
	return 0;
}