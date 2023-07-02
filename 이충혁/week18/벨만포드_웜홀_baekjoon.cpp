#include<iostream>
#include<vector>

using namespace std;

typedef long long ll;

struct Info {
	int to;
	int w; // 걸리는 시간
};

const ll MAX_VAL = 9e18;
const int MAX_PT = 555; // 지점 갯수

int N, M, W; // 지점 갯수, 도로 갯수, 웜홀 갯수
ll dist[MAX_PT];
vector<Info> graph[MAX_PT];

int init()
{
	for (int i = 0; i < MAX_PT; i++)
	{
		dist[i] = MAX_VAL;
		graph[i].clear(); // 초기화를 잘하자
	}


	// 임의로 1번 시작지점
	dist[1] = 0;
	return 0;
}

int input()
{
	cin >> N >> M >> W;
	int from, to, w;
	for (int i = 0; i < M; i++)
	{
		cin >> from >> to >> w;
		graph[from].push_back({ to, w });
		graph[to].push_back({ from, w });
	}

	for (int i = 0; i < W; i++)
	{
		cin >> from >> to >> w;
		graph[from].push_back({ to, -w }); // 웜홀은 시간 감소
	}
	return 0;
}

// 음의 싸이클 존재하면 1 return
int solve_func()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			for (auto now : graph[j])
			{
				// 이번 문제의 경우 MAX_VAL로 제한하면 
				// dist가 제대로 갱신 되지 않는다.
				ll temp = dist[j] + now.w; 
				if (dist[now.to] > temp)
				{
					dist[now.to] = temp;

					if (i == N) return 1;
				}
			}
		}
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
		if (solve_func())
			cout << "YES\n";
		else
		{
			cout << "NO\n";
		}
	}


	return 0;
}