/*
N x N 체스판, K개의 말.
이동방향은 상하좌우.
흰색 -> 그냥 올리기
빨간색 -> 뒤집어서 올리기
체스판 벗어나거나 파란색 -> 방향 반대로 한 칸이동(방향 바꾸고도 파란색이면 이동하지 않고 방향만 변경)

같은 칸에 말이 두 개 이상 있는 경우는 입력으로 주어지지 않는다.

턴이 진행되던 중에 말이 4개 이상 쌓이는 순간 게임이 종료된다.
게임이 종료되는 턴의 번호를 구해보자.
그 값이 1,000보다 크거나 절대로 게임이 종료되지 않는 경우에는 -1을 출력
*/

#include <bits/stdc++.h>

using namespace std;
constexpr int WHITE = 0;
constexpr int RED = 1;
constexpr int BLUE = 2;
constexpr int dx[]{ 0,0,-1,1 };
constexpr int dy[]{ 1,-1,0,0 };

struct piece{
	int num, x, y, d, floor;
	piece(int num, int x, int y, int d, int floor) : num(num), x(x), y(y), d(d), floor(floor) {}
};

bool MovePieces(vector<vector<vector<int>>>& curBoard, vector<piece>& pieces, int px,int py, int nx, int ny) {
	bool gameOver{ false };
	int floor = (int)curBoard[nx][ny].size();
	for (int i{}; i < (int)curBoard[px][py].size(); ++i) {
		int& pIdx = curBoard[px][py][i];
		curBoard[nx][ny].push_back(pIdx);
		pieces[pIdx - 1].x = nx;
		pieces[pIdx - 1].y = ny;
		pieces[pIdx - 1].floor = floor + i;
	}
	if (curBoard[nx][ny].size() >= 4) gameOver = true;
	vector<int>().swap(curBoard[px][py]); // swap with empty vector
	return gameOver;
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
	int N, K; // 체스판 크기, 말의 개수
	cin >> N >> K;
	vector<vector<int>> board(N + 2, vector<int>(N + 2, BLUE));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> board[i][j];
		}
	}
	
	vector<vector<vector<int>>> curBoard(N + 2, vector<vector<int>>(N + 2));
	vector<piece> pieces(K, piece(0, 0, 0, 0, 0));
	for (int k{}; k < K;++k) {
		piece& p = pieces[k];
		cin >> p.x >> p.y >> p.d;
		p.d--; // 1 ~ 4 -> 0 ~ 3
		p.num = k + 1;
		curBoard[p.x][p.y].push_back(k + 1); // index만 저장
	}

	int t = 1;
	bool gameOver{ false };
	for (;t<=1000; ++t) {
		for (int k{}; k < K; ++k) { // 한 턴
			piece& p = pieces[k]; 
			if (p.floor > 0) continue;
			int nx = p.x + dx[p.d], ny = p.y + dy[p.d];
			if (board[nx][ny] == BLUE) {
				// 방향 반대로 한 칸이동(방향 바꾸고도 파란색이면 이동하지 않고 방향만 변경)
				p.d^=1;
				nx = p.x + dx[p.d], ny = p.y + dy[p.d];
				if (board[nx][ny] == BLUE) continue;
			}
			if(board[nx][ny] == RED) {
				// 뒤집어서 올리기
				reverse(begin(curBoard[p.x][p.y]), end(curBoard[p.x][p.y]));
				gameOver = MovePieces(curBoard, pieces, p.x, p.y, nx, ny);
			}
			else { // WHITE
				// 그냥 올리기
				gameOver = MovePieces(curBoard, pieces, p.x, p.y, nx, ny);
			}
			if (gameOver) break;
		}
		if (gameOver) break;
	}

	if (gameOver) cout << t << '\n';
	else cout << "-1\n";

	return 0;
}