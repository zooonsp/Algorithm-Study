#include<iostream>
#include<queue>
using namespace std;
const int MAX = 110;

struct BC_info{
	int x, y, C, P; // 좌표, 충전범위(C), 처리량(P)
};

struct point{
	int y, x;
};

enum{
	S, U, R, D, L
};

const int ry[] = { 0, -1, 0, 1, 0 };
const int rx[] = { 0, 0, 1, 0, -1 };

int M, BC_cnt;
int user[2][MAX];
BC_info BC[10];

int MAP[10][12][12];

int init()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			for (int k = 0; k < 10; k++)
				MAP[k][i][j] = 0;
		}
	}


	return 0;
}
int input()
{
	cin >> M >> BC_cnt;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> user[i][j];
		}
	}

	for (int i = 0; i < BC_cnt; i++)
	{
		BC_info temp;
		cin >> temp.x >> temp.y >> temp.C >> temp.P;
		BC[i] = temp;
	}
	return 0;
}

int bfs_makemap(BC_info start, int BC_num)
{
	queue<BC_info> q;
	q.push(start);
	MAP[BC_num][start.y][start.x] = start.P;

	while (!q.empty())
	{
		BC_info now = q.front();
		q.pop();

		if (now.C < 0) continue;
		MAP[BC_num][now.y][now.x] = now.P;

		for (int i = 1; i <= 4; i++)
		{
			BC_info next;
			next.y = now.y + ry[i];
			next.x = now.x + rx[i];

			if (next.y < 1 || next.y > 10 ||
				next.x < 1 || next.x > 10)
				continue;
			if (MAP[BC_num][next.y][next.x] != 0)
				continue;


			next.C = now.C - 1;
			next.P = now.P;
			q.push(next);
		}

	}

	return 0;
}

int max_charge(point user0, point user1)
{
	int BC_visited[10];
	int max = 0;


	for (int i = 0; i < BC_cnt; i++)
	{
		for (int j = 0; j < BC_cnt; j++)
		{
			if (MAP[i][user0.y][user0.x] == 0 && MAP[j][user1.y][user1.x] == 0) continue;

			if (i == j)
			{
				if (max < BC[i].P)
					max = BC[i].P;
			}
			else
			{
				int temp = MAP[i][user0.y][user0.x] + MAP[j][user1.y][user1.x];
				if (max < temp)
					max = temp;
			}
		}
	}
	return max;
}

int solve_data()
{
	int sum = 0;
	point user0 = { 1, 1 }, user1 = { 10, 10 };
	for (int i = 0; i < BC_cnt; i++)
	{
		bfs_makemap(BC[i], i);
	}

	// 0 시간 대에 충전
	sum += max_charge(user0, user1);

	for (int i = 0; i < M; i++)
	{
		user0.y += ry[user[0][i]];
		user0.x += rx[user[0][i]];
		user1.y += ry[user[1][i]];
		user1.x += rx[user[1][i]];

		sum += max_charge(user0, user1);


	}

	return sum;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		cout << "#" << test_case << " " << solve_data() << "\n";
	}
	return 0;
}