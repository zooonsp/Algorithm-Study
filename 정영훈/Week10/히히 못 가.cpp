#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N{}, index{};

vector<string> strMap; // input
vector<vector<int>> Map; // input -> index
vector<int> spaces; // index별 차지하는 공간 개수


struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

vector<vector<int>> graph; // index -> index graph
vector<int> lastColumnIndexes;
vector<int> firstColumnIndexes;
vector<int> lastRowIndexes;
vector<int> firstRowIndexes;


// 상하좌우 대각선
int dx[]{ -1,1,0,0,-1,-1,1,1 };
int dy[]{ 0,0,-1,1,-1,1,1,-1 };

void Bfs(coord start) {
	queue<coord> q;
	q.push(start);
	int count{ 1 }; // 영역 개수
	Map[start.x][start.y] = index;
	char startChar = strMap[start.x][start.y];
	while (!q.empty()) {
		coord now = q.front(); q.pop();

		// 상하좌우
		for (int dir{}; dir < 4; ++dir) {
			int nx = now.x + dx[dir];
			int ny = now.y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (Map[nx][ny] == -1 && strMap[nx][ny] == startChar) {
				q.push(coord(nx, ny));
				Map[nx][ny] = index;
				++count;
			}
		}
	}
	spaces.push_back(count);
	++index;
}

void MakeGraph(coord start) {
	queue<coord> q;
	q.push(start);
	int startIndex = Map[start.x][start.y];
	vector<int> numChk(index, 0);
	vector<vector<int>> visited(N, vector<int>(N, 0));
	visited[start.x][start.y] = 1;
	while (!q.empty()) {
		coord now = q.front(); q.pop();

		// 상하좌우, 대각선
		for (int dir{}; dir < 8; ++dir) {
			int nx = now.x + dx[dir];
			int ny = now.y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = 1;
			if (Map[nx][ny] == startIndex) {
				q.push(coord(nx, ny));
			}
			else if (Map[nx][ny] == -1) continue; // .
			else {
				if (numChk[Map[nx][ny]]) continue;
				numChk[Map[nx][ny]] = 1;
				graph[startIndex].push_back(Map[nx][ny]);
			}
		}
	}
}

int ans{ 10000000 };
int mode{};
vector<int> chk;
void DFS(int index, int sum) {
	// base case
	if (mode) { // column
		if (firstRowIndexes[index]) {
			ans = min(ans, sum);
			return;
		}
		if (lastColumnIndexes[index]) {
			ans = min(ans, sum);
			return;
		}
	}
	else {
		if (firstRowIndexes[index]) {
			ans = min(ans, sum);
			return;
		}
		if (lastColumnIndexes[index]) {
			ans = min(ans, sum);
			return;
		}
	}
	// pruning
	if (sum >= ans) return;

	for (int& next : graph[index]) {
		if (chk[next]) continue;
		chk[next] = 1;
		DFS(next, sum + spaces[next]);
		chk[next] = 0;
	}
	return;
}

void printMap() {
	for (auto& row : Map) {
		for (int& v : row) {
			cout << v << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N;	
	strMap.assign(N, "");
	Map.assign(N, vector<int>(N, -1));
	for (int n{}; n < N; ++n) {
		cin >> strMap[n];
	}
	
	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			if (strMap[i][j] == '.') continue;
			if (Map[i][j] != -1) continue;
			Bfs(coord(i,j));
		}
	}
	vector<int> startChk(index, 0);
	graph = vector<vector<int>>(index);
	lastColumnIndexes.assign(index, 0);
	//lastRowIndexes.assign(index, 0);
	//firstColumnIndexes.assign(index, 0);
	firstRowIndexes.assign(index, 0);
	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			if (strMap[i][j] == '.') continue;
			if (startChk[Map[i][j]]) continue;
			startChk[Map[i][j]] = 1;
			MakeGraph(coord(i, j));
		}
		if (i != N - 1) {
			lastColumnIndexes[Map[i][N - 1]] = 1;
			//lastRowIndexes[Map[N-1][i]] = 1;
		}
		if (i != 0) {
			//firstColumnIndexes[Map[i][0]] = 1;
			firstRowIndexes[Map[0][i]] = 1;
		}
	}

	// printMap();
	
	startChk.assign(index, 0);
	chk.assign(index, 0);
	for (int row{ 1 }; row < N; ++row) {
		if (startChk[Map[row][0]] == 0) {
			startChk[Map[row][0]] = 1;
			chk[Map[row][0]] = 1;
			DFS(Map[row][0], spaces[Map[row][0]]);
			chk[Map[row][0]] = 0;
		}
	}

	mode = 1;
	startChk.assign(index, 0);
	for (int col{ 0 }; col < N - 1; ++col) {
		if (startChk[Map[N-1][col]] == 0) {
			startChk[Map[N-1][col]] = 1;
			chk[Map[N-1][col]] = 1;
			DFS(Map[N-1][col], spaces[Map[N-1][col]]);
			chk[Map[N - 1][col]] = 0;
		}
	}

	cout << ans << '\n';

	return 0;
}