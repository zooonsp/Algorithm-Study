#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MAX = 21e8;
const int MAX_MAT = 15;
const int ry[] = { -1, 1, 0 , 0 };
const int rx[] = { 0, 0, -1, 1 };

struct Point {
	int y, x;
};

struct Ans_Info {
	int core_connect; // 연결된 코어
	int wire_length; // 전선 길이
};

// dfs
struct Path_Info {
	int MAT[MAX_MAT][MAX_MAT]; // 셀 정보 (입력)
	Ans_Info current; // 현재까지 연결된 코어수, 전선길이
};

int N; // 크기
vector <Point> core; // 코어의 좌표값 
int core_cnt; // 코어 갯수  DFS 기저조건으로 쓸거임 vector size() 
// 쓰는거랑 큰 차이가 없나?

Ans_Info ans;
// dfs path 인데 입력 좌표값도 여기 저장
Path_Info path;


int init()
{
	// path 정보 초기화 
	path = { {0,}, {0, 0} };

	ans = { 0, MAX };
	core.clear();
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> path.MAT[i][j];
			if (path.MAT[i][j] == 1)
				core.push_back({ i, j });
		}
	}

	core_cnt = core.size();

	return 0;
}

// 이 쪽 방향으로 연결이 가능한지
int possible_func(Point now,  int dir)
{
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		if (path.MAT[next.y][next.x] != 0)
			return 0; // 하나라도 뭐가 있다면 연결 안됨

		next.y += ry[dir];
		next.x += rx[dir];
	}

	return 1; // 모든 케이스 통과 연결 가능
}

// 연결 해주는 함수
int connect_func(Point now, int dir)
{
	int ret = 0; // 사용한 wire 값 반환
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		path.MAT[next.y][next.x] = 1;
		ret++;

		next.y += ry[dir];
		next.x += rx[dir];
	}
	return ret;
}

// 끊어 주는 함수
int sprt_func(Point now, int dir)
{
	Point next;
	next = now;
	next.y += ry[dir];
	next.x += rx[dir];

	while (next.y > 0 && next.y <= N &&
		next.x > 0 && next.x <= N)
	{
		path.MAT[next.y][next.x] = 0;
		next.y += ry[dir];
		next.x += rx[dir];
	}
	return 0;
}

int dfs(int level)
{
	if (level == core_cnt)
	{
		if (ans.core_connect < path.current.core_connect) // 코어가 더많이 연결되면 갱신
		{
			ans = path.current;
		}
		else if (ans.core_connect == path.current.core_connect &&
			ans.wire_length > path.current.wire_length) // 연결 코어 갯수가 같고 전선길이가 짧으면 갱신
		{
			ans = path.current;
		}

		return 0;
	}

	Point now = core[level]; // 현재 탐색하는 코어의 좌표
	
	// 가지치기 1.  1, N 이 y, x면 전선값 그대로 연결된 프로세서 갯수 + 1 하고 그대로 전달
	if (now.y == 1 || now.y == N ||
		now.x == 1 || now.x == N)
	{
		path.current.core_connect += 1;
		dfs(level + 1);
		path.current.core_connect -= 1;

		return 0;
	}

	// 가지치기 2.  N-1 이 y, x면 "연결할 곳에 프로세서가 있는지 확인 후" 전선값 + 1 연결된 프로세서 갯수  + 1 하고
	// MAP 정보 갱신후 전달. MAT 에 정보를 추가하지 않는건 1 부분의 전선은 나머지 코어에 영향이 없기 때문이다.
	if (now.y == 2 || now.y == N - 1 ||
		now.x == 2 || now.x == N - 1)
	{
		int possible_flag = 0; // 연결할 곳에 프로세스가 없으면 flag -> 1
		if (now.y == 2)
		{
			if (path.MAT[1][now.x] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.y == N - 1)
		{
			if (path.MAT[N][now.x] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.x == 2)
		{
			if (path.MAT[now.y][1] == 0)
			{
				possible_flag = 1;
			}
		}
		if (now.x == N - 1)
		{
			if (path.MAT[now.y][N] == 0)
			{
				possible_flag = 1;
			}
		}

		if (possible_flag) // 가능하면 다음으로 넘어감
		{
			path.current.core_connect += 1;
			path.current.wire_length += 1;
			dfs(level + 1);
			path.current.core_connect -= 1;
			path.current.wire_length -= 1;

			return 0;
		}
	}

	dfs(level + 1);

	for (int dir = 0; dir < 4; dir++)
	{
		if (!possible_func(now, dir)) continue;
		
		int temp = connect_func(now, dir);
		path.current.core_connect += 1;
		path.current.wire_length += temp;
		dfs(level + 1);
		path.current.core_connect -= 1;
		path.current.wire_length -= temp;

		sprt_func(now, dir);
	}

	return 0;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		dfs(0);

		cout << "#" << test_case << " " << ans.wire_length << "\n";
	}
	return 0;
}