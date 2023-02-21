#include<iostream>
using namespace std;

const int MAX = 20;

enum {
	PLUS, MINUS, MULTI, DIVIDE
};

int N;
int num[MAX];
int calc[4];
int MAP[MAX];
int mn, mx;

int init()
{
	for (int i = 0; i < MAX; i++)
		MAP[i] = 0;


	mn = 111111111;
	mx = -111111111;
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < 4; i++)
		cin >> calc[i];
	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
	}
	return 0;
}

int dfs(int level) // level 1 부터 시작
{
	if (level == N)
	{
		if (MAP[level - 1] < mn)
			mn = MAP[level - 1];
		if (MAP[level - 1] > mx)
			mx = MAP[level - 1];
		
		return 0;
	}

	for (int i = 0; i < 4; i++)
	{
		if (calc[i] == 0) continue;

		if (i == PLUS)
		{
			MAP[level] = MAP[level - 1] + num[level];
			calc[i] --;
			dfs(level + 1);
			calc[i] ++;
		}
		else if (i == MINUS)
		{
			MAP[level] = MAP[level - 1] - num[level];
			calc[i] --;
			dfs(level + 1);
			calc[i] ++;
		}
		else if (i == MULTI)
		{
			MAP[level] = MAP[level - 1] * num[level];
			calc[i] --;
			dfs(level + 1);
			calc[i] ++;
		}
		else if (i == DIVIDE)
		{
			MAP[level] = MAP[level - 1] / num[level];
			calc[i] --;
			dfs(level + 1);
			calc[i] ++;
		}


	}


	return 0;
}


int solve_func()
{
	MAP[0] = num[0];
	dfs(1);

	return 0;
}



int main(int argc, char** argv)
{
	//freopen("input.txt", "r", stdin);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		solve_func();
		cout << "#" << test_case << " " << mx - mn << "\n";
	}
	return 0;
}