#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<cstring>

using namespace std;

const int MAT_MAX = 1515;
const int ry[] = { 1, -1, 0, 0 };
const int rx[] = { 0, 0, 1, -1 };

struct coordi {
	int y, x;

	coordi operator +=(coordi next)
	{
		coordi temp;
		temp.y = y + next.y;
		temp.x = x + next.x;

		return temp;
	}

	bool operator ==(coordi next) const
	{
		if (next.y == y && next.x == x)
			return true;
		return false;
	}
};



int R, C;
vector<coordi> swan;
int MAT[MAT_MAX][MAT_MAX];
vector<coordi> melt;

int input()
{
	cin >> R >> C;

	string temp;
	for (int i = 0; i < R; i++)
	{
		cin >> temp;
		for (int j = 0; j < C; j++)
		{
			if (temp[j] == 'X')
				MAT[i][j] = 1;
			else if (temp[j] == 'L')
			{
				MAT[i][j] = 2;
				swan.push_back({ i, j });
			}
		}
	}

	return 0;
}

int visited[MAT_MAX][MAT_MAX];

queue<coordi> nq; // 다음큐

int bfs() // 백조가 만나는지?
{
	queue<coordi>q;
	q.swap(nq);


	while (!q.empty())
	{
		coordi now = q.front();
		q.pop();

		if (now == swan[1])
			return 1;

		int next_flag = 0;

		for (int i = 0; i < 4; i++)
		{
			coordi next = now;
			next.y += ry[i];
			next.x += rx[i];

			if (next.y < 0 || next.y >= R ||
				next.x < 0 || next.x >= C) continue;

			if (visited[next.y][next.x]) continue;

			if (MAT[next.y][next.x] == 1)
			{
				if (!next_flag)
				{
					next_flag = 1;
					nq.push(now);
				}
				continue;
			}

			visited[next.y][next.x] = 1;

			q.push(next);
		}
	}
	return 0;
}

int ans = 0;

int solve_func()
{
	// 백조가 바로 만날 수 있다면 return
	nq.push(swan[0]);
	visited[swan[0].y][swan[0].x] = 1;
	if (bfs())
	{
		return 0;
	}



	// 1. pq에 물에 맞닿은 얼음 다 추가
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (MAT[i][j] != 1) continue;

			for (int k = 0; k < 4; k++)
			{
				coordi temp;
				temp.y = i + ry[k];
				temp.x = j + rx[k];

				if (temp.y < 0 || temp.y >= R ||
					temp.x < 0 || temp.x >= C) continue;

				if (MAT[temp.y][temp.x] != 1)
				{
					melt.push_back({ i, j });
					break;
				}
			}
		}
	}
	ans++;

	while (!melt.empty())
	{
		for (auto v : melt)
		{
			MAT[v.y][v.x] = 0;
		}

		if (bfs())
		{
			return 0;
		}



		vector<coordi> next_ice; // 다음에 녹을 얼음들

		while (!melt.empty())
		{
			coordi now = melt.back();
			melt.pop_back();


			for (int i = 0; i < 4; i++)
			{
				coordi next = now;
				next.y += ry[i];
				next.x += rx[i];

				if (next.y < 0 || next.y >= R ||
					next.x < 0 || next.x >= C) continue;

				if (MAT[next.y][next.x] != 1) continue;


				next_ice.push_back(next);
				MAT[next.y][next.x] = 0;

			}
		}

		melt.swap(next_ice);

		ans++;

	}


	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);


	input();
	solve_func();

	cout << ans;
	return 0;
}