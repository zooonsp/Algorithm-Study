#include<iostream>
#include<string>
#include<cstring>
using namespace std;

enum COLOR {
	WHITE = 0,
	YELLOW = 1,
	RED = 2,
	ORANGE = 3,
	GREEN = 4,
	BLUE = 5
};

enum DIR {
	U = 0,
	D = 1,
	F = 2,
	B = 3,
	L = 4,
	R = 5
};

enum CLOCK_WISE {
	REVERSE = 0,
	NORMAL = 1
};




int N; // 몇번 돌리는지
int cube[6][3][3]; // 방향은 enum 순서 대로


int init()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cube[i][j][k] = i;
			}
		}
	}

	return 0;
}

int copy_cube[3][3];
// 돌아가는 면에 있는 부분 돌리기
void normal(int dir)
{
	memcpy(copy_cube, cube[dir], sizeof(copy_cube));

	cube[dir][0][0] = copy_cube[2][0];
	cube[dir][0][1] = copy_cube[1][0];
	cube[dir][0][2] = copy_cube[0][0];
	cube[dir][1][2] = copy_cube[0][1];
	cube[dir][2][2] = copy_cube[0][2];
	cube[dir][2][1] = copy_cube[1][2];
	cube[dir][2][0] = copy_cube[2][2];
	cube[dir][1][0] = copy_cube[2][1];

	return;
}

void reverse(int dir)
{
	memcpy(copy_cube, cube[dir], sizeof(copy_cube));

	cube[dir][0][0] = copy_cube[0][2];
	cube[dir][0][1] = copy_cube[1][2];
	cube[dir][0][2] = copy_cube[2][2];
	cube[dir][1][2] = copy_cube[2][1];
	cube[dir][2][2] = copy_cube[2][0];
	cube[dir][2][1] = copy_cube[1][0];
	cube[dir][2][0] = copy_cube[0][0];
	cube[dir][1][0] = copy_cube[0][1];

	return;
}

// 모든 돌리는 함수는 돌릴때 돌아가는 옆면 돌리기 를 수행한다.
int temp[3]; // swap할 때 쓸 temp
// temp를 받을 면 기준 순차적으로 넣어준다.
void U_normal()
{
	temp[0] = cube[F][0][0];
	temp[1] = cube[F][0][1];
	temp[2] = cube[F][0][2];

	cube[F][0][0] = cube[R][0][0];
	cube[F][0][1] = cube[R][0][1];
	cube[F][0][2] = cube[R][0][2];


	cube[R][0][0] = cube[B][0][0];
	cube[R][0][1] = cube[B][0][1];
	cube[R][0][2] = cube[B][0][2];


	cube[B][0][0] = cube[L][0][0];
	cube[B][0][1] = cube[L][0][1];
	cube[B][0][2] = cube[L][0][2];


	cube[L][0][0] = temp[0];
	cube[L][0][1] = temp[1];
	cube[L][0][2] = temp[2];

	return;
}

void U_reverse()
{
	temp[0] = cube[F][0][0];
	temp[1] = cube[F][0][1];
	temp[2] = cube[F][0][2];

	cube[F][0][0] = cube[L][0][0];
	cube[F][0][1] = cube[L][0][1];
	cube[F][0][2] = cube[L][0][2];


	cube[L][0][0] = cube[B][0][0];
	cube[L][0][1] = cube[B][0][1];
	cube[L][0][2] = cube[B][0][2];


	cube[B][0][0] = cube[R][0][0];
	cube[B][0][1] = cube[R][0][1];
	cube[B][0][2] = cube[R][0][2];


	cube[R][0][0] = temp[0];
	cube[R][0][1] = temp[1];
	cube[R][0][2] = temp[2];

	return;
}

void D_normal()
{
	temp[0] = cube[F][2][0];
	temp[1] = cube[F][2][1];
	temp[2] = cube[F][2][2];

	cube[F][2][0] = cube[L][2][0];
	cube[F][2][1] = cube[L][2][1];
	cube[F][2][2] = cube[L][2][2];


	cube[L][2][0] = cube[B][2][0];
	cube[L][2][1] = cube[B][2][1];
	cube[L][2][2] = cube[B][2][2];


	cube[B][2][0] = cube[R][2][0];
	cube[B][2][1] = cube[R][2][1];
	cube[B][2][2] = cube[R][2][2];


	cube[R][2][0] = temp[0];
	cube[R][2][1] = temp[1];
	cube[R][2][2] = temp[2];

	return;
}

