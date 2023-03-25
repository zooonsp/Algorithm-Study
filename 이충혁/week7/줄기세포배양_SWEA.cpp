#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;
const int MAX_MAT = 700; // 배양시간이 300 이고 격자크기가 50이라 650까지만 큼
const int STAND_MAT = 320; // 중간 지점을 여기로 ( 음수 방지 )

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct coordi {
	int y, x;
};

struct Info { // 세포 정보 {coordi, int, int}
	coordi pt; // 좌표
	int life; // 생명력
	int time; // 태어난 시간

	bool operator < (Info next) const
	{
		if (life > next.life)
			return true;

		return false;
	}
};

int N, M, K; // N: 세로크기, M: 가로크기, K: 배양시간
int MAT[MAX_MAT][MAX_MAT]; // 그리드 셀 정보

list <Info> alive_cells; // 살아있는 (활성화, 비활성화) 세포

int init()
{
	memset(MAT, 0, sizeof(MAT));
	alive_cells.clear();

	return 0;
}

int input()
{
	cin >> N >> M >> K;

	for (int i = STAND_MAT; i < STAND_MAT + N; i++)
	{
		for (int j = STAND_MAT; j < STAND_MAT + M; j++)
		{
			cin >> MAT[i][j];
			if (MAT[i][j] == 0) continue;

			alive_cells.push_back({ {i, j}, MAT[i][j] });
		}
	}

	return 0;
}

int solve_func()
{
	alive_cells.sort();

	for (int time = 1; time <= K; time++)
	{
		// 1. 번식 ( 번식은 활성화 되고 한번만 해도 됨 )
		for (auto it = alive_cells.begin(); it != alive_cells.end(); it++)
		{
			if (it->time + it->life + 1 != time) continue; // 번식시간 아님
			coordi now = it->pt;
			auto insert_it = it;
			insert_it++;
			for (int i = 0; i < 4; i++)
			{
				coordi next;
				next.y = now.y + ry[i];
				next.x = now.x + rx[i];

				if (MAT[next.y][next.x] != 0) continue;

				MAT[next.y][next.x] = it->life;
				alive_cells.insert(insert_it, { next, it->life, time });
			}
		}
		auto it = alive_cells.begin();
		// 2. 죽이기
		while (it != alive_cells.end())
		{
			if (it->time + it->life * 2 == time)
			{
				it = alive_cells.erase(it);
			}
			else
			{
				it++;
			}

		}
	}
	return alive_cells.size();
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