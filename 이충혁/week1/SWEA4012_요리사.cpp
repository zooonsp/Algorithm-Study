#include<iostream>
#include<cmath>
using namespace std;
const int MAX = 20;

int N;
int MAP[MAX][MAX];
int visited[MAX];
int mn;

int init()
{
	mn = 2000101101;
	for (int i = 0; i < MAX; i++)
		visited[i];
	return 0;
}
int input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	return 0;
}

int dfs(int level, int limit)
{
	if (level == N / 2)
	{
		int cook1 = 0, cook2 = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				if (visited[i] && visited[j])
				{
					cook1 = cook1 + MAP[i][j] + MAP[j][i];
				}

				if (!visited[i] && !visited[j])
				{
					cook2 = cook2 + MAP[i][j] + MAP[j][i];
				}
			}

		}
		int temp = abs(cook1 - cook2);
		if (temp < mn)
		{
			mn = temp;
		}

		return 0;
	}

	for (int i = limit; i < N; i++)
	{
		if (visited[i] == 1) continue;

		visited[i] = 1;
		dfs(level + 1, i + 1);
		visited[i] = 0;
	}
	return 0;
}

int solve_func()
{
	visited[0] = 1;
	dfs(1, 1);
	return 0;
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
		solve_func();
		cout << "#" << test_case << " " << mn << "\n";
	}
	return 0;
}