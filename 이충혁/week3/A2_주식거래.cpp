#include<iostream>
#include<cstring>
using namespace std;
const int MAX_MAP = 20;

// 1. 수익이 나는 주식만 산다.
// 2. 수익이 나는 주식중 dfs로 뭘 얼마나 살지 결정
// 3. 한개월의 수익은 모두 매도 되어 다음 개월에 영향 없음 ( 가진 보유금은 달라짐 )


int Ms, Ma; // 첫 시드액(Ms), 월별 투자 금액(Ma)
int N, L; // 종목수(N), 과거 데이터 기간(L)
int MAP[MAX_MAP][MAX_MAP];  // 기간별 주식 종목 가격 [종목][월별]


int init()
{
	memset(MAP, 0, sizeof(MAP));
	return 0;
}

int input()
{
	cin >> Ms >> Ma;
	cin >> N >> L;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < L + 1; j++) // 0개월도 받음
			cin >> MAP[i][j];

	return 0;
}

int stock_check[MAX_MAP]; // 다음달에 수입이 나는 주식만 1, 나머지 0

int use_money[MAX_MAP]; // dfs 돌리면서 현재까지 쓴 돈
int seed_money; // 달별로 증가 되는 시드액 (주식으로 버는거 + 월별 투자금)
int next_money[MAX_MAP]; // dfs에서 전달되는 다음달 수입의 합
int max_money; // dfs 에서 최대 값 ( 다음달 최대 수입금 )

int dfs(int level, int m) // level: 종목 index, m: 월, 
{
	// 기저 조건: 모든 종목을 거쳤다면
	if (level == N)
	{
		int temp = seed_money - use_money[level] + next_money[level]; // 남은돈 + 다음달에 벌 수입
		if (max_money < temp)
			max_money = temp;
		return 0;
	}

	// 가지 치기: 수입이 안생길 종목이면 다음 재귀 호출
	if (!stock_check[level])
	{
		use_money[level + 1] = use_money[level]; //
		next_money[level + 1] = next_money[level];
		dfs(level + 1, m);
		return 0;
	}
	//  누적된 주식 가격(use_money)이 seed)money를 넘지 않는 선에서
	// level 종목 주식을 살수 있는 만큼 반복하여 재귀호출
	for (int i = 0;; i++)
	{
		use_money[level + 1] = use_money[level] + MAP[level][m] * i;
		if (use_money[level + 1] > seed_money)
			break;

		next_money[level + 1] = next_money[level] + MAP[level][m + 1] * i;
		dfs(level + 1, m);
	}


	return 0;
}

int solve_func()
{
	seed_money = Ms;
	for (int m = 0; m < L; m++) // 월 순으로 돌림
	{
		// dfs 전 초기화
		max_money = 0;
		memset(next_money, 0, sizeof(next_money));
		memset(use_money, 0, sizeof(use_money));
		memset(stock_check, 0, sizeof(stock_check));

		// 수입 있는 주식만 체크
		for (int i = 0; i < N; i++)
		{
			if (MAP[i][m] < MAP[i][m + 1])
				stock_check[i] = 1;
		}


		dfs(0, m);
		seed_money = max_money;
		seed_money += Ma; // 다음달 투자금 미리 더해줌
	}

	int ans = seed_money - Ms - Ma * L;
	return ans;
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
