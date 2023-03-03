#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 좌표와 limit를 가진 구조체
// PQ에서 작은 limit 우선
struct Node
{
	int y;
	int x;
	int limit;
	bool operator<(Node next) const
	{
		if (limit < next.limit)
			return false;
		if (limit > next.limit)
			return true;
		return false;
	}
};

// 방향 배열(한 칸씩 이동)
int dir[]{1, -1};

const int MAX = 987654321;
int N, M; // N: 세로크기, M: 가로크기
int MAP[52][52];
int minLimit[52][52]; // 해당 좌표까지 가는데 필요한 최소 limit
Node st, de;		  // st: 출발 지점, de: 도착 지점

void calcMinLimit()
{
	priority_queue<Node> pq;
	pq.push({st.y, st.x, 0});
	minLimit[st.y][st.x] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (minLimit[now.y][now.x] < now.limit)
			continue;

		// move
		for (int i = 0; i < 2; i++)
		{
			// 좌우로 이동
			int nx = now.x + dir[i];

			// 맵을 벗어나거나 빈 공간인 경우 skip
			if (MAP[now.y][nx] == -1 || MAP[now.y][nx] == 0)
				continue;
			// 이미 찾은 최소 limit보다 크거나 같으면 skip
			if (minLimit[now.y][nx] <= now.limit)
				continue;

			// move의 경우 필요한 게이지는 0이므로 최소 limit은 그대로
			minLimit[now.y][nx] = now.limit;
			pq.push({now.y, nx, now.limit});
		}

		// jump
		for (int i = 0; i < 2; i++)
		{
			// 위 아래로 점프
			int ny = now.y + dir[i];
			// 현재 jump에서 필요한 limit
			int limit = 1;

			while (true)
			{
				// 빈 공간이 아닌 경우 break
				if (MAP[ny][now.x] != 0)
					break;
				// 빈 공간인 경우 y좌표 및 limit 증가
				ny += dir[i];
				limit++;
			}

			// 맵을 벗어났으면 skip
			if (MAP[ny][now.x] == -1)
				continue;

			// next까지 가는데 필요한 최소 limit
			// => now까지 오는데 필요한 최소 limit과 현재 jump에서 필요한 limit 중 큰 값
			limit = max(minLimit[now.y][now.x], limit);

			// 이미 찾은 최소 limit보다 크거나 같으면 skip
			if (minLimit[ny][now.x] <= limit)
				continue;

			minLimit[ny][now.x] = limit;
			pq.push({ny, now.x, limit});
		}
	}
}

int main(void)
{
	cin >> N >> M;

	// 울타리 치기 => 맵 벗어나는 경우 -1
	for (int i = 0; i <= N + 1; i++)
		MAP[i][0] = MAP[i][M + 1] = -1;

	// 울타리 치기
	for (int i = 0; i <= M + 1; i++)
		MAP[0][i] = MAP[N + 1][i] = -1;

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= M; x++)
		{
			cin >> MAP[y][x];
			minLimit[y][x] = MAX; // minLimit을 MAX값으로 초기화
			if (MAP[y][x] == 2)
				st = {y, x}; // 출발 지점
			else if (MAP[y][x] == 3)
				de = {y, x}; // 도착 지점
		}
	}

	calcMinLimit();

	// 도착 지점까지 가는데 필요한 최소 limit 출력
	cout << minLimit[de.y][de.x] << '\n';

	return 0;
}
