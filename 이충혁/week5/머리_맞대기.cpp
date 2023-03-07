#include<iostream>
#include<vector>
using namespace std;

int N, T; // N : 사람 수, T : 팀 갯수
vector<int> person; // 사람 정보 저장
vector<int> prefix_sum; // 사람 수 누적합

int mx = 0;

int input()
{
	int sum = 0;
	prefix_sum.push_back(0); // 누적합으로 자를 때 index: 0 이 0 이어야 편리

	cin >> N >> T;
	for (int i = 0; i < N; i++)
	{
		int temp;
		cin >> temp;
		person.push_back(temp);
		sum += temp;
		prefix_sum.push_back(sum); // 누적 합 저장

		if (mx < temp)
			mx = temp;
	}
	return 0;
}


// 이번 mid값 이하로 나누는게 가능한지 확인
int possible_func(int mid)
{
	int sub_num; // 누적합 기준 ( 그룹을 자르는 기준으로 팀이 카운팅 될 때 같이 갱신됨 )
	int team_cnt;

	for (int i = 0; i <= N; i++) // 시작 지점 바꾸기
	{
		if (prefix_sum[i] > mid) // 시작 지점 이전의 값은 무조건 한덩이로 묶임, mid 보다 크면 끝
			break;

		team_cnt = 1;
		sub_num = prefix_sum[i];

		for (int j = i + 1; j <= N; j++)
		{
			if (prefix_sum[j] - sub_num > mid) // 현재 더한 부분이 최대값 보다 크면
			{
				sub_num = prefix_sum[j - 1]; // 이전 값을 기준으로 갱신
				team_cnt++;
			}
		}
		if (prefix_sum[i] + prefix_sum[N] - sub_num > mid) // 마지막 기준 의 우측과 시작지점은 한덩이라 mid보다 크면 건너 뜀
			continue;

		if (team_cnt <= T)
			return 1;
	}
	return 0;
}


int solve_func()
{
	int left = mx; // 하나의 원소 보다 같거나 커야 함
	int right = prefix_sum[N - 1]; // 원소의 총합 보다 크면 안됨
	int ans;

	while (left <= right)
	{
		int mid = (left + right) / 2; 

		if (possible_func(mid))
		{
			ans = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	cout << ans;
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	input();
	solve_func();
	return 0;
}