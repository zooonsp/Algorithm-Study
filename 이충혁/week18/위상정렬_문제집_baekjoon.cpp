#include<iostream>
#include<vector>
using namespace std;

const int MAX_NODE = 101010;

int N, M;
vector<int> graph[MAX_NODE];
int topo[MAX_NODE] = { 0, };

int input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int from, to;

		cin >> from >> to;

		topo[to]++;
		graph[from].push_back(to);
	}
	return 0;
}

int solve_func()
{
	int cnt = 0;

	while (cnt < N)
	{
		for (int i = 1; i <= N; i++)
		{
			if (topo[i] == 0)
			{
				topo[i] = -1; // 풀었다

				if (!graph[i].empty())
				{
					for (auto& val : graph[i])
					{
						topo[val]--;
					}
				}

				cout << i << " ";
				cnt++;

				break;
			}
		}
	}
	return 0;
}

int main()
{
	cin.tie();
	input();
	solve_func();
	return 0;
}