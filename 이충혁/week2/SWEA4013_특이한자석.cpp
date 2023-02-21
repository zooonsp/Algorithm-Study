#include<iostream>
using namespace std;

struct cmd_Info{
	int sel, cmd;
};

int K;
int magnet[6][10];
int magnet_index[6];
cmd_Info cycles[30];


int init()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
			magnet[i][j] = -100;

		magnet_index[i] = 1;
	}
	return 0;
}

int input()
{
	cin >> K;

	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			cin >> magnet[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		int sel, cmd;

		cin >> sel >> cmd;

		cycles[i] = { sel, cmd };
	}

	return 0;
}

int cycle_func(int &index, int dir)
{
	index -= dir;

	if (index < 1)
	{
		index = 8;
	}
	else if (index > 8)
	{
		index = 1;
	}
	return 0;
}

int visited[10] = { 0, };

int dfs(int sel, int cmd)
{
	
	visited[sel] = 1;

	// ¿À¸¥ÂÊ
	if (magnet[sel][(magnet_index[sel] + 1) % 8 + 1] +
		magnet[sel + 1][(magnet_index[sel + 1] + 5) % 8 + 1] == 1 && 
		visited[sel + 1] == 0 )
		dfs(sel + 1, cmd * -1);
	
	// ¿ÞÂÊ

	if (magnet[sel][(magnet_index[sel] + 5) % 8 + 1] +
		magnet[sel - 1][(magnet_index[sel - 1] + 1) % 8 + 1] == 1 &&
		visited[sel - 1] == 0)
		dfs(sel - 1, cmd * -1);

	cycle_func(magnet_index[sel], cmd);

	return 0;
}

int score[5] = { 0, 1, 2, 4, 8 };

int solve_func()
{
	int ans = 0;

	for (int i = 0; i < K; i++)
	{
		for (int j = 1; j <= 8; j++)
			visited[j] = 0;
		dfs(cycles[i].sel, cycles[i].cmd);
	}


	for (int i = 1; i <= 4; i++)
	{
		ans += score[i] * magnet[i][magnet_index[i]];
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