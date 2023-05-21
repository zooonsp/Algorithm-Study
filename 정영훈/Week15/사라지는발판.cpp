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

// https://blog.encrypted.gg/1032

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct coord {
	int x, y; 
	coord(int x, int y) : x(x), y(y) {}
};

int R, C;

// 최적의 플레이 횟수 반환
// 짝수인 경우 현재 플레이어의 패배
// 홀수인 경우 현재 플레이어의 승리
int dfs(vector<vector<int>>& board, coord now, coord op) {

	if (board[now.x][now.y] == 0) return 0; // 발판 사라짐
	int ret{};

	for (int d{}; d < 4; ++d) {
		int nx = now.x + "0211"[d] - '1';
		int ny = now.y + "1102"[d] - '1';

		if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue; // out of bound
		if (board[nx][ny] == 0) continue; // 없는 발판

		coord newC(nx, ny);
		board[now.x][now.y] = 0; // 삭제
		int val = dfs(board, op, newC) + 1; // + 1 (현재)
		board[now.x][now.y] = 1; // 복구

		if (!(ret & 1) && (val & 1)) ret = val; // 패배인 줄 알았지만 승리가 가능한 경우를 알게 됨. (패배 -> 승리)
		else if (!(ret & 1) && !(val & 1)) ret = max(ret, val); // 최대한 많은 턴을 소비해야 함. (패배 -> 패배)
		else if ((ret & 1) && (val & 1)) ret = min(ret, val); // 최대한 빨리 이기도록 (승리 -> 승리)
	}
	return ret;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
	int answer = -1;
	
	coord aPos = { aloc[0], aloc[1] }, bPos = { bloc[0], bloc[1] };
	R = (int)board.size(), C = (int)board[0].size();
	answer = dfs(board, aPos, bPos); // 0일 때, a가 움직임

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