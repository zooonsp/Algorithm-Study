#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int TREE_SIZE = 202020;
const int DEPTH_SIZE = 20; // log2(200000) : 약 18   
const int NODE_SIZE = 202020;

struct LCA_Info { // LCA 구할 2개 노드
	int a, b;
};

struct edge_Info {
	int from, to, w; // w: 가중치(지나갈 수 있는 온도)

	bool operator < (edge_Info next) const
	{
		if (w < next.w)
			return true;
		return false;
	}
};

//input data
int N, M; // N: 정점의 갯수, M: 간선의 갯수, 쿼리는 solve_func 에서 입력 받으면서 처리한다.
vector<edge_Info> edge;

//union find parent
int u_parent[TREE_SIZE];

int sub_tree[TREE_SIZE]; // 해당 노드 가 가지고 있는 서브 노드 수
int weight[TREE_SIZE]; // 해당 노드까지의 최대 가중치
int parent[TREE_SIZE][DEPTH_SIZE]; //노드의 깊이값 위에 해당하는 부모 정보
int depth[TREE_SIZE]; // 노드 별 깊이 정보
vector<int> graph[TREE_SIZE];
int node_cnt = 0;
vector<LCA_Info> LCA_vals;

int init()
{
	for (int i = 0; i < TREE_SIZE; i++)
	{
		u_parent[i] = -1;
		sub_tree[i] = 1; // 서브트리 더해서 구할거라 1로 초기화
	}

	return 0;
}

int input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int from, to, w;
		cin >> from >> to >> w;
		edge.push_back({from, to, w});
	}

	return 0;
}


int find(int now)
{
	if (u_parent[now] < 0)
		return now;

	return u_parent[now] = find(u_parent[now]);
}

int Union()
{
	sort(edge.begin(), edge.end());

	node_cnt = N;
	for (auto e : edge)
	{
		int pa = find(e.from);
		int pb = find(e.to);

		if (pa == pb) continue;

		node_cnt++;
		graph[node_cnt].push_back(pa);
		graph[node_cnt].push_back(pb);
		u_parent[pa] = node_cnt;
		u_parent[pb] = node_cnt;
		sub_tree[node_cnt] = sub_tree[pa] + sub_tree[pb];
		weight[node_cnt] = e.w;
	}
	return 0;
}


int dfs_parent(int now, int level) // 깊이는 now 까지 하고 갱신 (루트가 어딘지 모름)
{
	depth[now] = level;
	for (int node : graph[now])
	{
		if (node == now) continue;
		parent[node][0] = now;
		dfs_parent(node, level + 1);

	}

	return 0;
}

int connect() // 깊이 값에 따른 부모 값 갱신
{
	for (int i = 1; i < DEPTH_SIZE; i++)
	{
		for (int now = 1; now <= node_cnt; now++)
			parent[now][i] = parent[parent[now][i - 1]][i - 1];
	}
	return 0;
}

int LCA(LCA_Info val)
{
	// LCA 전 깊이 맞추기
	if (depth[val.a] < depth[val.b])
	{
		swap(val.a, val.b);
	}
	int dist = depth[val.a] - depth[val.b];

	for (int i = 0; dist != 0; i++)
	{
		if ((dist & 1) == 1)
			val.a = parent[val.a][i];
		dist /= 2;
	}

	// 깊이 맞춘후 같으면 이미 공통조상
	if (val.a == val.b)
	{
		return  val.b;
	}


	// 부모쪽으로 올라가기
	for (int i = DEPTH_SIZE - 1; i >= 0; i--)
	{
		if (parent[val.a][i] != parent[val.b][i])
		{
			val.a = parent[val.a][i];
			val.b = parent[val.b][i];
		}
	}

	return  parent[val.b][0];
}



int solve_func()
{
	Union(); // 결합 하면서 새로운 그래프 생성

	for (int i = 1; i <= node_cnt; i++)
	{
		if (u_parent[i] >= 0) continue;

		dfs_parent(i, 0);
	}

	connect();

	int Q; // 쿼리의 갯수
	cin >> Q;
	for (int i = 0; i < Q; i++)
	{
		int x, y;
		cin >> x >> y;


		if (find(x) == find(y))
		{
			int val = LCA({ x, y });
			cout << weight[val] << ' ' << sub_tree[val] << '\n';
		}
		else
			cout << -1 << '\n';
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