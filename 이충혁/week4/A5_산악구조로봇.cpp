#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAX_MAT = 33;
const int MAX = 21e8;

const int ry[] = { 0, 1 };
const int rx[] = { 1, 0 };

struct point
{
	int y, x;
};

struct Info_route
{
	point to; // 도착 지점
	int fuel; // 여기까지 도달 하기 위한 연료 양 

	bool operator < (Info_route next) const
	{
		if (fuel < next.fuel)
			return false;

		if (fuel > next.fuel)
			return true;

		return false;
	}
};

struct Info_turnel
{
	point pt1, pt2; // 터널 두 입구
	int fuel; // 터널 통과시 드는 연료
};

// 다익스트라로 풀이
// MAT 동서 남북 방향을 모두 엣지로 놓고
// 터널도 엣지로 놓고 1,1 좌표에서 연료 최소로 드는 길들을 탐색

int N, M; // N: 지도 변의 길이, M: 터널의 갯수
int MAT[MAX_MAT][MAX_MAT]; // 지도 높이 값
vector<Info_route> graph[MAX_MAT][MAX_MAT]; // 다익스트라 노드 정보
Info_turnel tunnel[MAX_MAT];


int init()
{
	for (int i = 0; i < MAX_MAT; i++)
		for (int j = 0; j < MAX_MAT; j++)
		{
			MAT[i][j] = -1;
			graph[i][j].clear();

		}

	memset(tunnel, 0, sizeof(tunnel));

	return 0;
}

int input()
{
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> MAT[i][j];
	}

	point A, B;
	int fuel;

	for (int i = 0; i < M; i++)
	{
		cin >> A.y >> A.x >> B.y >> B.x >> fuel;

		tunnel[i] = { A, B, fuel };
	}

	return 0;
}


int dijk(point start)
{
	priority_queue<Info_route> pq;
	int fuel[MAX_MAT][MAX_MAT]; // 각 좌표마다 최소 가 되는 연료양 저장 할 거임
	// 좌표마다 연료 값을 MAX로 초기화
	for (int i = 0; i < MAX_MAT; i++)
		for (int j = 0; j < MAX_MAT; j++)
			fuel[i][j] = MAX;

	pq.push({ start, 0 });
	fuel[start.y][start.x] = 0;

	while (!pq.empty())
	{
		Info_route now = pq.top();
		pq.pop();

		// pq에서 나온 now 보다 이미 적은 연료가 드는 경우가 fuel에 있으면
		if (fuel[now.to.y][now.to.x] < now.fuel) continue;

		for (int i = 0; i < graph[now.to.y][now.to.x].size(); i++)
		{
			Info_route next = graph[now.to.y][now.to.x][i];
			next.fuel = next.fuel + now.fuel;

			// 이미 탐색 된 좌표면
			if (fuel[next.to.y][next.to.x] <= next.fuel) continue;

			fuel[next.to.y][next.to.x] = next.fuel;
			pq.push(next);
		}
	}

	return fuel[N][N]; // N, N 제일 짧은 경로
}

int solve_func()
{

	// 다익스트라 하기 위해 노드 연결 해주기 
	// 1. 동서남북 방향 노드 vector에 저장
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{

			for (int k = 0; k < 2; k++)
			{
				// i, j 가 from
				point to;
				to.y = i + ry[k];
				to.x = j + rx[k];

				if (MAT[to.y][to.x] == -1) continue;

				// to 가 from 높이 보다 크면 
				// 정방향에 드는 연료 = 높이 * 2
				// 역방향에 드는 연료 = 0
				if (MAT[to.y][to.x] > MAT[i][j])
				{
					graph[i][j].push_back({ to, (MAT[to.y][to.x] - MAT[i][j]) * 2 });
					graph[to.y][to.x].push_back({ { i, j }, 0 });
				}
				// to 가 from 높이 보다 작으면
				// 정방향에 드는 연료 = 0
				// 역방향에 드는 연료 = 높이 * 2
				else if (MAT[to.y][to.x] < MAT[i][j])
				{
					graph[i][j].push_back({ to, 0 });
					graph[to.y][to.x].push_back({ { i, j }, (MAT[i][j] - MAT[to.y][to.x]) * 2 });
				}
				else
				{
					graph[i][j].push_back({ to, 1 });
					graph[to.y][to.x].push_back({ { i, j }, 1 });
				}
			}
		}
	}
	// turnel 노드 기록
	for (int i = 0; i < M; i++)
	{
		graph[tunnel[i].pt1.y][tunnel[i].pt1.x].push_back({ tunnel[i].pt2, tunnel[i].fuel });
		graph[tunnel[i].pt2.y][tunnel[i].pt2.x].push_back({ tunnel[i].pt1, tunnel[i].fuel });
	}




	return dijk({ 1, 1 });
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;


	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		cout << "#" << tc << " " << solve_func() << "\n";
	}
	return 0;
}