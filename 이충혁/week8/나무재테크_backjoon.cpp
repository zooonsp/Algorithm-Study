#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAT_MAX = 13;

const int ry[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
const int rx[] = { 0, 0, -1, 1, 1, -1, 1, -1 };


int N, M, K; // N: 정사각형 땅의 길이, M: 나무의 갯수, K: 몇년 키울건지
int robot_work[MAT_MAX][MAT_MAX]; // 로봇이 주는 양분 정보
int land[MAT_MAX][MAT_MAX]; // 땅의 현재 양분 상황
int dead_trees[MAT_MAX][MAT_MAX]; // 죽은 나무 정보

vector<int> tree[MAT_MAX][MAT_MAX]; // 나무정보 

struct coordi {
	int y, x;
};

int init()
{
	for (int i = 0; i < MAT_MAX; i++)
	{
		for (int j = 0; j < MAT_MAX; j++)
		{
			land[i][j] = 5;
		}
	}

	return 0;
}

int input()
{
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> robot_work[i][j];
		}
	}

	for (int i = 0; i < M; i++)
	{
		int y, x, age;
		cin >> y >> x >> age;

		tree[y][x].push_back(age);
	}
	return 0;
}

int solve_func()
{
	int ans = 0;

	while (K--)
	{
		memset(dead_trees, 0, sizeof(dead_trees));
		vector<coordi> five_tree; // 번식 가능 나무

		// 봄 : 양분 먹여서 나이 + , 못먹으면 죽이기
		for (int i = 1; i <= N; i++) // i, j 는 좌표, k 는 나이값
		{
			for (int j = 1; j <= N; j++)
			{

				if (tree[i][j].empty()) continue;

				vector<int> temp;

				sort(tree[i][j].begin(),tree[i][j].end()); // 나이 적은순 부터 양분 주려고

				for (int k = 0; k < tree[i][j].size(); k++) 
				{
					if (land[i][j] < tree[i][j][k]) 
					{
						dead_trees[i][j] += tree[i][j][k] / 2; // 양분 충분하지 않으면 죽이기
					}

					else 
					{
						land[i][j] -= tree[i][j][k];
						temp.push_back(tree[i][j][k] + 1);
						if ((tree[i][j][k] + 1) % 5 == 0) // 5의 배수 나이 인 나무 미리 모아놈
							five_tree.push_back({ i, j });
					}
				}

				tree[i][j] = temp; // 모아논 나이 1씩 증가한 벡터 다시 넣어주기
			}
		}

		// 여름 : 죽은 나무 양분 주기
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (dead_trees[i][j] == 0) continue;
				land[i][j] += dead_trees[i][j];
			}
		}
		// 가을 : 나무 번식, 번식하는 나무는 나이가 5의 배수, 인접한 모든 칸에 나이 1인 나무 생김
		while (!five_tree.empty())
		{
			coordi now = five_tree.back();
			five_tree.pop_back();

			for (int i = 0; i < 8; i++)
			{
				coordi next;
				next.x = now.x + rx[i];
				next.y = now.y + ry[i];

				if (next.y < 1 || next.y > N || 
					next.x < 1 || next.x > N) continue;

				tree[next.y][next.x].push_back(1);
			}
		}


		// 겨울 : 로봇이 땅에 양분 추가 각 칸에 추가되는 양분 A[r][c]

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
				land[i][j] += robot_work[i][j];
		}
	}
	

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			ans += tree[i][j].size();
	}

	return ans;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	init();
	input();
	
	cout << solve_func();

	return 0;
}