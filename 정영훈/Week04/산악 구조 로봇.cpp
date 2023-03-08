// 연료 소모를 최대한 적게 - pq
// 연료 소모량은 다음과 같음
// 각 칸의 값은 땅의 높이를 표현하며, 구조 로봇은 상, 하, 좌, 우 방향으로만 이동이 가능
/*
내리막길은 X
오르막길은 높이 차이의 2배
평지는 1
*/

// M개의 터널이 존재
// (x1,y1) -> (x2, y2) C의 연료 소모

// 출발지는 항상 (1,1) -> (0,0)
// 조난자의 위치는 (N, N) -> (N-1, N-1)

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1000000000;

struct TunnelInfo { // 단방향이라 가는 것만 저장할 거임
	int toX, toY;
	int cost;
	TunnelInfo(int x, int y, int c) : toX(x), toY(y), cost(c) {}
};

struct PQInfo {
	int x, y, dist;
	PQInfo(int x, int y, int dist) : x(x), y(y), dist(dist) {}
	bool operator< (const PQInfo& other) const {
		return dist > other.dist; // min heap
	}
};

vector<vector<int>> Map; // input
vector<vector<vector<int>>> tunnelMap; // 좌표별 터널 정보 저장(인덱스로)
vector<TunnelInfo> tunnels; // 터널 정보 저장

int N, M; // 지도 크기, 터널 개수

int solve() {
	int ret{ INF }; // 리턴할 최종값
	vector<vector<int>> distMap(N, vector<int>(N, INF)); // 좌표별 거리 저장
	
	priority_queue<PQInfo> pq;
	distMap[0][0] = 0;
	pq.push(PQInfo(0, 0, 0));

	int dx[]{ -1,1,0,0 };
	int dy[]{ 0,0,-1,1 };

	while (!pq.empty()) {
		auto now = pq.top(); pq.pop();

		if (now.x == N - 1 && now.y == N - 1) {
			// 최소값으로 조난자 위치에 도달
			
			// 답을 찾고 그냥 return해도 되는지는 모르겠음.
			ret = min(ret, now.dist);
			continue; // 이미 도착한 점에서는 갱신할 필요 없음
		}

		if (now.dist != distMap[now.x][now.y]) continue; // 최단 거리 정보가 아님

		// 단순한 상하좌우 이동
		for (int d = 0; d < 4; ++d) {
			int nx = now.x + dx[d];
			int ny = now.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue; // 범위 밖
			int oil{}; // now -> next 까지의 비용
			
			if (Map[nx][ny] > Map[now.x][now.y]) oil = (Map[nx][ny] - Map[now.x][now.y]) * 2; // 오르막
			else if (Map[nx][ny] == Map[now.x][now.y]) oil = 1; // 평지

			int ndist = distMap[now.x][now.y] + oil; // 새 비용
			if (distMap[nx][ny] <= ndist) continue; // 이미 다른 최단 거리가 있어
			distMap[nx][ny] = ndist;
			pq.push(PQInfo(nx, ny, ndist));
		}
		// 터널
		if (!tunnelMap[now.x][now.y].empty()) { // 터널 정보가 있다면~
			for (int& i : tunnelMap[now.x][now.y]) { // i = tunnels의 index들
				int nx = tunnels[i].toX;
				int ny = tunnels[i].toY;
				// 터널은 범위 밖으로 나갈 수 없으니 범위 조건은 생략

				int ndist = distMap[now.x][now.y] + tunnels[i].cost;
				if (distMap[nx][ny] <= ndist) continue; // 이미 다른 최단 경로가 있어

				distMap[nx][ny] = ndist;
				pq.push(PQInfo(nx, ny, ndist));
			}
		}
	}

	return ret;
}

int main() {
	int T;
	cin >> T;
	for (int tc{ 1 }; tc <= T; ++tc) {
		// reset
		tunnels.clear(); // 초기화를 똑바로 하자

		// input
		cin >> N >> M;
		Map.assign(N, vector<int>(N, 0));
		tunnelMap.assign(N, vector<vector<int>>(N));
		tunnels.reserve(2 * M); // 양방향 터널
		// tunnels.assign(2 * M, TunnelInfo(0,0,0)); // 양방향 터널
		for (auto& row : Map) {
			for (int& i : row) {
				cin >> i;
			}
		}

		int tunnelIndex{};
		for(int m=0;m<M;++m) {
			int x1, y1, x2, y2, cost;
			cin >> x1 >> y1 >> x2 >> y2 >> cost;
			x1--; y1--; x2--; y2--; // 문제의 좌표와의 차이
			tunnels.push_back(TunnelInfo(x2, y2, cost));
			tunnels.push_back(TunnelInfo(x1, y1, cost));
			
			// 터널 방향이 양방향임에 주의하시오.
			tunnelMap[x1][y1].push_back(tunnelIndex++); // (x1,y1) -> (x2,y2)
			tunnelMap[x2][y2].push_back(tunnelIndex++); // (x2,y2) -> (x1,y1)
		}

		// solve
		int ans = solve();

		// output
		cout << "#" << tc << ' ' << ans << '\n';
	}

	return 0;
}

