#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 좌표와 비용 정보를 가진 구조체
// PQ에서 낮은 cost 우선
struct Node
{
	int y;
	int x;
	int cost;
	bool operator<(Node next) const
	{
		if (cost < next.cost)
			return false;
		if (cost > next.cost)
			return true;
		return false;
	}
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

const int MAX = 987654321;
int N, M;					 // N: 지도의 가로 세로 길이, M: 터널의 개수
int MAP[30][30];			 // 지도
int dist[30][30];			 // 해당 좌표까지 가는데 필요한 최소 연료
vector<Node> tunnel[30][30]; // 해당 좌표에 연결된 터널(반대편 출구 좌표 및 연료 소모량 vector)

void dijkstra()
{
	priority_queue<Node> pq;
	pq.push({0, 0, 0});
	dist[0][0] = 0;

	while (!pq.empty())
	{
		Node now = pq.top();
		pq.pop();

		if (dist[now.y][now.x] < now.cost)
			continue;

		// 터널 이용
		for (auto &next : tunnel[now.y][now.x])
		{
			// now까지 오는데 필요한 최소 연료 + 터널 이용 시 필요한 연료
			int ncost = dist[now.y][now.x] + next.cost;

			if (dist[next.y][next.x] <= ncost)
				continue;

			pq.push({next.y, next.x, ncost});
			dist[next.y][next.x] = ncost;
		}

		// 상하좌우 이동
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N)
				continue;

			int ncost = dist[now.y][now.x]; // now까지 오는데 필요한 최소 연료

			if (MAP[now.y][now.x] == MAP[ny][nx]) // 평지 => 1의 연료 소모
				ncost += 1;
			else if (MAP[now.y][now.x] < MAP[ny][nx]) // 오르막길 => 높이 차이의 2배 소모
				ncost += (MAP[ny][nx] - MAP[now.y][now.x]) * 2;

			if (dist[ny][nx] <= ncost)
				continue;

			pq.push({ny, nx, ncost});
			dist[ny][nx] = ncost;
		}
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{

		cin >> N >> M;

		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				cin >> MAP[y][x];
				dist[y][x] = MAX;	  // dist를 MAX값으로 초기화
				tunnel[y][x].clear(); // tunnel 초기화
			}
		}

		for (int i = 0; i < M; i++)
		{
			int ay, ax, by, bx, c;
			cin >> ay >> ax >> by >> bx >> c;
			// 터널은 양방향으로 이동 가능, 좌표는 0부터 시작
			tunnel[ay - 1][ax - 1].push_back({by - 1, bx - 1, c});
			tunnel[by - 1][bx - 1].push_back({ay - 1, ax - 1, c});
		}

		dijkstra();

		// (N-1, N-1)까지 가는데 필요한 최소 연료 출력
		cout << '#' << tc << ' ' << dist[N - 1][N - 1] << '\n';
	}

	return 0;
}
