#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int TREE_SIZE = 101010;
const int DEPTH_SIZE = 20; // log2(50000) = 15,   15이상으로
const int NODE_SIZE = 101010;

struct INFO { // LCA 구할 2개 노드
	int a, b;
};


int N, M; // N: 노드의 갯수, M 알고싶은 쌍의 갯수
int parent[TREE_SIZE][DEPTH_SIZE]; //노드의 깊이값 위에 해당하는 부모 정보
int depth[TREE_SIZE]; // 노드 별 깊이 정보
vector<int> graph[TREE_SIZE];
vector<INFO> LCA_vals;

int init()
{
	for (int i = 0; i < TREE_SIZE; i++)
	{
		depth[i] = -1;
	}

	depth[1] = 0; // 루트 노드 : 1

	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N - 1; i++) // (주의) 트리의 엣지 정보라서 노드 갯수 -1 
	{
		int from, to;
		cin >> from >> to;
		graph[from].push_back(to);
		graph[to].push_back(from); // 양방향으로 쓰자
	}

	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		LCA_vals.push_back({ a, b });
	}
	return 0;
}

int dfs_parent(int now) // 자식 노드 깊이 현재 깊이 + 1로 갱신, 자식노드의 직접적인 부모 노드값 저장
{
	for (int node : graph[now])
	{
		if (depth[node] == -1)
		{
			depth[node] = depth[now] + 1;
			parent[node][0] = now;
			dfs_parent(node);
		}
	}

	return 0;
}

int connect() // 깊이 값에 따른 부모 값 갱신
{
	for (int i = 1; i < DEPTH_SIZE; i++)
	{
		for (int now = 2; now <= N; now++)
			parent[now][i] = parent[parent[now][i - 1]][i - 1];
	}
	return 0;
}

int solve_func()
{
	// 1. LCA 하기 위한 parent, depth 만들기
	dfs_parent(1); 
	connect(); 

	for (auto val : LCA_vals)
	{
		// 2. LCA 하기 위해 깊이 맞추기
		if (depth[val.a] < depth[val.b]) // 깊이가 큰걸 a로 바꾸고
		{
			swap(val.a, val.b);
		}

		int dist = depth[val.a] - depth[val.b];

		for (int i = 0; dist != 0; i++)
		{
			if (dist % 2 == 1)
				val.a = parent[val.a][i]; // 2의 승수 만큼 다음 부모로 가서 더 빨리 깊이 이동이 가능
			dist /= 2;
		}

		// 3. 깊이를 맞췄을 떄 노드가 같다면 공통 부모는 b
		if (val.a == val.b)
		{
			cout << val.b << "\n";
			continue;
		}

		// 4. 깊이가 같아졌으니 올라가 본다
		for (int i = DEPTH_SIZE - 1; i >= 0; i--) // 깊이 맞출 때 처럼 점프해서 찾자
		{
			if (parent[val.a][i] != 0 && parent[val.b][i] != 0 &&
				parent[val.a][i] != parent[val.b][i])
			{
				val.a = parent[val.a][i];
				val.b = parent[val.b][i];
			}
		}

		cout << parent[val.b][0] << "\n";
	}



	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	init();
	input();
	solve_func();

	return 0;
}