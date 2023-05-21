#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAX_TREE = 101010;

struct Info // 트리 정보 구조체
{
	int to;
	int len; // 간선 길이
};

int N;
vector<Info> tree[MAX_TREE];

int input()
{
	cin >> N;

	int from, to, l;

	for (int i = 0; i < N; i++)
	{
		cin >> from;

		while (1)
		{
			cin >> to;
			if (to == -1)
				break;
			cin >> l;

			tree[from].push_back({ to, l });
		}

	}
	return 0;
}

int visited[MAX_TREE];
int max_depth = 0, max_node;
int dfs(int now, int depth)
{
	// 1. 가장 깊은 노드를 찾자
	if (max_depth < depth)
	{
		max_depth = depth;
		max_node = now;
	}

	for (auto next : tree[now])
	{
		if (visited[next.to] == 1) continue;

		visited[next.to] = 1;
		// 2. 탐색하지 않은 노드 로 재귀
		dfs(next.to, depth + next.len);
	}

	return 0;
}


int solve_func()
{
	// dfs 할 때 시작 지점 visited 체크 해주자
	visited[1] = 1;
	dfs(1, 0);
	memset(visited, 0, sizeof(visited));
	visited[max_node] = 1; 
	dfs(max_node, 0);

	cout << max_depth;

	return 0;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	input();
	solve_func();
	return 0;
}