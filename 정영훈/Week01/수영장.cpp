#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

// 각 이용권의 요금과 각 달의 이용 계획이 입력으로 주어질 때
// 가장 적은 비용 구하기.

int one, month, threeMonth, year; // 이용권 가격
int visited[12]{}; // 각 달에 뭘 샀는지
int willUse[12]{}; // 입력받을 매달 예상이용량
int ans{};

// 3^12 = 531,441
void dfs(int now,int sum) {
	if (sum > ans) return; // 한다면 가지치기? 이거 한 줄이 1872ms -> 25ms

	if (now == 12) {
		ans = min(ans, sum);
		return;
	}
	

	if (!willUse[now]) { // 사용량이 없는 달
		dfs(now + 1, sum);
	}
	if (visited[now]) { // 3달 사용권인 경우
		dfs(now + 1, sum);
	}

	// now달에는 하루 이용권으로~
	dfs(now+ 1, sum + one * willUse[now]);

	// now달에는 1달 이용권으로~
	dfs(now + 1, sum + month);

	// now달에는 3달 이용권으로 now+1, now+2까지
	if (now < 11) {
		visited[now] = visited[now + 1] = visited[now + 2] = 1;
		dfs(now + 1, sum + threeMonth);
		visited[now] = visited[now + 1] = visited[now + 2] = 0;
	}

}

int main()
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int days{};
		cin >> one >> month >> threeMonth >> year;
		for (int& i : willUse) {
			cin >> i;
			days += i;
		}
		// 1년 이용권
		ans = year;
		// 다 1일 이용권으로
		ans = min(ans, days * one);

		dfs(0, 0);
		
		cout << "#" << test_case << " " << ans << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}