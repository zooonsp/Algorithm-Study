#include<iostream>
#include<algorithm>
using namespace std;

const int MAX_VAL =	1e8;
const int MAX_CITY = 111;

int N, M; // N 도시수, M 버스수
int dist[MAX_CITY][MAX_CITY];


int init()
{
	for(int i=0; i<MAX_CITY; i++)
		for (int j = 0; j < MAX_CITY; j++)
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
		int from, to, w;
		cin >> from >> to >> w;
		dist[from][to] = min(dist[from][to],w);
	}
	return 0;
}

int solve_func()
{
	// 플로이드 와샬
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			for (int k = 1; k <= N; k++)
			{
				// 버그 1: 같은 시작지점 도착지점을 갖는 버스도 있다.
				dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
			}
		}
	}

	// 출력
	for (int i = 1; i <= N; i++)
	{
		for(int j=1; j<= N; j++)
		{
			// 버그 2 : 못도착한경우 예외처리
			if (dist[i][j] == MAX_VAL)
				cout << "0 ";
			else
				cout << dist[i][j] << " ";
		}
		cout << "\n";
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