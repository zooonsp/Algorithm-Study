#include<iostream>
#include<cmath>
using namespace std;
const int MAX = 25;

int N, X;
int MAP[MAX][MAX];

int init()
{
	return 0;
}

int input()
{
	cin >> N >> X;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	return 0;
}


int row_cnt()
{
	int ret = 0;
	int check_right[MAX][MAX] = { 0, };
	int check_left[MAX][MAX] = { 0, }; 
	int fail[MAX] = { 0, };

	for (int i = 0; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			int dist = MAP[i][j - 1] - MAP[i][j];
			if (abs(dist) > 1) // 높이가 2이상이면 설치 안됨
			{
				fail[i] = 1;
				break;
			}
			else if (dist > 0) // 왼쪽에서부터 내려가는 모양
			{
				// 이미 check 가 있었는가
				if (check_right[i][j - 1] > 1)
				{
					fail[i] = 1;
					break;
				}

				// check 경사로가 크기를 벗어 나는 가
				if (j + X > N)
				{
					fail[i] = 1;
					break;
				}
				check_right[i][j] = X; // 경사로를 위해 필요한 크기 저장
			}
			else
			{
				if (check_right[i][j - 1] != 0) // 경사로를 설치 중이라면 전 값 - 1
 				{
					check_right[i][j] = check_right[i][j - 1];
					check_right[i][j]--;
				}

			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (fail[i]) // 반대쪽에서 fail이 이미 됬다면 건너뜀
			continue;
		for (int j = N - 2; j >= 0; j--)
		{
			int dist = MAP[i][j + 1] - MAP[i][j];

			if (dist > 0) // 오른쪽에서부터 내려가는 모양
			{
        // check 경사로가 크기를 벗어 나는 가
				if (j - X + 1 < 0)
				{
					fail[i] = 1;
					break;
				}
				// 이미 반대 방향 check 값이 있었는가
				else if (check_right[i][j] != 0)
				{
					fail[i] = 1;
					break;
				}
				// 이미 같은 방향 check 값이 있었는가
				else if (check_left[i][j + 1] > 1)
				{
					fail[i] = 1;
					break;
				}

				check_left[i][j] = X;// 경사로를 위해 필요한 크기 저장
			}
			else
			{
				if (check_left[i][j + 1] != 0) // 경사로를 설치 중이라면 전 값 - 1
				{
					check_left[i][j] = check_left[i][j + 1];
					check_left[i][j]--;

					if (check_left[i][j] != 0 && check_right[i][j] != 0) // 설치중인 양 방향이 겹치는지
					{
						fail[i] = 1;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
		if (fail[i] == 0)
			ret++;


	return ret;
}

int MAP_copy[MAX][MAX];
// matrix transpose 해줌
int trans()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			MAP_copy[i][j] = MAP[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			MAP[i][j] = MAP_copy[j][i];

	return 0;
}

int solve_func()
{
	int ans = 0;

	ans += row_cnt();
	trans();
	ans += row_cnt();

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
