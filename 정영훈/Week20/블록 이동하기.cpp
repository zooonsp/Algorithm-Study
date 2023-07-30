/*
https://yabmoons.tistory.com/628
준비 중인 로봇은 2 x 1 크기의 로봇으로 "무지"는 "0"과 "1"로 이루어진 N x N 크기의 지도에서
2 x 1 크기인 로봇을 움직여 (N, N) 위치까지 이동 할 수 있도록 프로그래밍하려 함.
바꿔서 (0, 0)에서 (N - 1, N - 1)로

도착점에 가까운 좌표를 기준점으로 visited 확인
로봇은 벽이 있는 칸 또는 지도 밖으로는 이동할 수 없습니다
로봇은 처음에 아래 그림과 같이 좌표 (1, 1) 위치에서 가로방향으로 놓여있는 상태로 시작하며,
앞뒤 구분없이 움직일 수 있습니다.
*/

#include <bits/stdc++.h>

using namespace std;
constexpr int HORIZONTAL = 0;
constexpr int VERTICAL = 1;
constexpr int INF = 1 << 30;
struct Robot {
	int x, y, dir, time;
	Robot(int x, int y, int dir, int time) : x(x), y(y), dir(dir), time(time) {}
	bool operator<(const Robot& other) const {
		return this->time > other.time;
	}
};
constexpr int dx[]{ -1,1,0,0 };
constexpr int dy[]{ 0,0,-1,1 };


int solution(vector<vector<int>> board) {
	int answer = INF;
	const int SIZE = static_cast<int>(board.size());

	vector<vector<vector<int>>> visited(SIZE, vector<vector<int>>(SIZE, vector<int>(2, INF)));
	priority_queue<Robot> q;
	q.emplace(0, 1, HORIZONTAL, 0); // start
	visited[0][1][HORIZONTAL] = 0;

	while (!q.empty()) {
		// auto[x, y, dir, time] = q.front(); q.pop();
		Robot rob = q.top(); q.pop();
		int x = rob.x, y = rob.y, dir = rob.dir, time = rob.time;
		int otherX{ x }, otherY{ y };

		// if (time != visited[x][y][dir]) continue;

		if (dir == HORIZONTAL) {
			otherY--;
		}
		else {
			otherX--;
		}

		if ((x == SIZE - 1 && y == SIZE - 1) || (otherX == SIZE - 1 && otherY == SIZE - 1)) {
			answer = time;
			// answer = min(answer, time);
			break;
		}

		int nextTime = time + 1;

		for (int d{}; d < 4; ++d) { // 모양 유지하면서 4방향 이동 가능한지 확인
			int nx = x + dx[d], ny = y + dy[d];
			int otherNx = otherX + dx[d], otherNy = otherY + dy[d];
			if (nx < 0 || nx >= SIZE || ny < 0 || ny >= SIZE) continue;
			if (otherNx < 0 || otherNx >= SIZE || otherNy < 0 || otherNy >= SIZE) continue;

			// 이거 두 줄?.. 빼먹어서 ㅇ으어러어렁러어어ㅓ
			if (board[nx][ny] == 1) continue;
			if (board[otherNx][otherNy] == 1) continue;

			if (visited[nx][ny][dir] <= nextTime) continue;
			visited[nx][ny][dir] = nextTime;
			q.emplace(nx, ny, dir, nextTime);
		}

		if (dir == HORIZONTAL) {
			if (x > 0 && board[x - 1][y] == 0) {
				if (board[x - 1][y - 1] == 0) {
					if (visited[x][y - 1][VERTICAL] > nextTime) { // 1
						visited[x][y - 1][VERTICAL] = nextTime;
						q.emplace(x, y - 1, VERTICAL, nextTime);
					}
				}
			}
			if(x + 1 < SIZE && board[x + 1][y] == 0) {
				if (board[x + 1][y - 1] == 0) {
					if (visited[x + 1][y - 1][VERTICAL] > nextTime) { // 2
						visited[x + 1][y - 1][VERTICAL] = nextTime;
						q.emplace(x + 1, y - 1, VERTICAL, nextTime);
					}
				}
			}
			if (x > 0 && board[x - 1][y] == 0) {
				if (board[x - 1][y - 1] == 0) { // 3
					if (visited[x][y][VERTICAL] > nextTime) {
						visited[x][y][VERTICAL] = nextTime;
						q.emplace(x, y, VERTICAL, nextTime);
					}
				}
			}
			if (x + 1 < SIZE && board[x + 1][y] == 0) {
				if (board[x + 1][y - 1] == 0) { // 4
					if (visited[x + 1][y][VERTICAL] > nextTime) {
						visited[x + 1][y][VERTICAL] = nextTime;
						q.emplace(x + 1, y, VERTICAL, nextTime);
					}
				}
			}
		}
		else { // dir == VERTICAL
			if (y > 0 && board[x][y - 1] == 0) {
				if (board[x - 1][y - 1] == 0) {
					if (visited[x - 1][y][HORIZONTAL] > nextTime) { // 1
						visited[x - 1][y][HORIZONTAL] = nextTime;
						q.emplace(x - 1, y, HORIZONTAL, nextTime);
					}
				}
			}
			if (y + 1 < SIZE && board[x][y + 1] == 0) {
				if (board[x - 1][y + 1] == 0) {
					if (visited[x - 1][y + 1][HORIZONTAL] > nextTime) { // 2
						visited[x - 1][y + 1][HORIZONTAL] = nextTime;
						q.emplace(x - 1, y + 1, HORIZONTAL, nextTime);
					}
				}
			}
			if (y > 0 && board[x][y - 1] == 0) {
				if (board[x - 1][y - 1] == 0) {
					if (visited[x][y][HORIZONTAL] > nextTime) { // 3
						visited[x][y][HORIZONTAL] = nextTime;
						q.emplace(x, y, HORIZONTAL, nextTime);
					}
				}
			}
			if (y + 1 < SIZE && board[x][y + 1] == 0) {
				if (board[x - 1][y + 1] == 0) {
					if (visited[x][y + 1][HORIZONTAL] > nextTime) { // 4
						visited[x][y + 1][HORIZONTAL] = nextTime;
						q.emplace(x, y + 1, HORIZONTAL, nextTime);
					}
				}
			}
		}
	}

	return answer;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
	vector<vector<int>> board{ {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };

	cout << solution(board) << '\n';

	return 0;
}
