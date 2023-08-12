#include <iostream>
#include <deque>
using namespace std;


/*
N 크기의 체스판에서 K개의 말갯수가 순차적으로 움직일 때,
말이 언제 모두 쌓이는지 , 1000횟수 이상이면 안되는 것으로 판단하여 -1 출력
*/

struct coordi
{
	int y, x;

	bool operator ==(const coordi& next) const
	{
		if (y == next.y && x == next.x)
			return 1;
		return 0;
	}
};

struct Info
{
	coordi pt;
	int dir;
};

const int ry[] = { 0, 0, 0, -1, 1 };
const int rx[] = { 0, 1, -1, 0, 0 };

const int MAP_SIZE = 15;
const int PIECE_SIZE = 15;

int N, K;
int MAP[MAP_SIZE][MAP_SIZE] = { 0, };
Info piece[PIECE_SIZE] = { 0, };
deque<int> piece_deq[PIECE_SIZE];

int init_func()
{
	// 파란색으로 울타리 쳐주기
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			MAP[i][j] = 2;
		}
	}

	// 큐 자기 자신 미리 쌓아 놓기
	for (int i = 1; i < PIECE_SIZE; i++)
	{
		piece_deq[i].push_back(i);
	}

	return 0;
}

int input_func()
{
	cin >> N >> K;


	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> MAP[i][j];
		}
	}

	for (int i = 1; i <= K; i++)
	{
		int y, x, dir;
		cin >> y >> x >> dir;
		piece[i] = { {y,x}, dir };
	}
	return 0;
}

bool complete()
{
	for (int i = 1; i <= K; i++)
	{
		if (piece_deq[i].size() >= 4)
			return 1;
	}

	return 0;
}

int solve_func()
{
	// 몇 번째 턴인지
	int ans = 1;


	while (1)
	{
		if (ans > 1000)
			return -1;

		for (int i = 1; i <= K; i++)
		{
			if (piece_deq[i].empty())
				continue;

			coordi next = piece[i].pt;
			next.y += ry[piece[i].dir];
			next.x += rx[piece[i].dir];

			int dir_reverse; // switch case 내부에 변수 초기화 하지 말자
			coordi next_of_next;
			int deq_back;


			switch (MAP[next.y][next.x])
			{
			case 0:
				// 일단 옮기고
				piece[i].pt = next;

				// 이미 있는 말이 있다면 업히고 지금 움직인 말의 정보를 모두 깔끔히 지워주자
				for (int j = 1; j <= K; j++)
				{
					if (j == i) continue;

					if (next == piece[j].pt)
					{
						if (piece_deq[j].empty())
							continue;

						// 다 업히기
						while (!piece_deq[i].empty())
						{
							int front = piece_deq[i].front();
							piece_deq[i].pop_front();
							piece_deq[j].push_back(front);
						}

						break;
					}
				}

				break;
			case 1:
				// 일단 옮기고
				piece[i].pt = next;

				if (piece_deq[i].size() <= 1)
					break;

				// 말이 없을 때도 뒤집혀야 함으로
				deq_back = piece_deq[i].back();

				while (!piece_deq[i].empty())
				{
					int back = piece_deq[i].back();
					piece_deq[i].pop_back();
					piece_deq[deq_back].push_back(back);
				}
				piece[deq_back].pt = next;

				// 하양과 똑같이 해주지만 뒤집어서 저장해주자
				for (int j = 1; j <= K; j++)
				{
					if (j == deq_back) continue;

					if (next == piece[j].pt)
					{
						if (piece_deq[j].empty())
							continue;

						// 다 업히기
						while (!piece_deq[deq_back].empty())
						{
							int front = piece_deq[deq_back].front();
							piece_deq[deq_back].pop_front();
							piece_deq[j].push_back(front);
						}

						break;
					}
				}





				break;
			case 2:
				next_of_next = piece[i].pt;
				dir_reverse = piece[i].dir;
				// 이거 하드코딩 말고 방법 없나
				if (dir_reverse == 1) dir_reverse = 2;
				else if (dir_reverse == 2) dir_reverse = 1;
				else if (dir_reverse == 3) dir_reverse = 4;
				else if (dir_reverse == 4) dir_reverse = 3;

				next_of_next.y += ry[dir_reverse];
				next_of_next.x += rx[dir_reverse];

				piece[i].dir = dir_reverse;

				// 또 파란색이면 방향 만 바꾸고 탈출
				if (MAP[next_of_next.y][next_of_next.x] == 2)
					continue;

				piece[i].pt = next_of_next;

				// 하얀색에 했던 걸 또 해준다 ( 클린코드.... )
				for (int j = 1; j <= K; j++)
				{
					if (j == i) continue;

					if (next_of_next == piece[j].pt)
					{
						if (piece_deq[j].empty())
							continue;

						// 다 업히기
						while (!piece_deq[i].empty())
						{
							int front = piece_deq[i].front();
							piece_deq[i].pop_front();
							piece_deq[j].push_back(front);
						}

						break;
					}
				}


				break;
			default:
				cout << "ERROR!!\n";
				break;
			}

		}


		// 끝났냐!
		if (complete())
			return ans;

		ans++;
	}


	// ERROR!
	return -999;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	init_func();
	input_func();
	cout << solve_func() << "\n";



	return 0;
}