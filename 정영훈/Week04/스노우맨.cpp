// 좌우로는 땅이 있는 곳으로만 이동 가능
// 땅이 없는 곳은 좌우 이동 x

// 수직이동도 있음(수직이동 중에는 좌우 이동 X)
// 수직이동을 할 때마다 게이지가 차며, 게이지가 LIMIT를 넘으면 녹아서 죽음

// 플레이어는 수직 이동 게이지의 LIMIT를 정할 수 있음.
// LIMIT을 작게 설정하면 더 높은 점수를 얻을 수 있음.
// 보석을 먹기 위한 최소 LIMIT를 구하시오 -> 그냥 길 찾기?

/*
1. 시작점에서 보석까지 도달할 수 없는 경우는 주어지지 않습니다.
2. 맵의 맨 하단부는 모든 칸들이 빈칸 없이 땅으로 되어있습니다.
3. 보석의 위치가 하단부의 바로 위에 주어지는 입력은 없습니다.
( 0 행이 상단, N - 1 행이 하단부일 때  N - 2 행에 주어지는 경우는 없다)
*/

// 게이지 최대양으로 pq

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 1000000000;
int N, M; // 가로 세로

struct PQInfo {
	int x, y;
	int maxGauge;
	int curGauge;
	PQInfo(int x, int y, int m, int c) : x(x), y(y), maxGauge(m), curGauge(c) {}
	bool operator<(const PQInfo& other) const {
		return this->maxGauge > other.maxGauge; // min heap
	}
};

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin >> N >> M;
	vector<vector<int>> Map(N, vector<int>(M, 0));
	vector<vector<int>> distMap(N, vector<int>(M, INF));

	coord snowMan(0, 0), jewel(0, 0);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> Map[i][j];
			if (Map[i][j] == 2) {
				snowMan.x = i;
				snowMan.y = j;
			}
			if (Map[i][j] == 3) {
				jewel.x = i;
				jewel.y = j;
			}
		}
	}

	priority_queue<PQInfo> pq;
	pq.push(PQInfo(snowMan.x, snowMan.y, 0, 0)); // 시작
	distMap[snowMan.x][snowMan.y] = 0;

	int dx[]{ -1,1,0,0 };
	int dy[]{ 0,0,-1,1 };

	int ans = 21e8;
	while (!pq.empty()) {
		auto now = pq.top(); pq.pop();

		if (now.x == jewel.x && now.y == jewel.y) { // 끝 도달 시 갱신
			ans = min(ans, now.maxGauge);
			// cout << now.maxGauge << endl;
			continue;
		}

		for (int d = 0; d < 4; ++d) {
			int nx = now.x + dx[d];
			int ny = now.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue; // 범위 밖

			if (d < 2) { // 상하
				int Max = max(now.curGauge + 1, now.maxGauge);
				if (distMap[nx][ny] <= Max) continue;
				distMap[nx][ny] = Max;
				if (Map[nx][ny] == 1) {
					pq.push(PQInfo(nx, ny, distMap[nx][ny], 0)); // 땅있으면 current gauge를 0으로 초기화
				}
				else {
					pq.push(PQInfo(nx, ny, distMap[nx][ny], now.curGauge + 1)); // 땅이 없으니 current guage 누적
				}
				
			}
			else { // 좌우
				if (Map[now.x][now.y] != 0) { // 공중에서는 갈 수 없음
					if (Map[nx][ny] == 0) continue; // 히히 못 가

					if (distMap[nx][ny] <= now.maxGauge) continue;
					distMap[nx][ny] = now.maxGauge;
					pq.push(PQInfo(nx, ny, distMap[nx][ny], 0)); // 땅이 있으니 curreng guage를 0으로 초기화
				}
			}
		}
	}
	cout << ans << endl;

	return 0;
}