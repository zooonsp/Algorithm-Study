#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int MAX_ST = 32323;
int N, M; // N 학생, M 비교
int visited[MAX_ST];
vector<int> graph[MAX_ST];

int input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		graph[from].push_back(to);
		visited[to]++;
	}

	return 0;
}

int solve_func()
{
	queue<int> q;
	for (int i = 1; i <= N; i++)
	{
		if (visited[i] == 0)
		{
			q.push(i);
			visited[i] = -1;
		}

	}

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		cout << now << " ";

		for (int val : graph[now])
		{
			if (visited[val] > 0)
				visited[val] --;
		}

		for (int i = 1; i <= N; i++)
		{
			if (visited[i] == 0)
			{
				q.push(i);
				visited[i] = -1;
			}
		}
	}

	return 0;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	input();
	solve_func();

	return 0;
}