#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
LCA 알고리즘에 min, max 값만 추가로 저장하자
*/

const int TREE_SIZE = 101010;
const int DEPTH_SIZE = 20;
const int NODE_SIZE = 101010;

struct NODE_INFO {
	int to;
	int len;
};

struct LCA_INFO {
	int a, b; // LCA 2개 노드
};


int N, K; // N: 노드의 갯수,  K: 도시쌍 갯수
int parent[TREE_SIZE][DEPTH_SIZE]; //부모 정보
int depth[TREE_SIZE]; // 노드 별 깊이 정보
int min_road[TREE_SIZE][DEPTH_SIZE]; // LCA 안의 최소 도로 길이
int max_road[TREE_SIZE][DEPTH_SIZE]; // LCA 안의 최대 도로 길이
vector<NODE_INFO> graph[TREE_SIZE];
vector<LCA_INFO> LCA_vals;

int init()
{
	for (int i = 0; i < TREE_SIZE; i++)
	{
		depth[i] = -1;

		for (int j = 0; j < DEPTH_SIZE; j++)
		{
			min_road[i][j] = 21e8;
		}
	}

	depth[1] = 0; // 임의로 루트 노드 1로 


	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N - 1; i++) // 트리의 엣지 정보: 노드 갯수 -1 
	{
		int from, to, len;
		cin >> from >> to >> len;
		graph[from].push_back({ to, len });
		graph[to].push_back({ from, len }); 
	}

	cin >> K;

	for (int i = 0; i < K; i++)
	{
		int a, b;
		cin >> a >> b;
		LCA_vals.push_back({ a, b });
	}
	return 0;
}

int dfs_parent(int now, int len)
{
	min_road[now][0] = max_road[now][0] = len;

	for (NODE_INFO node : graph[now])
	{
		if (depth[node.to] == -1)
		{
			depth[node.to] = depth[now] + 1;
			parent[node.to][0] = now;
			dfs_parent(node.to, node.len);
		}
	}

	return 0;
}

int connect() // 깊이 값에 따른 부모 값 갱신
{
	for (int i = 1; i < DEPTH_SIZE; i++)
	{
		for (int now = 2; now <= N; now++)
		{
			parent[now][i] = parent[parent[now][i - 1]][i - 1];
			min_road[now][i] = min(min_road[parent[now][i - 1]][i - 1], min_road[now][i - 1]);
			max_road[now][i] = max(max_road[parent[now][i - 1]][i - 1], max_road[now][i - 1]);
		}

	}
	return 0;
}

int solve_func()
{
	// LCA 만들기
	dfs_parent(1, 0);
	connect();

	for (auto val : LCA_vals)
	{
		int min_ans = 21e8;
		int max_ans = 0;

		// LCA 하기 위해 깊이 맞추기
		if (depth[val.a] < depth[val.b])
		{
			swap(val.a, val.b);
		}

		int dist = depth[val.a] - depth[val.b];

		for (int i = 0; dist != 0; i++)
		{
			if (dist % 2 == 1)
			{
				min_ans = min(min_ans, min_road[val.a][i]);
				max_ans = max(max_ans, max_road[val.a][i]);
				val.a = parent[val.a][i]; // 2의 승수 만큼 다음 부모로 점프
			}

			dist = dist>>1;
		}

		// 깊이를 맞췄을 떄 노드가 같다면 공통 부모는 b
		if (val.a == val.b)
		{
			cout << min_ans << " " << max_ans << "\n";
			continue;
		}

		// 깊이가 같아졌으니 올라가 본다
		for (int i = DEPTH_SIZE - 1; i >= 0; i--) // 깊이 맞출 때 처럼 점프해서 찾자
		{
			if (parent[val.a][i] != 0 && parent[val.b][i] != 0 &&
				parent[val.a][i] != parent[val.b][i])
			{
				min_ans = min(min_ans, min_road[val.a][i]);
				min_ans = min(min_ans, min_road[val.b][i]);

				max_ans = max(max_ans, max_road[val.a][i]);
				max_ans = max(max_ans, max_road[val.b][i]);

				val.a = parent[val.a][i];
				val.b = parent[val.b][i];
			}
		}

		min_ans = min(min_ans, min_road[val.a][0]);
		min_ans = min(min_ans, min_road[val.b][0]);

		max_ans = max(max_ans, max_road[val.a][0]);
		max_ans = max(max_ans, max_road[val.b][0]);

		cout << min_ans << " " << max_ans << "\n";
	}



	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	init();
	input();
	solve_func();

	return 0;
}