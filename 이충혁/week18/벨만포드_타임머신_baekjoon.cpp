#include<iostream>
#include<vector>

using namespace std;

typedef long long ll;

struct Info {
	int to;
	int w; // 걸리는 시간
};

const ll MAX_VAL = 9e18;
const int MAX_CITY = 555;

int N, M; // 도시 갯수, 버스 노선 갯수
ll dist[MAX_CITY];
vector<Info> graph[MAX_CITY];

int init()
{
	for (int i = 0; i < MAX_CITY; i++)
		dist[i] = MAX_VAL;

	// 1번에서 시작 
	dist[1] = 0;
	return 0;
}

int input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int from, to, w;
		cin >> from >> to >> w;
		graph[from].push_back({ to, w });
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
				if (dist[j] == MAX_VAL) continue; // 지정한 MAX_VAL의 가까이에서 더해지면 음수로 최소값이 갱신됨!
				ll temp = dist[j] + now.w; // 보존하는 변수도 longlong 으로...
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

	init();
	input();
	if (solve_func())
		cout << -1;
	else
	{
		for (int i = 2; i <= N; i++)
		{
			if (dist[i] != MAX_VAL)
				cout << dist[i] << "\n";
			else
				cout << -1 << "\n";
		}
	}
	
	return 0;
}