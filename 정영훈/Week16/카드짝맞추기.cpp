/*
카드 16장이 뒷면을 위로하여 4 x 4 크기의 격자 형태로 표시되어 있습니다.
각 카드의 앞면에는 카카오프렌즈 캐릭터 그림이 그려져 있으며,
8가지의 캐릭터 그림이 그려진 카드가 각기 2장씩 화면에 무작위로 배치되어 있습니다.
유저가 카드를 2장 선택하여 앞면으로 뒤집었을 때 같은 그림이 그려진 카드면
해당 카드는 게임 화면에서 사라지며, 같은 그림이 아니라면 원래 상태로 뒷면이 보이도록 뒤집힙니다.
이와 같은 방법으로 모든 카드를 화면에서 사라지게 하면 게임이 종료됩니다.

커서는 [Ctrl] 키와 방향키에 의해 이동되며 키 조작법은 다음과 같습니다.
- 방향키를 통해 1칸 이동
- [Ctrl] 키 + 방향키로 이동. (누른 키 방향에 있는 가장 가까운 카드로 한 번에 이동)
	- 카드가 없다면 가장 마지막 칸으로 이동.
	- 만약 이동 가능한 카드 또는 빈 공간이 없어 이동할 수 없다면 움직이지 않음.
- 카드를 뒤집기 위해서는 [Enter] 키를 입력

게임 진행 중 카드의 짝을 맞춰 몇 장 제거된 상태에서 카드 앞면의 그림을 알고 있다면,
남은 카드를 모두 제거하는데 필요한 키 조작 횟수의 최솟값을 구해 보려고 합니다.
방향키 = 1회
[Enter] 키 = 1회
[Ctrl] 키 + 방향키 = 1회

board = 4 x 4
각 원소는 0 이상 6이하인 자연수
0은 카드가 제거된 빈 칸을
1 ~ 6까지의 자연수는 2개씩 들어 있으며 같은 숫자는 같은 그림의 카드를 의미함.
*/
#include <bits/stdc++.h>

using namespace std;

constexpr int SIZE = 4;
constexpr int INF = 1 << 30;
constexpr int dr[]{ -1,1,0,0 };
constexpr int dc[]{ 0,0,-1,1 };

struct coord {
	int r, c;
	coord(int r, int c) : r(r), c(c) {}
};
vector<vector<coord>> cards(7); // 1 ~ 6
// cards[i][0] : card번호가 i번인 첫 번째 카드의 위치(coord)
// cards[i][1] : card번호가 i번인 두 번째 카드의 위치(coord)

int minimumCnt{ INF };
int maxCard{ -1 };
int row, col;
vector<int> cardVisit;
vector<int> cardOrder;
vector<vector<int>> originBoard, copyBoard;

int GetDistance(vector<vector<int>>& board, coord start, coord target) {
	vector<vector<int>> visited(SIZE, vector<int>(SIZE, INF));
	queue<coord> q;
	q.push(start);
	visited[start.r][start.c] = 1;
	while (!q.empty()) {
		coord now = q.front(); q.pop();
		if (now.r == target.r && now.c == target.c) {
			break;
		}
		for (int dir{}; dir < SIZE; ++dir) { // 방향키 이동
			int nr = now.r + dr[dir], nc = now.c + dc[dir];
			if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) continue;
			if (visited[nr][nc] > visited[now.r][now.c] + 1) {
				q.emplace(nr, nc);
				visited[nr][nc] = visited[now.r][now.c] + 1;
			}
		}

		for (int dir{}; dir < SIZE; ++dir) { // [Ctrl] 키 + 방향키
			for (int dist{ 1 }; dist < 4; ++dist) {
				int nr = now.r + dr[dir] * dist, nc = now.c + dc[dir] * dist;
				if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) break; // 처음부터 벗어남.
				if (board[nr][nc]) { // 발견된 카드가 있거나
					if (visited[nr][nc] > visited[now.r][now.c] + 1) {
						q.emplace(nr, nc);
						visited[nr][nc] = visited[now.r][now.c] + 1;
					}
					break;
				}
				if ((dir == 0 && nr == 0) || (dir == 1 && nr == SIZE - 1) ||
					(dir == 2 && nc == 0) || (dir == 3 && nc == SIZE - 1)) { // 끝이거나
					if (visited[nr][nc] > visited[now.r][now.c] + 1) {
						q.emplace(nr, nc);
						visited[nr][nc] = visited[now.r][now.c] + 1;
					}
					break;
				}
			}
		}
	}
	return visited[target.r][target.c] - 1; // -1 해야 방문횟수 제대로 반환
}

void Simulate(coord now, int orderIndex, int sum) {
	if (orderIndex == maxCard) {
		minimumCnt = min(minimumCnt, sum);
		return;
	}
	for (int t{}; t < 2; ++t) {
		int order = cardOrder[orderIndex], cnt{};

		coord& first = cards[order][t];
		coord& second = cards[order][(t + 1) % 2];

		// now -> first
		cnt += GetDistance(copyBoard, now, first);
		copyBoard[first.r][first.c] = 0;
		// first -> second
		cnt += GetDistance(copyBoard, first, second);
		copyBoard[second.r][second.c] = 0;
		Simulate(second, orderIndex + 1, sum + cnt);

		copyBoard[cards[order][0].r][cards[order][0].c] = order;
		copyBoard[cards[order][1].r][cards[order][1].c] = order;
	}
}

void MakeOrder(int index) {
	if (index == maxCard) {
		coord start{ row,col };
		copyBoard = { begin(originBoard), end(originBoard) };
		Simulate(start, 0, 0);
		return;
	}

	for (int c{ 1 }; c <= maxCard; ++c) {
		if (cardVisit[c]) continue;
		cardVisit[c] = 1;
		cardOrder.push_back(c);
		MakeOrder(index + 1);
		cardVisit[c] = 0;
		cardOrder.pop_back();
	}
}

int solution(vector<vector<int>> board, int r, int c) {
	int answer{};
	for (int n{}; n < SIZE; ++n) {
		for (int m{}; m < SIZE; ++m) {
			if (board[n][m]) {
				cards[board[n][m]].emplace_back(n, m);
				maxCard = max(maxCard, board[n][m]);
			}
		}
	}
	cardVisit.assign(maxCard + 1, 0);
	originBoard = { begin(board), end(board) };
	row = r, col = c;

	MakeOrder(0);

	answer = minimumCnt;
	answer += (maxCard << 1);
	return answer;
}

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	vector<vector<int>> board{ {1,0,0,3}, {2,0,0,0},{0,0,0,2},{3,0,1,0} };
	int r = 1, c = 0;
	cout << solution(board, r, c) << '\n';

	vector<vector<int>> board1{ {3,0,0,2}, {0,0,1,0},{0,1,0,0},{2,0,0,3} };
	int r1 = 0, c1 = 1;
	cout << solution(board1, r1, c1) << '\n';

	return 0;
}