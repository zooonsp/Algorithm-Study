#include <iostream>
#include <queue>
#include <vector>
#define sws ios::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

struct Node {
	int y;
	int x;
	int num;
	int dir;
};

struct Compare {
	bool operator()(Node a, Node b) {
		return a.num < b.num;
	}
};

int dx[] = { 1, 0, -1, 0 };  // R U L D
int dy[] = { 0, -1, 0, 1 };
int input_to_dir[] = { 0, 1, 3, 2, 0 };

int N, M, K;
int MAP[100][100];
queue<Node> q;
priority_queue<Node, vector<Node>, Compare> pq;

void func() {
	while (!q.empty()) {
		Node now = q.front(); q.pop();

		now.y += dy[now.dir];
		now.x += dx[now.dir];

		if (now.y == 0 || now.y == N - 1 || now.x == 0 || now.x == N - 1) {
			now.dir = (now.dir + 2) % 4;
			now.num /= 2;
		}

		if (now.num == 0) continue;

		MAP[now.y][now.x] += now.num;
		pq.push(now);
	}

	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();

		if (MAP[now.y][now.x] == 0) continue;

		now.num = MAP[now.y][now.x];
		MAP[now.y][now.x] = 0;
		
		q.push(now);
	}
}

int main(void) {
	sws;
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N >> M >> K;

		for (int i = 0; i < K; i++) {
			Node node;
			cin >> node.y >> node.x >> node.num >> node.dir;
			node.dir = input_to_dir[node.dir];
			q.push(node);
		}

		for(int i = 0; i < M; i++)
			func();

		int ans = 0;

		while (!q.empty()) {
			Node now = q.front(); q.pop();
			ans += now.num;
		}

		cout << ans << '\n';
	}

	return 0;
}
