#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<set>
using namespace std;

struct Info {
	int from, to;

	bool operator!=(const Info& next) const
	{
		if (from == next.from && to == next.to)
			return true;

		return false;
	}
};

const int MAX_SIZE = 10101;

int V, E; // V 정점 수, E 간선 수
int tree_cnt = 0;
int dfsn[MAX_SIZE] = { 0, };
set<int> cutvertex;
vector<int> graph[MAX_SIZE];

int input()
{
	cin >> V >> E;
	for (int i = 0; i < E; i++)
	{
		int from, to;
		cin >> from >> to;

		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	return 0;
}

int dfs(int now, int prev)
{
	int ret;

	tree_cnt++;
	ret = dfsn[now] = tree_cnt;

	int child_cnt = 0;
	for (auto next : graph[now])
	{

		// 부모 노드면 이미 탐색 했으므로 건너 뛴다
		if (next == prev) continue;

		// 방문 했으면 dfsn 갱신되어 있음. 역방향 간선 넘어가자
		if (dfsn[next] > 0)
		{
			ret = min(ret, dfsn[next]);
			continue;
		}
		child_cnt++; // 역방향 간선에 포함된 자식들은 넘어가며 세야한다 (루트노드가 단절점인지 판단 할 때)

		int temp = dfs(next, now);
		ret = min(ret, temp);

		// temp가 dfsn[now]와 같거나 크면 now와 연결된 BCC가 이전 (상위 호출 스택)의 BCC와 다르다.
		if (prev != 0 && temp >= dfsn[now])
		{
			if(cutvertex.find(now) == cutvertex.end())
				cutvertex.insert(now);
		}
	}

	// 루트고 자식이 2 이상이면 단절점
	if (prev == 0 && child_cnt >= 2)
		if (cutvertex.find(now) == cutvertex.end())
			cutvertex.insert(now);

	return ret;
}

int solve_func()
{
	for (int i = 1; i <= V; i++)
	{
		// dfs 안돌았으면 돌리자
		if (dfsn[i] == 0)
			dfs(i, 0);
	}

	cout << cutvertex.size() << "\n";
	for (auto val : cutvertex)
	{
		cout << val << " ";
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