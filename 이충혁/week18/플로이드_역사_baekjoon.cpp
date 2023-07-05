#include<iostream>
#include<algorithm>
using namespace std;

const int MAX_VAL =	1e8; // val 따지지 않을거라 어떤 값이어도 상관 없음
const int MAX_EVENT = 444;

int N, M; // N 도시수, M 버스수
int dist[MAX_EVENT][MAX_EVENT];


int init()
{
	for(int i=0; i< MAX_EVENT; i++)
		for (int j = 0; j < MAX_EVENT; j++)
		{
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = MAX_VAL;
		}
	return 0;
}

int input()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		dist[from][to] = 0;
	}
	return 0;
}

int solve_func()
{
	// 플로이드
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			for (int k = 1; k <= N; k++)
			{
				dist[j][k] = min(dist[j][k], dist[i][k] + dist[j][i]);
			}
		}
	}

	int cmd, from, to;
	cin >> cmd;
	for (int i = 0; i < cmd; i++)
	{
		cin >> from >> to;
		if (dist[from][to] == MAX_VAL && dist[to][from] == MAX_VAL)
			cout << "0\n";
		else if (dist[from][to] == MAX_VAL)
			cout << "1\n";
		else
			cout << "-1\n";
	}
	return 0;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	init();
	input();
	solve_func();

	return 0;
}