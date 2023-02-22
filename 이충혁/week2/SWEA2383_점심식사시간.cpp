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

// priority queue는 거리 기준으로, 들어올 때 시간 값도 같이 저장
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
int MAP[MAX][MAX]; // 공간 배열
vector<point> person; // 사람들만 저장
Stairs_Info stairs[2]; // 계단은 2개만 있음
int select_cnt; // 계단에 가는 모든 경우를 2진수로 쓸 예정 
                // 사람이 4명이라면 0000 ~ 1111 까지
int sel[MAX]; // select_cnt를 2진수 변환해서 다 분리해서 저장


	
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
	priority_queue<Stairs_order> pq[2]; // 각 계단별 priority queue
	queue<int> stair_use[2];

  //각 계단별 pq에 그 계단을 이용하는 사람들을 다 넣어줌
	for (int i = 0; i < person.size(); i++)
	{
		pq[sel[i]].push({ abs(person[i].x - stairs[sel[i]].pt.x) + abs(person[i].y - stairs[sel[i]].pt.y)
			, stairs[sel[i]].cnt });
	}

	int ret = 0;

  // 각 계단별로 시간을 구해서 최대값 return
	for (int i = 0; i < 2; i++)
	{
		int time = 0;
		while (!pq[i].empty() || !stair_use[i].empty())
		{
			time++;
			
			// 계단 이용이 끝나면 stair_use 비워줌
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
      
      // 시간이 되면 계단이용
			while (1)
			{
				if (pq[i].empty()) break; // pq 가 비었으면 continue;
				if (pq[i].top().dist > time) break;
				if (stair_use[i].size() >= 3) break; // 3명이 쓰고 있으면 못 씀

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

	int pow_res = pow(2, person.size()); // 2^(사람수) : 사람수 만큼 계단을 나눠가는 경우의 수
	
	for (int i = 0; i < pow_res; i++)
	{
		int temp = find_time();
		select_func(); // select 값 증가 시키고 배열 다시 세팅
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