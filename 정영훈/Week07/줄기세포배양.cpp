// 일정 시간 동안 배양을 시킨 후 줄기 세포의 개수가 몇 개인지
// 생명력 수치가 X인 경우 X시간 동안 비활성 상태이고 X시간이 지난 후 활성.
// 활성 상태가 되면 X시간 동안 살아남을 수 있음.
// 세포가 죽더라도 소멸되는 것이 아닌 죽은 상태로 해당 그리드 셀을 차지함.

// 활성화된 줄기 세포는 첫 1시간 동안 상하좌우 네 방향으로 동시에 번식
// 번식된 줄기 세포는 비활성 상태임
// 하나의 그리드 셀에는 하나의 줄기 세포만 존재 가능, 번식하는 방향에 
// 이미 줄기 세포가 존재하는 경우 해당 방향으로 번식하지 않음.
// 두 개 이상의 줄기 세포가 하나의 그리드 셀에 동시 번식하려 하는 경우
// 생명력 수치가 높은 줄기 세포가 혼자 차지함. (1 <= x <= 10)

// N, M : 1 ~ 50
/*
5
2 2 10
1 1
0 2
*/

constexpr int SIZE = 1000;
constexpr int OFFSET = 500; 
// (x,y) 인 경우 -> (OFFSET + x, OFFSET + y)로 저장되도록 하는 값.
int Map[SIZE][SIZE]{};
int N, M; // 세로 가로
int K; // 배양 시간
int ans; // 답

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct cell {
	int x, y; // pos
	int lifes; // 생명력
	int realtime; // 실제 시간
	cell(int x, int y, int lifes, int realtime) : x(x), y(y), lifes(lifes), realtime(realtime) {}

	// heap
	// 1. 시간이 더 짧은 친구가 먼저
	// 2. 시간이 같다면 생명력이 더 높은 친구가 먼저
	bool operator< (const cell& other) const {
		if (this->realtime == other.realtime) return this->lifes < other.lifes; // 생멱력 수치가 높은
		return this->realtime > other.realtime; // 시간이 더 짧은
	}
};

void init() {
	ans = 0;
	memset(Map, 0, sizeof(Map));
}

void input(priority_queue<cell>& pq) {
	cin >> N >> M >> K;
	for (int n{}; n < N; ++n) {
		for (int m{}; m < M; ++m) {
			cin >> Map[n + OFFSET][m + OFFSET];
			if (Map[n + OFFSET][m + OFFSET]) {
				++ans;
				pq.push(cell(n, m, Map[n + OFFSET][m + OFFSET], Map[n + OFFSET][m + OFFSET])); // 줄기 세포 정보 저장
			}
		}
	}
}

int dx[]{ -1,1,0,0 };
int dy[]{ 0,0,-1,1 };

int main() {
	int T, time{};
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int t{ 1 }; t <= T; ++t) {
		init();
		time = 0;
		priority_queue<cell> notActive; // 비활성
		priority_queue<cell> active; // 활성 

		queue<cell> tmpnotActive;
		input(notActive);

		while (1) {
			// 활성 -> 사망
			while (!active.empty() && active.top().realtime <= time) {
				active.pop();
			}
			//cout << time << ' ' << (int)notActive.size() + (int)active.size() << '\n';
			
			// 비활성 -> 활성
			// 증식(time + 1 + now.lifes); 
			while (!notActive.empty() && notActive.top().realtime <= time) {
				// notActive -> active;
				auto now = notActive.top();
				notActive.pop();
				for (int i = 0; i < 4; ++i) {
					int nx = now.x + dx[i];
					int ny = now.y + dy[i];
					if (Map[nx + OFFSET][ny + OFFSET]) {
						continue; // 이미 다른 놈이..
					}
					Map[nx + OFFSET][ny + OFFSET] = time + 2;
					// notActive.push(cell(nx, ny, now.lifes, time + 2));
					tmpnotActive.push(cell(nx, ny, now.lifes, time + 1 + now.lifes)); // 1개 더해야 함..
					// 답을 구할 때 notActive의 개수와 active의 개수를 더하기 때문에
					// 따로 tmp에 담아서 마지막에 추가했음.
				}
				active.push(cell(now.x, now.y, now.lifes, time + now.lifes)); // 얘는 한 번만
			}
			
			if (time == K) break;
			++time;

			// 진짜 추가
			while (!tmpnotActive.empty()) {
				notActive.push(tmpnotActive.front());
				tmpnotActive.pop();
			}
		}
		
		ans = (int)notActive.size() + (int)active.size();
		cout << "#" << t << ' ' << ans << '\n';
	}

	return 0;
}