#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAX_TEAM = 555;

int N, M; // N : 팀수, M : 상대적인 등수가 바뀐 쌍의 수
int visited[MAX_TEAM];
int graph[MAX_TEAM][MAX_TEAM];
int ord_rank[MAX_TEAM];

int init()
{
	memset(visited, 0, sizeof(visited));
	memset(graph, 0, sizeof(graph));
	memset(ord_rank, 0, sizeof(ord_rank));
	return 0;
}

int input()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> ord_rank[i];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			// 나중 순위에 있다면 그래프에 경로로 모두 표시하자
			graph[ord_rank[i]][ord_rank[j]] = 1;
			// 위상 정렬을 위해 앞순위가 얼마나 있는지도 확인
			visited[ord_rank[j]]++;
		}
	}

	cin >> M;

	// 바뀐 부분의 visited와 graph 갱신
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;

		if (graph[from][to] != 1)
			swap(from, to);

		graph[from][to] = 0;
		graph[to][from] = 1;
		visited[from]++;
		visited[to]--;

	}

	return 0;
}

int solve_func()
{
	vector<int> ans;
	queue<int> q;
	for (int i = 1; i <= N; i++)
	{
		if (visited[i] == 0)
		{
			q.push(i);
		}

	}

	while (!q.empty())
	{
		if (q.size() >= 2)
		{
			cout << "?\n";
			return 0;
		}
		int now = q.front();
		q.pop();

		ans.push_back(now);


		for (int i = 1; i <= N; i++)
		{
			if (graph[now][i] == 1)
			{
				visited[i]--;
				if (visited[i] == 0)
				{
					q.push(i);
				}
			}
		}

	}

	if (ans.size() != N)
		cout << "IMPOSSIBLE\n";
	else
	{
		for (auto& val : ans)
			cout << val << " ";
		cout << "\n";
	}

	return 0;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		init();
		input();
		solve_func();
	}


	return 0;
}