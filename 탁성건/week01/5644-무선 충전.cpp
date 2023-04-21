#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

struct BC {
	int y;
	int x;
	int c;
	int p;
};

int dx[] = { 0, 0, 1, 0, -1 };  // X U R D L
int dy[] = { 0, -1, 0, 1, 0 };

int M, A;
vector<int> MAP[10][10];
Node user[2];
int dir[2][101];
BC bc[8];
int ans;

void create_map() {
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			MAP[y][x] = vector<int>();

	for (int k = 0; k < A; k++) {
		BC b = bc[k];
		int cnt = 0;

		queue<Node> q;
		q.push({ b.y, b.x });
		
		int visited[10][10] = { 0, };
		visited[b.y][b.x] = 1;
		MAP[b.y][b.x].push_back(k);

		while (!q.empty() && cnt < b.c) {
			int sz = q.size();
			cnt++;

			for (int s = 0; s < sz; s++) {
				Node now = q.front(); q.pop();
			
				for (int i = 1; i <= 4; i++) {
					int ny = now.y + dy[i];
					int nx = now.x + dx[i];

					if (ny < 0 || ny >= 10 || nx < 0 || nx >= 10) continue;
					if (visited[ny][nx] != 0) continue;

					q.push({ ny, nx });
					visited[ny][nx] = visited[now.y][now.x] + 1;
					MAP[ny][nx].push_back(k);
				}
			}
		}
	}
}

void move_user() {
	ans = 0;
	user[0] = { 0, 0 }, user[1] = { 9, 9 };

	for (int m = 0; m <= M; m++) {
		for (int i = 0; i < 2; i++) {
			user[i].y += dy[dir[i][m]];
			user[i].x += dx[dir[i][m]];
		}

		vector<int>& a = MAP[user[0].y][user[0].x], & b = MAP[user[1].y][user[1].x];
		int capacity = 0;

		if (!a.empty() && !b.empty()) {
			for (int i = 0; i < a.size(); i++) {
				for (int j = 0; j < b.size(); j++) {
					if (a[i] == b[j])
						capacity = max(capacity, bc[a[i]].p);
					else
						capacity = max(capacity, bc[a[i]].p + bc[b[j]].p);
				}
			}
		}
		else if (!a.empty()) {
			for (int i = 0; i < a.size(); i++)
				capacity = max(capacity, bc[a[i]].p);
		}
		else if (!b.empty()) {
			for (int i = 0; i < b.size(); i++)
				capacity = max(capacity, bc[b[i]].p);
		}

		ans += capacity;
	}
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> M >> A;

		for (int i = 0; i < 2; i++)
			for (int j = 1; j <= M; j++)
				cin >> dir[i][j];

		for (int i = 0; i < A; i++) {
			cin >> bc[i].x >> bc[i].y >> bc[i].c >> bc[i].p;
			bc[i].x--, bc[i].y--;
		}

		create_map();

		move_user();

		cout << ans << '\n';
	}
	return 0;
}
