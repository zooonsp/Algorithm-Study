// 가장자리 = 약물
// 이동방향 = 상하좌우(1,2,3,4) -> (0,1,2,3) 바꿈
// 각 군집들은 1시간마다 이동방향에 있는 다음 셀로 이동
// 약품이 칠해진 셀에 도착하면 절반이 죽고, 이동방향 반전
// 미생물 수가 홀수이던 짝수이던 2로 나눈 몫
// 군집이 한 셀에 모이는 경우 군집 합치기 -> 이동 방향은 많은 쪽으로 결정
// M시간 후 남은 미생물 수 구하기

// 매 시간 경과 관찰 필요 - flood fill

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>

// 상하좌우(0,1,2,3)
int dx[]{ -1,1,0,0 };
int dy[]{ 0,0,-1,1 };

using namespace std;
int N, M, K;
int total{};

struct Info {
	int num; // 군집 중 최대 마리 수
	int dir; // 최대 마리인 군집이 가지는 방향
	int total_num; // 해당 좌표에 도착하는 총 세균 수
	Info(int n, int d, int tot) : num(n), dir(d), total_num(tot) {}
};

struct qq {
	int x, y; // 위치
	int num; // 마릿수
	int dir; // 방향
	qq(int x, int y, int n,int d) : x(x), y(y), num(n), dir(d) {}
};

int main() {
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);

	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> N >> M >> K; // 셀 개수, 격리 시간, 군집 수
		vector<vector<Info>> Map(N, vector<Info>(N, Info(0, 0, 0))); // 각 좌표별 마리수, 방향 저장
		total = 0;

		queue<qq> q;
		for (int k = 0; k < K; ++k) {
			int x, y, num, dir;
			cin >> x >> y >> num >> dir;
			total += num;
			dir--;
			q.push(qq(x, y, num, dir));
		}
		
		for (int m = 0; m < M; ++m) {
			vector<pair<int, int>> coords; // 다음에 위치들.
			int cursize = q.size();
			for (int ss = 0; ss < cursize; ++ss) {
				while (!q.empty()) {
					auto now = q.front();
					q.pop();

					// 약물에서 왔다리갔다리는 없겠지?..
					int nx = now.x + dx[now.dir];
					int ny = now.y + dy[now.dir];

					if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
						int a{};
					}

					coords.push_back(make_pair(nx, ny));

					if (nx == 0) {
						int num = now.num / 2; // 새 마리수
						total -= (now.num - num);
						if (Map[nx][ny].num < now.num) { // 최대 마리수 갱신
							Map[nx][ny].num = num;
						}
						Map[nx][ny].dir = now.dir + 1; // 상 -> 하 (무조건 해야되네)
						Map[nx][ny].total_num += num;
					}
					else if (ny == 0) {
						int num = now.num / 2;
						total -= (now.num - num);
						if (Map[nx][ny].num < now.num) {
							Map[nx][ny].num = num;
						}
						Map[nx][ny].dir = now.dir + 1; // 좌 -> 우
						Map[nx][ny].total_num += num;
					}
					else if (nx == N - 1) {
						int num = now.num / 2;
						total -= (now.num - num);
						if (Map[nx][ny].num < now.num) {
							Map[nx][ny].num = num;
						}
						Map[nx][ny].dir = now.dir - 1; // 하 -> 상
						Map[nx][ny].total_num += num;
					}
					else if (ny == N - 1) {
						int num = now.num / 2;
						total -= (now.num - num);
						if (Map[nx][ny].num < now.num) {
							Map[nx][ny].num = num;
						}
						Map[nx][ny].dir = now.dir - 1; // 우 -> 좌
						Map[nx][ny].total_num += num;
					}
					else {
						if (Map[nx][ny].num < now.num) {
							Map[nx][ny].num = now.num;
							Map[nx][ny].dir = now.dir;
						}
						Map[nx][ny].total_num += now.num;
					}
				}
			}

			// 다시 q에 push
			for (auto& coord : coords) {
				// qq : x, y, num, dir
				int x = coord.first, y = coord.second;
				if (Map[x][y].total_num == 0) continue; // 다 죽음..
				q.push(qq(x, y, Map[x][y].total_num, Map[x][y].dir));
				Map[x][y].dir = Map[x][y].num = Map[x][y].total_num = 0;
			}
		}

		cout << "#" << test_case << ' ' << total << '\n';

	}
	return 0;
}

