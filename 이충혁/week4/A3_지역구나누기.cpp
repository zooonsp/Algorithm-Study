#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int MAX_MAT = 10; 
const int MAX = 21e8;

// union find로 푼다
// 1. 마을을 2개로 나눈다 (bitmasking 사용해서)
// 2. 2개로 나누었을 떄 union find해서 부모가 같은 지 확인 안같으면 그 경우의 수 는 그냥 지나친다.
// 3. union find 하면서 유권자 수를 부모에 합해줄 건데 두 부모의 유권자수 의 차이를 출력

int N; // 마을의 개수
int MAT[MAX_MAT][MAX_MAT]; // 마을 간선 정보
int town[MAX_MAT]; // 마을 유권자 수

int init()
{
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAT[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		cin >> town[i];
	}
	return 0;
}

int parent[2][MAX_MAT];
int pop[2][MAX_MAT];

int Find(int now , int group)
{
	if (now == parent[group][now])
		return now;

	return parent[group][now] = Find(parent[group][now], group);
}

int Union(int a, int b, int group)
{
	int pa = Find(a, group);
	int pb = Find(b, group);

	if (pa == pb) return 0;

	parent[group][pb] = pa;

	// 마을 끼리 합칠 때 pa 가 최종 부모기 때문에
	// pa 유권자수(pa)에 모두 합쳐 준다. 합치고 다른 하나는 0으로

	pop[group][pa] += pop[group][pb];
	pop[group][pb] = 0;

	return 0;
}

int Union_Find(int bit_val)
{
	int group_i, group_j;
	for (int i = 0; i < N; i++)
	{
		group_i = (bit_val >> i) % 2;
		for (int j = 0; j < N; j++)
		{
			if (MAT[i][j] == 0) continue; // 마을과 마을간의 edge 가 없으면 
			group_j = (bit_val >> j) % 2;
			if (group_i != group_j) continue; // 행과 열의 나눈 그룹이 다르면 

			Union(i, j, group_i);
		}
	}
	return 1;
}

int group_check(int bit_val)
{
	int before_index[2] = { -1, -1 }; // 이전 [그룹 (0 or 1)] 의 인덱스 
	for (int i = 0; i < N; i++)
	{
		int group = (bit_val >> i) % 2;
		if (before_index[group] == -1)
		{
			before_index[group] = i;
		}
		else
		{
			if (Find(i, group) != Find(before_index[group], group))
				return 0;
		}
	}

	return 1;
}

int pop_diff()
{
	int group_pop[2];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (pop[i][j] != 0)
			{
				group_pop[i] = pop[i][j];
				break;
			}
		}
	}

	return abs(group_pop[0] - group_pop[1]);
}

int solve_func()
{
	// 비트연산으로 마을을 두 그룹으로 나눔.
	int bit_val = 1; // 마을의 그룹을 의미하는 수, 0부터 시작하지 않는건 0은 모두 한 그룹이라서
	int bit_limit = 1; // bit_val <= 2 ^ N - 2 ( -1 더하는 이유 : 모두 1이면 한그룹)
	for (int i = 0; i < N; i++)
		bit_limit *= 2; 
	bit_limit = bit_limit - 2;

	int ans = MAX;
	
	for (bit_val; bit_val <= bit_limit; bit_val++) // 모든 그룹의 경우의 수를 돌아본다.
	{
		// union-find 초기화: parent, pop
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < N; j++)
			{
				parent[i][j] = j;
				int group = (bit_val >> j) % 2;
				if (group == i)
					pop[i][j] = town[j];
				else
					pop[i][j] = 0;
			}
		}
		
		Union_Find(bit_val); // 일단 그룹을 쪼개보고 그에 따라 유권자수도 합해줌

		// 두그룹으로 가르고 싶었지만 엣지가 없어서 초과해서 나누어졌는지 확인
		if (!group_check(bit_val)) continue;

		// 두그룹 최솟값 구함
		int temp = pop_diff();
		if (ans > temp)
			ans = temp;
	}

	return ans;
}

int main()
{
	//freopen("input.txt", "r", stdin);

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