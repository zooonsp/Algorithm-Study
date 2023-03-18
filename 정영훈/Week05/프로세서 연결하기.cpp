// N x N 개의 cell
// 1개의 cell에는 1개의 core or 1개의 전선이 올 수 있음.
// 가장 자리에는 전원이 흐르고 있음.
// Core와 전원을 연결하는 전선은 직선으로만 연결이 가능함.
// 전선은 절대로 교차해서는 안 된다.
// 가장자리에 위치한 Cores는 이미 전원이 연결된 것으로 간주함.

// 최대한 많은 Core에 전원은 연결하였을 경우, 전선 길이의 합을 구하고자 함.
// 단, 여러 방법이 있다면 전선 길이의 합이 최소가 되는 값을 구하기.

// 한 Core -> 4가지
// 4^12 = 16,777,216
// 16,777,216 * 60 = 1,006,632,960 : 2초에 가능함?

/*
3
7
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
int len, maxCore;
vector<vector<int>> board;
int dx[]{ -1,1,0,0 };
int dy[]{ 0,0,-1,1 };

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};
vector<coord> coords;
vector<int> isConnected;

void dfs(int now, int nowMaxCore, int nowLen) {
	// base case
	if (now == coords.size()) {
		if (maxCore < nowMaxCore) {
			maxCore = nowMaxCore;
			len = nowLen;
			
		}
		else if (maxCore == nowMaxCore) {
			len = min(len, nowLen);
		}
		/*cout << '\n';
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cout << board[i][j] << ' ';
			}
			cout << '\n';
		}
		int tmp{};*/
		return;
	}

	coord& coordNow = coords[now];
	if (!isConnected[now]) { // 가장자리가 아니여서 연결이 안 된 경우
		// UP
		bool chk{ false };
		int startX{ coordNow.x - 1 };
		for (; startX >= 0; --startX) {
			if (board[startX][coordNow.y]) { // != 0
				chk = true;
				for (int sX{ coordNow.x - 1 }; sX > startX; --sX) board[sX][coordNow.y] = 0; // reset
				break;
			}
			board[startX][coordNow.y] = 2; // 전선
		}
		if (!chk) {
			isConnected[now] = 1;
			dfs(now + 1, nowMaxCore + 1, nowLen + coordNow.x);
			isConnected[now] = 0;
			for (int sX{ coordNow.x - 1 }; sX > startX; --sX) board[sX][coordNow.y] = 0; // reset
		}


		// DOWN
		chk = false;
		startX = coordNow.x + 1;
		for (; startX < N; ++startX) {
			if (board[startX][coordNow.y]) { // != 0
				chk = true;
				for (int sX{ coordNow.x + 1 }; sX < startX; ++sX) board[sX][coordNow.y] = 0; // reset
				break;
			}
			board[startX][coordNow.y] = 2;
		}
		if (!chk) {
			isConnected[now] = 1;
			dfs(now + 1, nowMaxCore + 1, nowLen + N - 1 - coordNow.x);
			isConnected[now] = 0;
			for (int sX{ coordNow.x + 1 }; sX < startX; ++sX) board[sX][coordNow.y] = 0; // reset
		}

		// LEFT
		chk = false;
		int startY{ coordNow.y - 1 };
		for (; startY >= 0; --startY) {
			if (board[coordNow.x][startY]) { // != 0
				chk = true;
				for (int sY{ coordNow.y - 1 }; sY > startY; --sY) board[coordNow.x][sY] = 0; // reset
				break;
			}
			board[coordNow.x][startY] = 2; // 전선
		}
		if (!chk) {
			isConnected[now] = 1;
			dfs(now + 1, nowMaxCore + 1, nowLen + coordNow.y);
			isConnected[now] = 0;
			for (int sY{ coordNow.y - 1 }; sY > startY; --sY) board[coordNow.x][sY] = 0; // reset
		}

		// RIGHT
		chk = false;
		startY = coordNow.y + 1;
		for (; startY < N; ++startY) {
			if (board[coordNow.x][startY]) { // != 0
				chk = true;
				for (int sY{ coordNow.y + 1 }; sY < startY; ++sY) board[coordNow.x][sY] = 0; // reset
				break;
			}
			board[coordNow.x][startY] = 2;
		}
		if (!chk) {
			isConnected[now] = 1;
			dfs(now + 1, nowMaxCore + 1, nowLen + N - 1 - coordNow.y);
			isConnected[now] = 0;
			for (int sY{ coordNow.y + 1 }; sY < startY; ++sY) board[coordNow.x][sY] = 0; // reset
		}

		// not connect
		dfs(now + 1, nowMaxCore, nowLen);
	}
	else { // 이미 연결됨(테두리)
		dfs(now + 1, nowMaxCore + 1, nowLen);
	}
}

void solve() {
	dfs(0,0,0);
}

int main() {
	int T;
	ios::sync_with_stdio(false); // 있어도 없어도 시간 차이 그닥
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc{ 1 }; tc <= T; ++tc) {
		coords.clear();
		isConnected.clear();
		maxCore = 0;
		len = 0;
		cin >> N;
		board = vector<vector<int>>(N, vector<int>(N, 0));
		
		
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> board[i][j];
				if (board[i][j]) { // core
					coords.push_back(coord(i, j));
					if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
						// (멕시노스의 가장자리에 위치한 Core는 이미 전원이 연결된 것으로 간주한다.)
						isConnected.push_back(1);
						maxCore++;
					}
					else {
						isConnected.push_back(0);
					}
				}
			}
		}
		solve();
		int ans{ len };
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}