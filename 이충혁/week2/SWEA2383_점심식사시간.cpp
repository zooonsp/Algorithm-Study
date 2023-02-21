#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
const int MAX = 11;

struct point {
	int y, x;
};

struct Stairs_Info{
	point pt;
	int cnt;
};

struct Stairs_order{
	int dist;
	int time;

	bool operator < (Stairs_order next) const{
		if (dist < next.dist)
			return false;

		if (dist > next.dist)
			return true;
		return false;
	}
};

int min(int a, int b)
{
	return (a < b) ? a : b;
}



int N;
int MAP[MAX][MAX];
vector<point> person;
Stairs_Info stairs[2];
int sel[MAX];
int select_cnt;

	
int init()
{
	person.clear();

	for (int i = 0; i < MAX; i++)
		sel[i] = 0;

	select_cnt = 0;
	return 0;
}


int input()
{
	int temp = 0;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] == 1)
			{
				person.push_back({ i, j });
			}
			else if (MAP[i][j] > 1 ) // 계단
			{
				stairs[temp] = { { i, j }, MAP[i][j] };
				temp++;
			}
		}
	}
	return 0;
}




int select_func()
{
	select_cnt++;
	int temp = 0;
	int select_temp = select_cnt;


	while (select_temp != 0)
	{
		sel[temp] = select_temp % 2;
		select_temp = select_temp / 2;
		temp++;
	}

	return 0;
}

int find_time()
{
	priority_queue<Stairs_order> pq[2];
	queue<int> stair_use[2];

	for (int i = 0; i < person.size(); i++)
	{
		pq[sel[i]].push({ abs(person[i].x - stairs[sel[i]].pt.x) + abs(person[i].y - stairs[sel[i]].pt.y)
			, stairs[sel[i]].cnt });
	}

	int ret = 0;

	for (int i = 0; i < 2; i++)
	{
		int time = 0;
		while (!pq[i].empty() || !stair_use[i].empty())
		{
			time++;
			while (1)
			{
				if (!stair_use[i].empty())
					if ((stair_use[i].front() + stairs[i].cnt) <= time)
					{
						stair_use[i].pop();
						continue;
					}

				
				break;
			}

			while (1)
			{
				if (pq[i].empty()) break; // pq 가 비었으면 continue;
				if (pq[i].top().dist > time) break;
				if (stair_use[i].size() >= 3) break;

				stair_use[i].push(time);
				pq[i].pop();
			}

		}

		if (ret < time)
			ret = time;
	}



	return ret + 1;
}

int solve_func()
{
	int ans = 21e8;

	int pow_res = pow(2, person.size());
	
	for (int i = 0; i < pow_res; i++)
	{


		int temp = find_time();
		select_func();
		if (ans > temp)
			ans = temp;
	}





	return ans;
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
		cout << "#" << test_case << " " << solve_func() << "\n";

	}
	return 0;
}