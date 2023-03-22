#include<iostream>
#include<vector>
using namespace std;

const int MAT_MAX = 110;

enum COORDI_ENUM {
	U, R, D, L
};

const int ry[] = { -1, 0, 1, 0 }; // 방향 좌표 12시부터 시계방향
const int rx[] = { 0, 1, 0, -1 };

// 완전 탐색, 시뮬레이션으로 구현
struct coordi {
	int y, x;
	bool operator !=(coordi next) const
	{
		if (y != next.y || x != next.x)
			return true;

		return false;
	}
};

int N;
int MAT[MAT_MAX][MAT_MAX];
vector <coordi> wormhole[15];




int init()
{
	for (int i = 0; i < MAT_MAX; i++)
		for (int j = 0; j < MAT_MAX; j++)
		{
			MAT[i][j] = 5;
		}

	for (int i = 0; i < 10; i++)
		wormhole[i].clear();


	return 0;
}

int input()
{
	cin >> N;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			cin >> MAT[i][j];
			if (MAT[i][j] > 5) // 웜홀 저장 어떻게?
			{
				wormhole[MAT[i][j]].push_back({ i, j });
			}
		}

	return 0;
}


// 현재 이동중인 방향과 벽의 종류 를 입력 받는다.
int bump_wall(int& dir, int wall)
{
	switch (wall)
	{
	case 1:
		switch (dir)
		{
		case U:
			dir = (dir + 2) % 4;
			break;
		case D:
			dir = R;
			break;
		case R:
			dir = (dir + 2) % 4;
			break;
		case L:
			dir = U;
			break;
		}
		break;
	case 2:
		switch (dir)
		{
		case U:
			dir = R;
			break;
		case D:
			dir = (dir + 2) % 4;
			break;
		case R:
			dir = (dir + 2) % 4;
			break;
		case L:
			dir = D;
			break;
		}
		break;
	case 3:
		switch (dir)
		{
		case U:
			dir = L;
			break;
		case D:
			dir = (dir + 2) % 4;
			break;
		case R:
			dir = D;
			break;
		case L:
			dir = (dir + 2) % 4;
			break;
		}
		break;
	case 4:
		switch (dir)
		{
		case U:
			dir = (dir + 2) % 4;
			break;
		case D:
			dir = L;
			break;
		case R:
			dir = U;
			break;
		case L:
			dir = (dir + 2) % 4;
			break;
		}
		break;
	case 5:
		dir = (dir + 2) % 4;
		break;

	}
	return 0;
}




// 좌표를 이동시키기만 해서 재귀 안씀
int dfs(coordi st, int dir)
{
	int ret = 0;
	coordi now = st;
	coordi temp_worm;

	do
	{
		coordi next = now;
		next.y += ry[dir];
		next.x += rx[dir];

		// 블랙홀 일 떄
		if (MAT[next.y][next.x] == -1) break;

		// 벽에 부딪혔을 때
		if (MAT[next.y][next.x] >= 1 && MAT[next.y][next.x] <= 5)
		{
			// 반대 벽만 전단계로 나머지는 그대로
			bump_wall(dir, MAT[next.y][next.x]);

			ret++;
		}

		// 웜홀 일 때
		else if (MAT[next.y][next.x] > 5)
		{
			// 웜홀 중에 다른 한쪽으로 좌표 이동
			for (int i = 0; i < 2; i++)
			{
				temp_worm = wormhole[MAT[next.y][next.x]][i];
				if (temp_worm.y == next.y && temp_worm.x == next.x) continue;

				now = temp_worm;
			}
			continue;
		}
		// 암것도 아닐 떄

		now = next;



	} while (now != st);


	return ret;
}

int solve_func()
{
	int ans = 0;

	for (int i = 1; i <= N; i++) // y좌표
	{
		for (int j = 1; j <= N; j++) // x 좌표
		{
			if (MAT[i][j] != 0) continue;

			for (int dir = 0; dir < 4; dir++)
			{
				int temp = dfs({ i, j }, dir);

				if (ans < temp)
					ans = temp;
			}

		}
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