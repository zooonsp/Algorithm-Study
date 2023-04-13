#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dx[]{ -1,1,0,0 };
int dy[]{ 0,0,-1,1 };
vector<string> Map;

enum class Direction {
	Up, Down, Left, Right
};

const int Up = static_cast<int>(Direction::Up);
const int Down = static_cast<int>(Direction::Down);
const int Left = static_cast<int>(Direction::Left);
const int Right = static_cast<int>(Direction::Right);


struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	// coord() = default;
};

coord R(0, 0), B(0, 0);

struct RBPlace {
	coord r;
	coord b;
	int cnt; // 움직인 횟수
	RBPlace(coord r, coord b, int cnt) : r(r), b(b), cnt(cnt) {}
};

int N, M;

void MoveBalls(coord& first, coord& second, int dir) {
	// first 먼저 이동
	bool firstFinish = false, secondFinish = false;
	bool firstGoal = false, secondGoal = false;
	while (!firstFinish || !secondFinish) {
		coord firstNext = { first.x + dx[dir], first.y + dy[dir] };
		if(!firstFinish) {
			if (Map[firstNext.x][firstNext.y] == 'O') {
				firstFinish = true;
				firstGoal = true;
				first = firstNext;
			}
			else if (Map[firstNext.x][firstNext.y] == '#') { // 벽
				firstFinish = true;
			}
			else { // 그 외엔 이동
				first = firstNext;
			}
		}
		coord secondNext = { second.x + dx[dir], second.y + dy[dir] };
		if (!secondFinish) {
			if (Map[secondNext.x][secondNext.y] == 'O') {
				secondFinish = true;
				secondGoal = true;
				second = secondNext;
			}
			else if (Map[secondNext.x][secondNext.y] == '#' || 
				(secondNext.x == first.x && secondNext.y == first.y)) { // 벽
				secondFinish = true;
			}
			else {
				second = secondNext;
			}
		}
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	
	cin >> N >> M;
	// vector<string> Map(N);
	Map.assign(N, "");
	for (int n = 0; n < N;++n) {
		cin >> Map[n];
		for (int m = 0; m < M; ++m) {
			if (Map[n][m] == 'R') {
				R = {n, m};
				// R = { .x = n, .y = m }; 왜 에러..
			}
			else if(Map[n][m] == 'B') {
				B = { n,m };
			}
		}
	}

	queue<RBPlace> q;
	q.push(RBPlace(R, B, 0));

	while (!q.empty()) {
		RBPlace now = q.front(); q.pop();
		if (now.cnt == 10) continue;
		RBPlace nowCopy = now;
		for(int dir=0;dir<4;++dir) {
			now = nowCopy;
			if (dir == Up) {
				if (now.b.x <= now.r.x) {
					MoveBalls(now.b, now.r, dir);
				}
				else {
					MoveBalls(now.r, now.b, dir);
				}

				if ((Map[now.r.x][now.r.y] == 'O' && Map[now.b.x][now.b.y] == 'O')
					|| Map[now.b.x][now.b.y] == 'O') {
					continue;
				}
				else if (Map[now.r.x][now.r.y] == 'O') {
					cout << now.cnt + 1 << '\n';
					return 0;
				}
				else {
					if (now.r.x == nowCopy.r.x && now.r.y == nowCopy.r.y
						&& now.b.x == nowCopy.b.x && now.b.y == nowCopy.b.y) continue;
					q.push(RBPlace(now.r, now.b, now.cnt + 1));
				}
			}
			else if (dir == Down) {
				if (now.b.x >= now.r.x) {
					MoveBalls(now.b, now.r, dir);
				}
				else {
					MoveBalls(now.r, now.b, dir);
				}

				if ((Map[now.r.x][now.r.y] == 'O' && Map[now.b.x][now.b.y] == 'O')
					|| Map[now.b.x][now.b.y] == 'O') {
					continue;
				}
				else if (Map[now.r.x][now.r.y] == 'O') {
					cout << now.cnt + 1 << '\n';
					return 0;
				}
				else {
					if (now.r.x == nowCopy.r.x && now.r.y == nowCopy.r.y
						&& now.b.x == nowCopy.b.x && now.b.y == nowCopy.b.y) continue;
					q.push(RBPlace(now.r, now.b, now.cnt + 1));
				}
			}
			else if (dir == Left) {
				if (now.b.y <= now.r.y) {
					MoveBalls(now.b, now.r, dir);
				}
				else {
					MoveBalls(now.r, now.b, dir);
				}

				if ((Map[now.r.x][now.r.y] == 'O' && Map[now.b.x][now.b.y] == 'O')
					|| Map[now.b.x][now.b.y] == 'O') {
					continue;
				}
				else if (Map[now.r.x][now.r.y] == 'O') {
					cout << now.cnt + 1 << '\n';
					return 0;
				}
				else {
					if (now.r.x == nowCopy.r.x && now.r.y == nowCopy.r.y
						&& now.b.x == nowCopy.b.x && now.b.y == nowCopy.b.y) continue;
					q.push(RBPlace(now.r, now.b, now.cnt + 1));
				}
			}
			else { // dir == Right
				if (now.b.y >= now.r.y) {
					MoveBalls(now.b, now.r, dir);
				}
				else {
					MoveBalls(now.r, now.b, dir);
				}

				if ((Map[now.r.x][now.r.y] == 'O' && Map[now.b.x][now.b.y] == 'O')
					|| Map[now.b.x][now.b.y] == 'O') {
					continue;
				}
				else if (Map[now.r.x][now.r.y] == 'O') {
					cout << now.cnt + 1 << '\n';
					return 0;
				}
				else {
					if (now.r.x == nowCopy.r.x && now.r.y == nowCopy.r.y
						&& now.b.x == nowCopy.b.x && now.b.y == nowCopy.b.y) continue;
					q.push(RBPlace(now.r, now.b, now.cnt + 1));
				}
			}
		}
	}
	cout << "-1\n";

	return 0;
}