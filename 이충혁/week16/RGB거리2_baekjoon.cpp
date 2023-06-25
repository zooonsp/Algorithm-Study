#include<iostream>
using namespace std;

const int MAX_SIZE = 1010;

int N;
int rgb[MAX_SIZE][3]; // size, rgb
int dp[3][MAX_SIZE][3]; // 시작 부분, size, rgb


// 원형 형태로 되는 것을 어떻게 풀까
/*
인덱스 들을 저장??? 마지막을 첫 인덱스에 대비 해서

*/

int input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
			cin >> rgb[i][j];
	}
	return 0;
}

int solve_func()
{
	int ans = 21e8;
	for (int i = 0; i < 3; i++) // 시작 색
	{
		dp[i][0][i] = rgb[0][i];
		for (int j = 1; j < N; j++) // 몇번째 갱신 하는지
		{
			for (int k = 0; k < 3; k++) // 이번 번째의 무슨 색을 갱신하는지
			{
				if (dp[i][j - 1][(k + 1) % 3] == 0 && dp[i][j - 1][(k + 2) % 3] == 0) continue;
				dp[i][j][k] = rgb[j][k];

				if (dp[i][j - 1][(k + 1) % 3] == 0)
					dp[i][j][k] += dp[i][j - 1][(k + 2) % 3];

				else if (dp[i][j - 1][(k + 2) % 3] == 0)
					dp[i][j][k] += dp[i][j - 1][(k + 1) % 3];

				else if (dp[i][j - 1][(k + 1) % 3] < dp[i][j - 1][(k + 2) % 3])
					dp[i][j][k] += dp[i][j - 1][(k + 1) % 3];
				else
					dp[i][j][k] += dp[i][j - 1][(k + 2) % 3];
			}
		}

		int temp;
		if (dp[i][N - 1][(i + 1) % 3] < dp[i][N - 1][(i + 2) % 3])
			temp = dp[i][N - 1][(i + 1) % 3];
		else
			temp = dp[i][N - 1][(i + 2) % 3];

		if (ans > temp)
			ans = temp;

	}


	return ans;
}

int main()
{
	cin.tie()->sync_with_stdio(false);

	input();
	cout << solve_func();

	return 0;
}