#include<iostream>
#include<vector>
using namespace std;
const int MAX = 50;

// 벌집 8방향 다 돌릴 예정
const int ry[] = { -1, 1, 0, 0, -1, -1, 1, 1 }; 
const int rx[] = { 0, 0, -1, 1, 1, -1, 1, -1 };

// 예외 부분 : Y자 4가지가 전부 안됨 - 리팩토링 해보자 ㅠ 
const int ex[4][3][3] = { { 0, 1, 0, 0, 1, 0, 1, 0, 1, }, { 1, 0, 1, 0, 1, 0, 0, 1, 0 },
{ 0, 1, 0, 1, 1, 1, }, { 1, 1, 1, 0, 1, 0, } };

struct point {
	int y, x;
};

int n, m;
int MAP[MAX][MAX] = { 0, };


int input()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> MAP[i][j];
		}
	}
	return 0;
}

// dfs 해서 이어진 벌집 경로 저장할 변수
vector<point> path;
int visited[MAX][MAX] = { 0, };

int ans = 0;

int dfs(int level)
{
	// 기저조건 : 첫 부분 저장해서 이어진 부분 3개 까지 도달했을때
	if (level == 3)
	{
		int sum = 0;
		// 해당 path 좌표 값의 벌통 값을 더함
		for (int i = 0; i < 4; i++)
		{
			sum += MAP[path[i].y][path[i].x];
		}

		if (sum > ans)
			ans = sum;

		return 0;
	}

	// 재귀는 8방향 으로 전부
	for (int i = 0; i < 8; i++)
	{
		// 대신 짝수 일경우 윗대각, 홀수 일경우 아랫 대각 안돌림
		if (path[level].x % 2 == 0 &&
			(i == 6 || i == 7))
			continue;
		else if (path[level].x % 2 == 1 &&
			(i == 4 || i == 5))
			continue;


		point next;
		next.y = path[level].y + ry[i];
		next.x = path[level].x + rx[i];
		if (next.y < 0 || next.y >= n ||
			next.x < 0 || next.x >= m)
			continue;
		if (visited[next.y][next.x])
			continue;

		visited[next.y][next.x] = 1;
		path.push_back(next);

		dfs(level + 1);

		visited[next.y][next.x] = 0;
		path.pop_back();

	}
	return 0;
}


// Y자 4가지 모양일때 벌통 값
int ex_func(point now)
{
	for (int i = 0; i < 4; i++)
	{
		int sum = 0;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				point next;
				next.y = now.y + j;
				next.x = now.x + k;

				sum += MAP[next.y][next.x] * ex[i][j][k];
			}
		}

		if (sum > ans)
			ans = sum;
	}

	return 0;
}

int solve_func()
{
	// 모든 x, y 좌표 탐색
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			// x,y 하나당 dfs 한번 씩 다 해줌
			// 시작점 경로와 visited에 저장, 새로 들어올 때 마다 path 초기화
			path.clear();
			path.push_back({ i, j });
			visited[i][j] = 1;
			dfs(0);
			visited[i][j] = 0;

			// 예외인 구조 처리
			ex_func({ i, j });

		}
	}
	return 0;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	input();
	solve_func();
	cout << ans;
	return 0;
}