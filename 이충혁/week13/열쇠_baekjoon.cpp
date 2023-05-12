#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

const int MAX_MAT = 110;
const int ASCII_SIZE = 130;

const int EMPTY = (int)('.');
const int WALL = (int)('*');
const int DOCS = (int)('$');

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct coordi {
	int y, x;
};

int H, W; // 높이와 너비
int MAT[MAX_MAT][MAX_MAT]; // 입력되는 행렬 int 정보
int key_DAT[ASCII_SIZE];
int visited[MAX_MAT][MAX_MAT]; // bfs visited 체크

int init()
{
	memset(key_DAT, 0, sizeof(key_DAT));
	memset(visited, 0, sizeof(visited));
	return 0;
}

int input()
{
	string str;
	cin >> H >> W;

	for (int i = 0; i < H; i++)
	{
		cin >> str;
		for (int j = 0; j < W; j++)
		{
			MAT[i][j] = (int)str[j];
		}

	}

	cin >> str;
	for (const char& temp_key : str)
	{
		key_DAT[(int)temp_key] = 1;
	}

	return 0;
}


int solve_func()
{
	int ans = 0;
	queue <coordi> q; // bfs 돌 큐
	vector<coordi> door_blocking[ASCII_SIZE];

	// 1. 가장 자리를 모두 출발지로 큐에

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (i != 0 && j != 0 && i != H - 1 && j != W - 1) continue;
			if (MAT[i][j] == WALL) continue; // 벽이라 건물 밖에서 못들어옴
			if (MAT[i][j] >= 'A' && MAT[i][j] <= 'Z') // 문이라면
			{
				int temp = MAT[i][j] - 'A' + 'a';
				// 키가 DAT에 있다면 q에추가 없다면 blockin 벡터에 추가
				if (key_DAT[temp])
				{
					q.push({ i,j });
				}
				else
				{
					door_blocking[temp].push_back({ i, j });
					continue;
				}
			}
			else
			{
				q.push({ i,j }); // 갈 수 있는 가장자리라 추가	
			}
			visited[i][j] = 1;
		}
	}

	// 2. bfs
	int temp_key;
	while (!q.empty())
	{
		coordi now = q.front();
		q.pop();

		// 문서면 ans 증가
		if (MAT[now.y][now.x] == DOCS)
			ans++;

		// 키면 블로킹 전부 큐에주가 후 해당 키에 블로킹 날려 버리자
		if (MAT[now.y][now.x] >= 'a' && MAT[now.y][now.x] <= 'z')
		{
			temp_key = MAT[now.y][now.x];
			key_DAT[temp_key] = 1; // 키 DAT 갱신 키를 주웠다!
			for (const coordi& pt : door_blocking[temp_key])
			{
				q.push(pt);
			}
			vector<coordi>().swap(door_blocking[temp_key]);
		}

		for (int i = 0; i < 4; i++)
		{
			coordi next = now;
			next.y += ry[i];
			next.x += rx[i];

			if (next.y < 0 || next.y >= H ||
				next.x < 0 || next.x >= W) continue;

			if (MAT[next.y][next.x] == WALL) continue;
			if (visited[next.y][next.x] == 1) continue;

			visited[next.y][next.x] = 1;

			// 문일 떄는 열쇠가 있는지 확인 한후
			// 1) 열쇠가 있으면 그냥 통과
			// 2) 열쇠가 없으면 블로킹에 추가

			if (MAT[next.y][next.x] >= 'A' && MAT[next.y][next.x] <= 'Z')
			{
				temp_key = MAT[next.y][next.x] - 'A' + 'a';
				// 키가 없으면 좌표 블로킹에 넣고 q에는 넣지않는다
				if (key_DAT[temp_key] != 1)
				{
					door_blocking[temp_key].push_back(next);
					continue;
				}
			}

			q.push(next);
		}
	}


	return ans;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		init();
		input();
		cout << solve_func() << "\n";
	}

	return 0;
}