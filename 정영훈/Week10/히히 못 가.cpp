#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

int N{}, index{};
constexpr int INF = static_cast<int>(21e8);

vector<string> strMap; // input
vector<vector<int>> Map; // input -> index
vector<int> spaces; // index별 차지하는 공간 개수


struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

struct Edge {
	int to;
	int weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
	bool operator< (const Edge& other) const { // min heap
		return this->weight > other.weight;
	}
};

// vector<unordered_set<int>> graph; // index -> index
vector<set<int>> graph; // index -> index


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

void MakeGraph(coord start, vector<vector<int>>& visited) {
	queue<coord> q;
	q.push(start);

	visited[start.x][start.y] = 1;
	while (!q.empty()) {
		coord now = q.front(); q.pop();

		// 상하좌우, 대각선
		for (int dir{}; dir < 8; ++dir) {
			int nx = now.x + dx[dir];
			int ny = now.y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			
			if (Map[nx][ny] == -1) continue; // .
			else if(Map[nx][ny] != Map[now.x][now.y]) {
				graph[Map[now.x][now.y]].insert(Map[nx][ny]);
				graph[Map[nx][ny]].insert(Map[now.x][now.y]);
			}
			else {
				if (visited[nx][ny]) continue;
				visited[nx][ny] = 1;
				q.push(coord(nx, ny));
			}
		}
	}
}

int ans{ 10000000 };
int mode{};

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

	set<int> startChk, endChk;

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			if (strMap[i][j] == '.') continue;
			if (Map[i][j] != -1) continue;
			Bfs(coord(i, j));
		}
	}

	graph = vector<set<int>>(index);
	
	priority_queue<Edge> PQ;
	vector<int> dist(index, INF);
	vector<vector<int>> visited(N, vector<int>(N, 0));

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			if (strMap[i][j] == '.') continue;
			if (visited[i][j]) continue;
			MakeGraph(coord(i, j), visited);
		}
		if (i != N - 1) {
			if (startChk.find(Map[N - 1][i]) == startChk.end()) { // 가장 밑 row
				PQ.push(Edge(Map[N - 1][i], spaces[Map[N - 1][i]]));
				startChk.insert(Map[N - 1][i]);
				dist[Map[N - 1][i]] = spaces[Map[N - 1][i]];
			}
			endChk.insert(Map[i][N - 1]);
		}
		if (i != 0) {
			if (startChk.find(Map[i][0]) == startChk.end()) { // 가장 왼쪽 column
				PQ.push(Edge(Map[i][0], spaces[Map[i][0]]));
				startChk.insert(Map[i][0]);
				dist[Map[i][0]] = spaces[Map[i][0]];
			}
			endChk.insert(Map[0][i]);
		}
	}

	// printMap();

	while (!PQ.empty()) {
		Edge now = PQ.top(); PQ.pop();
		if (endChk.find(now.to)!=endChk.end()) {
			cout << dist[now.to] << '\n';
			break;
		}

		if (dist[now.to] != now.weight) continue;

		for (auto& next : graph[now.to]) { // const int &
			if (dist[next] > dist[now.to] + spaces[next]) {
				dist[next] = dist[now.to] + spaces[next];
				PQ.push(Edge(next, dist[next]));
			}
		}
	}

	return 0;
}