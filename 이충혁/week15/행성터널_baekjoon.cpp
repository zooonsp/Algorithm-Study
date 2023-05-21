#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX_NODE = 101010;

struct Edge {
	int from, to;
	int w;
};

struct PLANET_INFO {
	int index; // 몇번쨰 행성인지
	int loc; // 행성의 좌표값
};

bool cmp(Edge left, Edge right)
{
	if (left.w < right.w)
		return true;

	return false;
}

bool PL_cmp(PLANET_INFO left, PLANET_INFO right)
{
	if (left.loc < right.loc)
		return true;

	return false;
}

int parent[MAX_NODE];

int Find(int now)
{
	if (now == parent[now])
		return now;
	return parent[now] = Find(parent[now]);
}

void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb)
		return;

	parent[pb] = pa;
}

int N; // 행성의 갯수
vector<PLANET_INFO> planet[3]; // 0 : x, 1 : y, 2 : z 각각 행성의 좌표값
vector<Edge> vec;

int init()
{
	for (int i = 0; i < MAX_NODE; i++)
		parent[i] = i;
	return 0;
}

int input()
{
	cin >> N;

	// x, y, z 값 따로 따로 저장 하자
	for (int i = 1; i <= N; i++)
	{
		int pl_x, pl_y, pl_z;

		cin >> pl_x >> pl_y >> pl_z;

		planet[0].push_back({ i, pl_x });
		planet[1].push_back({ i, pl_y });
		planet[2].push_back({ i, pl_z });
	}

	return 0;
}

int solve_func() // krusckal
{
	int sum = 0, cnt = 0;

	// 행성 좌표 값들 정렬 하고 엣지에 추가
	for (int i = 0; i < 3; i++)
	{
		sort(planet[i].begin(), planet[i].end(), PL_cmp);

		for (int j = 1; j < N; j++)
		{
			vec.push_back({ planet[i][j - 1].index, planet[i][j].index, abs(planet[i][j].loc - planet[i][j - 1].loc)});
		}
	}

	sort(vec.begin(), vec.end(), cmp);

	for (int i = 0; i < vec.size(); i++)
	{
		Edge now = vec[i];
		if (Find(now.from) == Find(now.to))
			continue;

		sum += now.w;

		cnt++;
		if (cnt == N - 1) break;

		Union(now.from, now.to);
	}

	return sum;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	init();
	input();
	cout << solve_func();
	return 0;
}