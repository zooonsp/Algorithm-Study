#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
	int y;
	int x;
};

const int MAX = 21e8;
int N;
int MAP[10][10];
vector<Node> person;
vector<Node> stair;
int dist[2][10];  // [stair][person]
int ans;
vector<int> s[2];

void go_down() {
	int time = 0, cnt = 0;;
	priority_queue<int, vector<int>, greater<int>> ready[2];
	priority_queue<int, vector<int>, greater<int>> move[2];

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < s[i].size(); j++)
			ready[i].push(dist[i][s[i][j]]);

	while (true) {
		time++;

		for (int i = 0; i < 2; i++) {
			while (true) {
				if (move[i].empty()) break;
				if (move[i].top() > time) break;

				move[i].pop();
				cnt++;
			}
			
			while (true) {
				if (ready[i].empty()) break;
				if (ready[i].top() >= time) break;
				if (move[i].size() >= 3) break;

				move[i].push(time + MAP[stair[i].y][stair[i].x]);
				ready[i].pop();
			}
		}

		if (cnt == person.size())
			break;

		if (time >= ans)
			return;
	}

	ans = min(ans, time);
}

void select_stair(int level) {
	if (level >= person.size()) {
		go_down();
		return;
	}

	for (int i = 0; i < 2; i++) {
		s[i].push_back(level);
		select_stair(level + 1);
		s[i].pop_back();
	}
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N;

		ans = MAX;
		person = vector<Node>();
		stair = vector<Node>();

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> MAP[y][x];
				if (MAP[y][x] == 1)
					person.push_back({ y, x });
				else if (MAP[y][x] != 0)
					stair.push_back({ y, x });
			}
		}

		for (int i = 0; i < stair.size(); i++)
			for (int j = 0; j < person.size(); j++)
				dist[i][j] = abs(stair[i].y - person[j].y) + abs(stair[i].x - person[j].x);

		select_stair(0);

		cout << ans << '\n';
	}

	return 0;
}