void D_reverse()
{
	temp[0] = cube[F][2][0];
	temp[1] = cube[F][2][1];
	temp[2] = cube[F][2][2];

	cube[F][2][0] = cube[R][2][0];
	cube[F][2][1] = cube[R][2][1];
	cube[F][2][2] = cube[R][2][2];


	cube[R][2][0] = cube[B][2][0];
	cube[R][2][1] = cube[B][2][1];
	cube[R][2][2] = cube[B][2][2];


	cube[B][2][0] = cube[L][2][0];
	cube[B][2][1] = cube[L][2][1];
	cube[B][2][2] = cube[L][2][2];


	cube[L][2][0] = temp[0];
	cube[L][2][1] = temp[1];
	cube[L][2][2] = temp[2];

	return;
}

void F_normal()
{
	temp[0] = cube[D][0][0];
	temp[1] = cube[D][0][1];
	temp[2] = cube[D][0][2];

	cube[D][0][0] = cube[R][2][0];
	cube[D][0][1] = cube[R][1][0];
	cube[D][0][2] = cube[R][0][0];


	cube[R][0][0] = cube[U][2][0];
	cube[R][1][0] = cube[U][2][1];
	cube[R][2][0] = cube[U][2][2];


	cube[U][2][0] = cube[L][2][2];
	cube[U][2][1] = cube[L][1][2];
	cube[U][2][2] = cube[L][0][2];


	cube[L][0][2] = temp[0];
	cube[L][1][2] = temp[1];
	cube[L][2][2] = temp[2];

	return;
}

void F_reverse()
{
	temp[0] = cube[D][0][2];
	temp[1] = cube[D][0][1];
	temp[2] = cube[D][0][0];

	cube[D][0][0] = cube[L][0][2];
	cube[D][0][1] = cube[L][1][2];
	cube[D][0][2] = cube[L][2][2];


	cube[L][0][2] = cube[U][2][2];
	cube[L][1][2] = cube[U][2][1];
	cube[L][2][2] = cube[U][2][0];


	cube[U][2][0] = cube[R][0][0];
	cube[U][2][1] = cube[R][1][0];
	cube[U][2][2] = cube[R][2][0];


	cube[R][0][0] = temp[0];
	cube[R][1][0] = temp[1];
	cube[R][2][0] = temp[2];

	return;
}

void B_normal()
{
	temp[0] = cube[D][2][2];
	temp[1] = cube[D][2][1];
	temp[2] = cube[D][2][0];

	cube[D][2][2] = cube[L][2][0];
	cube[D][2][1] = cube[L][1][0];
	cube[D][2][0] = cube[L][0][0];


	cube[L][0][0] = cube[U][0][2];
	cube[L][1][0] = cube[U][0][1];
	cube[L][2][0] = cube[U][0][0];


	cube[U][0][2] = cube[R][2][2];
	cube[U][0][1] = cube[R][1][2];
	cube[U][0][0] = cube[R][0][2];


	cube[R][0][2] = temp[0];
	cube[R][1][2] = temp[1];
	cube[R][2][2] = temp[2];

	return;
}

void B_reverse()
{
	temp[0] = cube[D][2][0];
	temp[1] = cube[D][2][1];
	temp[2] = cube[D][2][2];

	cube[D][2][2] = cube[R][0][2];
	cube[D][2][1] = cube[R][1][2];
	cube[D][2][0] = cube[R][2][2];


	cube[R][0][2] = cube[U][0][0];
	cube[R][1][2] = cube[U][0][1];
	cube[R][2][2] = cube[U][0][2];


	cube[U][0][2] = cube[L][0][0];
	cube[U][0][1] = cube[L][1][0];
	cube[U][0][0] = cube[L][2][0];


	cube[L][0][0] = temp[0];
	cube[L][1][0] = temp[1];
	cube[L][2][0] = temp[2];

	return;
}

void L_normal()
{
	temp[0] = cube[D][2][0];
	temp[1] = cube[D][1][0];
	temp[2] = cube[D][0][0];

	cube[D][2][0] = cube[F][2][0];
	cube[D][1][0] = cube[F][1][0];
	cube[D][0][0] = cube[F][0][0];


	cube[F][0][0] = cube[U][0][0];
	cube[F][1][0] = cube[U][1][0];
	cube[F][2][0] = cube[U][2][0];


	cube[U][0][0] = cube[B][2][2];
	cube[U][1][0] = cube[B][1][2];
	cube[U][2][0] = cube[B][0][2];


	cube[B][0][2] = temp[0];
	cube[B][1][2] = temp[1];
	cube[B][2][2] = temp[2];

	return;
}

