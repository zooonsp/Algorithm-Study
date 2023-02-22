#include<iostream>
#include<vector>
using namespace std;

// 군집 구조체 ( 좌표와 개수 )
struct Node {
	int y, x;
	int dir;
	int cnt;
};

// 한번 이동후 MAP 기록을 위한 구조체
struct Meet {
	int max, max_index;
	int sum;
};

// 방향 좌표를 위한 열거
enum {
	U, D, L, R
};

const int ry[] = { -1, 1, 0, 0 }; // 상하좌우
const int rx[] = { 0, 0, -1, 1 };
const int MAX = 110;

int N, M, K; 
vector<Node> micro;

int init()
{
	micro.clear();
	return 0;
}

int input()
{
	Node temp;
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++)
	{
		cin >> temp.y >> temp.x >> temp.cnt >> temp.dir;
		temp.dir--;
		micro.push_back(temp);
	}

	return 0;
}

int solve_func()
{
	int length = micro.size();
	int sum = 0;
	for (int i = 0; i < M; i++)
	{
		Meet MAP[MAX][MAX] = { 0, };

		for (int j = 0; j < length; j++)
		{
			if (micro[j].cnt == 0) continue;

			Node next; // 이동하는 좌표
			next.y = micro[j].y + ry[micro[j].dir];
			next.x = micro[j].x + rx[micro[j].dir];

			//약품에 빠진 경우
			if (next.y == 0 || next.y == N - 1 ||
				next.x == 0 || next.x == N - 1)
			{
				micro[j].cnt = micro[j].cnt / 2;

				if (next.y == 0) micro[j].dir = D;
				else if (next.y == N - 1) micro[j].dir = U;
				else if (next.x == 0) micro[j].dir = R;
				else if (next.x == N - 1) micro[j].dir = L;
			}
			// 겹치는 경우
			else if (MAP[next.y][next.x].sum)
			{
				if (MAP[next.y][next.x].max < micro[j].cnt)
				{
					//MAP에 있는 max 보다 새로운 값이 크면 MAP값 이번 index 값으로 새로 세팅 
					// and sum 값 가져오기
					MAP[next.y][next.x].max = micro[j].cnt;
					MAP[next.y][next.x].sum += micro[j].cnt;
					micro[j].cnt = MAP[next.y][next.x].sum;

					micro[MAP[next.y][next.x].max_index].cnt = 0; // MAP에 저장 되어서 갯수 0개로

					MAP[next.y][next.x].max_index = j;
				}
				else
				{
					MAP[next.y][next.x].sum += micro[j].cnt; // MAP에 저장된 갯수 값에 추가
					micro[MAP[next.y][next.x].max_index].cnt += micro[j].cnt;
					micro[j].cnt = 0;
				}
			}
			else
			{
				MAP[next.y][next.x].sum = micro[j].cnt;
				MAP[next.y][next.x].max = micro[j].cnt;
				MAP[next.y][next.x].max_index = j;
			}

			micro[j].y = next.y;
			micro[j].x = next.x;
		}

	}

	for (int j = 0; j < length; j++)
	{
		sum += micro[j].cnt;
	}
	return sum;
}



int main(int argc, char** argv)
{
	//freopen("input.txt", "r", stdin);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		cout << "#" << test_case << " " << solve_func() << "\n";
	}
	return 0;
}