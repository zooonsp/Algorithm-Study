#include<iostream>

using namespace std;

enum{
	DAY,
	MONTH,
	MONTH_3,
	YEAR,
};

int pay[4]; // 일, 1개월, 3개월 ,년
int month[12];
int mn;
int sum; // dfs 에서 합

int input()
{
	for (int i = 0; i < 4; i++)
		cin >> pay[i];
	for (int i = 0; i < 12; i++)
		cin >> month[i];

	return 0;
}

int dfs(int level)
{
	if (level >= 12)
	{
		if (mn > sum)
			mn = sum;
		return 0;
	}

	if (month[level] == 0)
	{
		dfs(level + 1);
		return 0;
	}

	int temp = pay[DAY] * month[level];
	sum += temp;
	if (mn > sum)
	{
		dfs(level + 1);
	}
	sum -= temp;

	sum += pay[MONTH];
	if (mn > sum)
	{
		dfs(level + MONTH);
	}
	sum -= pay[MONTH];

	sum += pay[MONTH_3];
	if (mn > sum)
	{
		dfs(level + 3);
	}
	sum -= pay[MONTH_3];


	return 0;
}

int solve_func()
{
	mn = pay[YEAR];

	dfs(0);

	return 0;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// init
		sum = 0;

		input();
		solve_func();

		cout << "#" << test_case << " " << mn << "\n";
	}
	return 0;
}