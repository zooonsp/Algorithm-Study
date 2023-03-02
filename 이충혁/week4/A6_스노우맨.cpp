#include<iostream>
#include<queue>
using namespace std;
const int MAT_MAX = 55;
// 0, 1 (상, 하 : 수직이동 ), 2, 3 (좌, 우 : 수평이동)
const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct point
{
	int y, x;
};

struct Info // bfs에서 좌표와 수직 이동 카운트 
{
	point pt;
	int cnt;
};

// binary search 와 bfs
// 0 ~ 세로크기 로 이진탐색 하며 최솟 값을 찾는다
// 탐색중인 mid 값으로 bfs 돌려서 보석에 도달하는지 체크

int N, M; // N: 세로크기, M: 가로크기
int MAT[MAT_MAX][MAT_MAX]; // 맵 정보
point st, ed; // st: 눈사람 위치, ed: 보석 위치

int input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> MAT[i][j];
			if (MAT[i][j] == 2)
				st = { i, j };
			else if (MAT[i][j] == 3)
				ed = { i, j };
		}
	}
	return 0;
}

int bfs(int limit) // lilmit : mid 값
{
	int visited[MAT_MAX][MAT_MAX] = { 0, };
	queue<Info> q;
	q.push({ st, 0 });
	visited[st.y][st.x] = 1;

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.pt.y == ed.y && now.pt.x == ed.x)
		{
			return 1;
		}

		// 수직 이동
		for (int i = 0; i < 2; i++)
		{
			if (limit == 0) break; // limit이 0이면 수직이동 못함

			Info next;
			next.pt.y = now.pt.y + ry[i];
			next.pt.x = now.pt.x + rx[i];

			if (next.pt.y < 0 || next.pt.y >= N ||
				next.pt.x < 0 || next.pt.x >= M) continue;

			if (visited[next.pt.y][next.pt.x] == 1) continue; 

			if (MAT[next.pt.y][next.pt.x] == 0)
			{
				next.cnt = now.cnt + 1;
				if (next.cnt >= limit) continue; // 수직이동 카운트가 한계보다 같거나 크면 q에 넣지 않는다.
			}
			else
			{
				next.cnt = 0; // 1은 땅이기 때문에 cnt 다시 0으로
			}
			visited[next.pt.y][next.pt.x] = 1;
			q.push(next);
		}
		// 수평이동
		for (int i = 2; i < 4; i++)
		{
			if (now.cnt > 0) continue; // 수직 이동중이면 수평이동 안하기
			Info next;
			next.pt.y = now.pt.y + ry[i];
			next.pt.x = now.pt.x + rx[i];

			if (next.pt.y < 0 || next.pt.y >= N ||
				next.pt.x < 0 || next.pt.x >= M) continue;

			if (visited[next.pt.y][next.pt.x] == 1) continue;

			if (MAT[next.pt.y][next.pt.x] == 0) continue;

			next.cnt = 0;
			visited[next.pt.y][next.pt.x] = 1;
			q.push(next);
		}
	}

	return 0;
}

int solve_func()
{
	// binary_search

	int left = 0;
	int right = N - 1;
	int ans = right;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (bfs(mid))
		{
			ans = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return ans;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	input();
	cout << solve_func();
	return 0;
}