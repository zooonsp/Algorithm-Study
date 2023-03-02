#include<iostream>
#include<cstring>
using namespace std;
const int MAX = 110;

// 이진 탐색으로 찾을 건데
// 1. 최대 높이는 최대 일수 이상이다. 따라서 right
// 2. 최저 일수 는 한번 물을 줘야하는 나무의 갯수 

int N; // 나무의 개수 
int tree[MAX]; // 나무 사이즈
int max_height = 0;

int init()
{
	memset(tree, 0, sizeof(tree));
	max_height = 0;
	return 0;
}

int input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> tree[i];
		if (max_height < tree[i])
			max_height = tree[i];
	}


	return 0;
}

int solve_func()
{
	int need_height = 0; // 나무가 자라야할 높이 합
	int limit_day = 0; // 한개만 있는 나무 만큼 홀수 일 에 물 줘야함.

	for (int i = 0; i < N; i++)
	{
		need_height += max_height - tree[i]; // 최대 나무높이에서 모든 나무의 값을 빼서 더함
		if ((max_height - tree[i]) % 2 == 1) // 한개의 높이를 갖는 나무를 찾아서
			limit_day += 2; // 그나무를 위해 필요한 제한 일수에 +2 씩
	}

	if (limit_day > 0)
		limit_day--; // 짝수 일이라 하루 빼줘야함.

	// 이진 탐색

	int left = limit_day;
	int right = need_height;

	int ans = left;

	while (left <= right)
	{
		int mid = (left + right) / 2;

		if (mid + mid / 2 >= need_height) // 최대한 줄 수 있는 물의 양이 자라야할 높이보다 같거나 높으면
		{
			ans = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
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