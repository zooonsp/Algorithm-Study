#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

enum { COL, ROW };
enum { DEL, ADD };

bool isValidCol(int x, int y, const vector<vector<vector<bool>>>& board) {
	if (y == 0) return true;
	if (board[x][y - 1][COL]) return true;
	if (x - 1 >= 0 && board[x - 1][y][ROW]) return true;
	if (board[x][y][ROW]) return true;
	return false;
}

bool isValidRow(int x, int y, const vector<vector<vector<bool>>>& board) {
	if (y - 1 >= 0 && board[x][y - 1][COL]) return true;
	if (y - 1 >= 0 && x + 1 < board.size() && board[x + 1][y - 1][COL]) return true;
	if (x - 1 >= 0 && x + 1 < board.size() && board[x - 1][y][ROW] && board[x + 1][y][ROW]) return true;
	return false;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector<vector<vector<bool>>> board(n + 1, vector<vector<bool>>(n + 1, vector<bool>(2)));

	for (auto bf : build_frame) {
		auto [x, y, buildType, cmd] = make_tuple(bf[0], bf[1], bf[2], bf[3]);

		if (cmd == DEL) {
			if (buildType == COL) {
				board[x][y][COL] = false;

				if (x - 1 >= 0 && y + 1 < board.size() && board[x - 1][y + 1][ROW] && !isValidRow(x - 1, y + 1, board))
					board[x][y][COL] = true;
				if (y + 1 < board.size() && board[x][y + 1][ROW] && !isValidRow(x, y + 1, board))
					board[x][y][COL] = true;
				if (y + 1 < board.size() && board[x][y + 1][COL] && !isValidCol(x, y + 1, board))
					board[x][y][COL] = true;
			}
			else if (buildType == ROW) {
				board[x][y][ROW] = false;

				if (x - 1 >= 0 && board[x - 1][y][ROW] && !isValidRow(x - 1, y, board))
					board[x][y][ROW] = true;
				if (x + 1 < board.size() && board[x + 1][y][ROW] && !isValidRow(x + 1, y, board))
					board[x][y][ROW] = true;
				if (board[x][y][COL] && !isValidCol(x, y, board))
					board[x][y][ROW] = true;
				if (x + 1 < board.size() && board[x + 1][y][COL] && !isValidCol(x + 1, y, board))
					board[x][y][ROW] = true;
			}
		}
		else if (cmd == ADD) {
			if (buildType == COL) {
				if (isValidCol(x, y, board)) {
					board[x][y][COL] = true;
				}
			}
			else if (buildType == ROW) {
				if (isValidRow(x, y, board)) {
					board[x][y][ROW] = true;
				}
			}
		}
	}

	for (int x = 0; x <= n; ++x) {
		for (int y = 0; y <= n; ++y) {
			auto [col, row] = make_pair(board[x][y][COL], board[x][y][ROW]);
			if (col) answer.push_back({ x, y, COL });
			if (row) answer.push_back({ x, y, ROW });
		}
	}

	return answer;
}
