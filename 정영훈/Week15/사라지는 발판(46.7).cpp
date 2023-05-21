// 목표 : 양 플레이어가 몇 번 움직이게 될지 예측하기.
// 처음 캐릭터를 올려놓는 곳은 항상 발판이 존재함.
// 캐릭터는 발판이 있는 곳으로만 이동 가능 + 보드 밖으로는 이동 X
// 밟고 있던 발판은 그 위에 있던 캐릭터가 다른 곳으로 이동하여 다른 발판을 밟는 경우 사라짐.
// 양 플레이어는 번갈아가며 자신의 캐릭터를 상하좌우로 인접한 4개의 칸 중에서 발판이 있는 칸으로 옮겨야 함.

// 승패 결정
// 1. 움직일 차례인데 갈 수 있는 곳이 없는 경우 => 패배
// 2. 두 캐릭터가 같은 발판 위일 때, 다른 플레이어가 다른 발판으로 이동 시 현재 발판 사라지며 패배

// 게임은 항상 A가 시작하며, 양 플레이어는 최적의 플레이를 함.
// 이길 수 있는 플레이어는 최대한 빨리 승리하도록, 질 수 밖에 없는 플레이어는 최대한 오래 버티도록

// 모든 경우 다 찾으면 되는 거 같은데?

// board의 가로, 세로 = [1, 5] -> (0,0) ~ (가로 - 1, 세로 - 1)
// 1 : 발판이 있음.
// aloc, bloc은 초기 위치.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

int ans{}, R, C;
int aWin{}, bWin{};
int aLose{}, bLose{};
constexpr int INF = 100000000;
void dfs(vector<vector<int>>& board, coord aPos, coord bPos, int turn, int count) {
	// base case
	// 1. 갈 수 있는 곳이 없다면..
	// 2. 현재 발판이 없어지거나
	if (turn & 1) { // b turn
		if (!board[bPos.x][bPos.y]) { // a win
			aWin = min(aWin, count);
			bLose = max(bLose, count);
			return;
		}
	}
	else { // a turn
		if (!board[aPos.x][aPos.y]) { // b win
			bWin = min(bWin, count);
			aLose = max(aLose, count);
			return;
		}
	}

	// vector<vector<int>> copyBoard(begin(board), end(board)); // copy

	int canGO{}, samePos{};
	for (int d{}; d < 4; ++d) {
		if (turn & 1) { // b turn
			int nx = bPos.x + "0211"[d] - '1';
			int ny = bPos.y + "1102"[d] - '1';
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue; // out of range
			if (!board[nx][ny]) continue; // 이미 없어진 발판
			if (nx == aPos.x && ny == aPos.y) {
				samePos = 1; // 무조건 게임 끝나기 때문에 바로 이동하지 않음.
				continue;
			}
			board[bPos.x][bPos.y] = 0; // 현재 발판 제거 후 이동
			coord newBPos = { nx, ny };
			++canGO;
			dfs(board, aPos, newBPos, 0, count + 1);
			board[bPos.x][bPos.y] = 1; // 복구
		}
		else { // a turn
			int nx = aPos.x + "0211"[d] - '1';
			int ny = aPos.y + "1102"[d] - '1';
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue; // out of range
			if (!board[nx][ny]) continue; // 이미 없어진 발판
			if (nx == bPos.x && ny == bPos.y) {
				samePos = 1; // 무조건 게임 끝나기 때문에 바로 이동하지 않음.
				continue;
			}
			board[aPos.x][aPos.y] = 0; // 현재 발판 제거 후 이동
			coord newAPos = { nx, ny };
			++canGO;
			dfs(board, newAPos, bPos, 1, count + 1);
			board[aPos.x][aPos.y] = 1; // 복구
		}
	}

	if (canGO == 0 && samePos) { // 같은 좌표 외에는 갈 곳이 없을 때 => 무조건 내가 지는 케이스..
		if (turn & 1) { // bturn
			board[bPos.x][bPos.y] = 0; // 현재 발판 제거 후 이동
			dfs(board, aPos, aPos, 0, count + 1);
			board[bPos.x][bPos.y] = 1; // 복구
		}
		else { // aturn
			board[aPos.x][aPos.y] = 0; // 현재 발판 제거 후 이동
			dfs(board, bPos, bPos, 1, count + 1);
			board[aPos.x][aPos.y] = 1; // 복구
		}
		++canGO;
	}

	if (canGO == 0) { // base case - 갈 수 있는 곳이 없다.
		if (turn & 1) { // bturn -> a win
			aWin = min(aWin, count);
			bLose = max(bLose, count);
		}
		else { // aturn -> b win
			bWin = min(bWin, count);
			aLose = max(aLose, count);
		}
		// ans = min(ans, count);
		return;
	}
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	int answer = -1;
	aWin = bWin = INF;
	aLose = bLose = -1;
	coord aPos = { aloc[0], aloc[1] }, bPos = { bloc[0], bloc[1] };
	R = (int)board.size(), C = (int)board[0].size();

	dfs(board, aPos, bPos, 0, 0); // 0일 때, a가 움직임
	
	int kk{};
	// 승리하는 경우가 하나라도 있는 경우
	// 한 번도 승리하지 못 하는 경우
	
	if (aWin == INF) answer = bWin; // 
	else if (bWin == INF) answer = aWin;
	else answer = min(aWin, bWin);

	return answer;
}

int main() {
	vector<vector<int>> board{ {1,1,1},{1,1,1},{1,1,1} };
	vector<int> aloc{ 1,0 }, bloc{ 1,2 };
	cout << solution(board, aloc, bloc) << '\n';

	vector<vector<int>> board1{ {1,1,1},{1,0,1},{1,1,1} };
	vector<int> aloc1{ 1,0 }, bloc1{ 1,2 };
	cout << solution(board1, aloc1, bloc1) << '\n';

	vector<vector<int>> board2{ {1,1,1,1,1} };
	vector<int> aloc2{ 0,0 }, bloc2{ 0,4 };
	cout << solution(board2, aloc2, bloc2) << '\n';

	vector<vector<int>> board3{ {1} };
	vector<int> aloc3{ 0,0 }, bloc3{ 0,0 };
	cout << solution(board3, aloc3, bloc3) << '\n';

	return 0;
}