void L_reverse()
{
	temp[0] = cube[D][0][0];
	temp[1] = cube[D][1][0];
	temp[2] = cube[D][2][0];

	cube[D][2][0] = cube[B][0][2];
	cube[D][1][0] = cube[B][1][2];
	cube[D][0][0] = cube[B][2][2];


	cube[B][0][2] = cube[U][2][0];
	cube[B][1][2] = cube[U][1][0];
	cube[B][2][2] = cube[U][0][0];


	cube[U][0][0] = cube[F][0][0];
	cube[U][1][0] = cube[F][1][0];
	cube[U][2][0] = cube[F][2][0];


	cube[F][0][0] = temp[0];
	cube[F][1][0] = temp[1];
	cube[F][2][0] = temp[2];

	return;
}

void R_normal()
{
	temp[0] = cube[D][0][2];
	temp[1] = cube[D][1][2];
	temp[2] = cube[D][2][2];

	cube[D][0][2] = cube[B][2][0];
	cube[D][1][2] = cube[B][1][0];
	cube[D][2][2] = cube[B][0][0];


	cube[B][0][0] = cube[U][2][2];
	cube[B][1][0] = cube[U][1][2];
	cube[B][2][0] = cube[U][0][2];


	cube[U][2][2] = cube[F][2][2];
	cube[U][1][2] = cube[F][1][2];
	cube[U][0][2] = cube[F][0][2];


	cube[F][0][2] = temp[0];
	cube[F][1][2] = temp[1];
	cube[F][2][2] = temp[2];

	return;
}

void R_reverse()
{
	temp[0] = cube[D][2][2];
	temp[1] = cube[D][1][2];
	temp[2] = cube[D][0][2];

	cube[D][0][2] = cube[F][0][2];
	cube[D][1][2] = cube[F][1][2];
	cube[D][2][2] = cube[F][2][2];


	cube[F][0][2] = cube[U][0][2];
	cube[F][1][2] = cube[U][1][2];
	cube[F][2][2] = cube[U][2][2];


	cube[U][2][2] = cube[B][0][0];
	cube[U][1][2] = cube[B][1][0];
	cube[U][0][2] = cube[B][2][0];


	cube[B][0][0] = temp[0];
	cube[B][1][0] = temp[1];
	cube[B][2][0] = temp[2];

	return;
}



string cmd; // 큐브 어떻게 돌릴지 명령어 문자열
int cmd_dir;
int cmd_clockwise;
int solve_func()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> cmd;
		
		if (cmd[1] == '+')
			cmd_clockwise = NORMAL;
		else
			cmd_clockwise = REVERSE;

		switch (cmd[0])
		{
		case 'U':
			cmd_dir = U;
			if (cmd_clockwise)
			{
				U_normal();
			}
			else
			{
				U_reverse();
			}
			break;
		case 'D':
			cmd_dir = D;
			if (cmd_clockwise)
			{
				D_normal();
			}
			else
			{
				D_reverse();
			}
			break;
		case 'F':
			cmd_dir = F;
			if (cmd_clockwise)
			{
				F_normal();
			}
			else
			{
				F_reverse();
			}
			break;
		case 'B':
			cmd_dir = B;
			if (cmd_clockwise)
			{
				B_normal();
			}
			else
			{
				B_reverse();
			}
			break;
		case 'L':
			cmd_dir = L;
			if (cmd_clockwise)
			{
				L_normal();
			}
			else
			{
				L_reverse();
			}
			break;
		case 'R':
			cmd_dir = R;
			if (cmd_clockwise)
			{
				R_normal();
			}
			else
			{
				R_reverse();
			}
		}

		if (cmd_clockwise)
		{
			normal(cmd_dir);
		}
		else
		{
			reverse(cmd_dir);
		}

	}

	// 답 출력
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (cube[0][i][j])
			{
			case WHITE:
				cout << 'w';
				break;
			case YELLOW:
				cout << 'y';
				break;
			case RED:
				cout << 'r';
				break;
			case ORANGE:
				cout << 'o';
				break;
			case GREEN:
				cout << 'g';
				break;
			case BLUE:
				cout << 'b';

			}
		}
		cout << "\n";
	}

	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		init();
		solve_func();
	}
	return 0;
}