#include<iostream>
#include<vector>
using namespace std;


const int MAX = 15;

int N, M, K; //벌통 크기, 선택할수 있는 벌통 개수, 채취 할수 있는 최대양
int hive[MAX][MAX]; // 벌통 들
int hive_price[MAX][MAX]; // 벌통 가격

int init()
{
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
		{
			hive[i][j] = 0;
			hive_price[i][j] = 0;
		}


	return 0;
}

int input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cin >> hive[i][j];
			hive_price[i][j] = hive[i][j] * hive[i][j];
		}

	return 0;
}

int path[MAX] = { 0, };
int sum = 0;
int sum_price = 0;
int mx = 0;

int dfs(int level, int *hive_temp, int *hive_price_temp)
{
	if (level == M)
	{
		int temp = 0;
		for (int i = 0; i < M; i++)
		{
			temp += path[i];
		}
		if (mx < temp)
			mx = temp;
		return 0;
	}


	for (int i = 0; i < 2; i++)
	{
		sum += hive_temp[level] * i;
		if (sum > K)
		{
			sum -= hive_temp[level];
			continue;
		}
		
		path[level] = hive_price_temp[level] * i;
		dfs(level + 1, hive_temp, hive_price_temp);
		sum -= hive_temp[level] * i;
	}

	return 0;
}


int solve_func()
{
	int col_sum[MAX] = { 0, };
	int row_sum[MAX] = { 0, };
	int col_max[2] = { 0, };
	int ans;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - M + 1; j++)
		{
			sum = 0;
			mx = 0;
			dfs(0, &hive[i][j], &hive_price[i][j]);
			if (col_sum[i] < mx)
				col_sum[i] = mx;
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - M; j++)
		{
			sum = 0;
			mx = 0;

			int row1 = dfs(0, &hive[i][j], &hive_price[i][j]);
			int row2;
			for (int k = j + M; k < N - M; k++)
			{

				sum = 0;
				mx = 0;
				row2 = dfs(0, &hive[i][k], &hive_price[i][k]);

				if (row1 + row2 > row_sum[i])
					row_sum[i] = row1 + row2;
			}

		}
	}



	for (int i = 0; i < N; i++)
	{
		if (col_max[0] < col_sum[i])
		{
			col_max[1] = col_max[0];
			col_max[0] = col_sum[i];
		}
		else if (col_max[1] < col_sum[i])
		{
			col_max[1] = col_sum[i];
		}
	}

	ans = col_max[0] + col_max[1];

	for (int i = 0; i < N; i++)
	{
		if (ans < row_sum[i])
			ans = row_sum[i];
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
		input();
		cout << "#" << test_case << " "  << solve_func() << "\n";
	}
	return 0;
}