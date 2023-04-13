#include<iostream>
#include<string>
#include<queue>
using namespace std;

const int MAT_MAX = 12; // N, M의 최대값
const int CNT_MAX = 12; // 최대로 움직일 수 있는 수 : 10 

enum {
	WALL = 1,
	HOLE = 2,
	RED = 3,
	BLUE = 4
};

struct coordi
{
	int y, x;

	bool operator==(coordi next) const
	{
		if (y == next.y && x == next.x)
			return true;
		return false;
	}

	coordi operator+(coordi next)const
	{
		coordi temp;
		temp.y = y + next.y;
		temp.x = x + next.x;
		return temp;
	}
};

const coordi dir[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


struct Info // 구슬 상황 red, blue
{
	coordi red;
	coordi blue;
	int cnt;
};

int N, M; // 세로, 가로 
int MAT[MAT_MAX][MAT_MAX];

coordi blue_st; // 구슬 시작지점
coordi red_st;

void input()
{
	string str;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		cin >> str;
		for (int j = 0; j < M; j++) // 벽 = 1, 구멍 = 2, 빨간공 = 3, 파란공 = 4 로 배열에 저장
		{
			switch (str[j])
			{
			case '#':
				MAT[i][j] = WALL;
				break;
			case 'O':
				MAT[i][j] = HOLE;
				break;
			case 'R':
				MAT[i][j] = RED;
				red_st = { i, j };
				break;
			case 'B':
				MAT[i][j] = BLUE;
				blue_st = { i, j };
			}
		}
	}
	return;
}




int bfs()
{
	queue<Info> q;
	q.push({ red_st, blue_st, 0 });

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.cnt == 10)
			continue;

		for (int i = 0; i < 4; i++)
		{
			Info next = now; // 다음 큐에 넣을 정보
			int possible_flag = 1; // 이 경우를 큐에 넣어도 되는가에 대한 플래그
			int answer_flag = 0; // 정답을 구한 경우 1

			while (1) // 구슬을 가능할 때 까지 움직여 본다.
			{
				coordi blue_move, red_move;
				red_move = next.red + dir[i];
				blue_move = next.blue + dir[i];

				if (MAT[blue_move.y][blue_move.x] == HOLE) // 이러면 큐에 추가 하지 않는다.
				{
					possible_flag = 0;
					answer_flag = 0; // 이경우는 정답이 안됨으로 다시 0으로
					break;
				}
				if (MAT[red_move.y][red_move.x] == HOLE) // 가장 횟수가 작은 답 찾음
				{
					answer_flag = 1;
				}

				if (MAT[red_move.y][red_move.x] == WALL) // 해당 좌표가 벽이면 전값으로 바꾼다.
					red_move = next.red;

				if (MAT[blue_move.y][blue_move.x] == WALL)
					blue_move = next.blue;


				if (red_move == blue_move) // 빨간 공과 파란공이 겹치면 갱신 X 탈출
					break;

				if (red_move == next.red &&
					blue_move == next.blue) // 전값과 달라진게 없다면 갱신 X 탈출
					break;


				next.blue = blue_move; // 갱신
				next.red = red_move;

			}
			next.cnt++;

			if (answer_flag)
				return next.cnt;
			if (possible_flag)
				q.push(next);

		}
	}

	return -1;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	input();

	cout << bfs();

	return 0;
}