#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

const int MAT_MAX = 25;

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct coordi {
	int y, x;

	bool operator != (coordi next) const
	{
		if (y != next.y || x != next.x)
			return true;

		return false;
	}

	bool operator == (coordi next) const
	{
		if (y == next.y && x == next.x)
			return true;

		return false;
	}
};

struct Info
{
	coordi pt;
	int cnt;
};

int N, M; // N : ¸ÊÅ©±â, M : ½Â°´ ¼ö
int MAT[MAT_MAX][MAT_MAX]; // ¸Ê Á¤º¸
coordi taxi; //  ÅÃ½Ã ÁËÇ¥ 
int fuel; // ÅÃ½Ã ¿¬·á
vector<coordi> pas_st, pas_ed; // ½Â°´ Á¤º¸ ( Ãâ¹ßÁö, µµÂøÁö )

void init()
{
	for (int i = 0; i < MAT_MAX; i++)
		for (int j = 0; j < MAT_MAX; j++)
			MAT[i][j] = 1;
	return;
}

int input()
{
	cin >> N >> M;
	cin >> fuel;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAT[i][j];
		}
	}

	cin >> taxi.y >> taxi.x;

	for (int i = 0; i < M; i++)
	{
		coordi st, ed;
		cin >> st.y >> st.x;
		cin >> ed.y >> ed.x;

		pas_st.push_back(st);
		pas_ed.push_back(ed);

	}

	return 0;
}

int pas_sel; // Á¤ÇØÁø ½Â°´
unordered_set<int> us; // ½Â°´ÀÌ Å¿´ÂÁö ¾ÈÅ¿´ÂÁö setÀ¸·Î

// µµÂøÁö º¤ÅÍ¿Í, ½Â°´ÀÌ ÀÖ´ÂÁö
int bfs(vector<coordi>& ed, int exist)
{
	queue<Info> q;
	q.push({ taxi, 0 });
	int visited[MAT_MAX][MAT_MAX] = { 0, };
	visited[taxi.y][taxi.x] = 1;
	int pas_find = -1; // ¼Õ´ÔÀ» Ã£¾Ò°í ±× ¼Õ´ÔÀÇ index
	int pas_dis; // Å¾½Â ¼Õ´ÔÀÇ °Å¸®

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		for (int i = 0; i < ed.size(); i++)
		{
			if (ed[i] != now.pt) continue;

			if (!exist) // Å¾½Â°´ ¿¡°Ô µµÂø
			{
				if (us.find(i) != us.end()) continue;
				if (pas_find < 0) // ÀÌ °Å¸®ÀÇ ½Â°´ Ã¹ ¹ß°ß
				{
					pas_find = i;
					pas_dis = now.cnt;

					us.insert(pas_find);
					pas_sel = pas_find;
					taxi = ed[pas_find];

					fuel -= now.cnt;
				}
				else
				{
					if (pas_dis < now.cnt)
					{
						us.insert(pas_find);
						pas_sel = pas_find;
						taxi = ed[pas_find];
						return 1;
					}

					int change_flag = 0;
					// Á¶°Ç
					if (pas_st[pas_find].y > pas_st[i].y)
					{
						change_flag = 1;
					}
					else if (pas_st[pas_find].y == pas_st[i].y)
					{
						if (pas_st[pas_find].x > pas_st[i].x)
						{
							change_flag = 1;
						}
					}


					if (change_flag)
					{
						us.erase(pas_find);
						pas_find = i;

						us.insert(pas_find);
						pas_sel = pas_find;
						taxi = ed[pas_find];
					}
				}


			}
			else // µµÂøÁö¿¡ µµÂø
			{
				fuel += now.cnt;
				taxi = ed[i];
				return 1;
			}
		}

		// ¿¬·á ´Ù ¾µ ¶§ ±îÁö µµÂø ¸øÇÔ
		if (now.cnt == fuel) continue;

		for (int i = 0; i < 4; i++)
		{
			coordi next = { ry[i], rx[i] };
			next.y += now.pt.y;
			next.x += now.pt.x;

			if (MAT[next.y][next.x] == 1) continue;
			if (visited[next.y][next.x] == 1) continue;

			visited[next.y][next.x] = 1;
			q.push({ next, now.cnt + 1 });
		}
	}

	if (pas_find < 0)

		return 0;

	return 1;
}


int solve_func()
{
	while (pas_st.size() != us.size())
	{
		if (!bfs(pas_st, 0))
			return -1;

		vector<coordi> sel_ed{ pas_ed[pas_sel] }; // µµÂøÁö´Â Á¤ÇØÁ® ÀÖÀ½.

		if (!bfs(sel_ed, 1))
			return -1;

	}

	return fuel;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	init();
	input();


	cout << solve_func();
	return 0;
}