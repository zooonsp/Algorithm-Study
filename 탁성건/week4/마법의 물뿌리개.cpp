#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;			 // 나무의 개수
int height[100]; // 나무의 높이
int maxHeight, ans;
int cnt[2]; // cnt[0]: 짝수 개수, cnt[1]: 홀수 개수

int main(void)
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{

		maxHeight = 0;
		ans = 0;
		memset(cnt, 0, sizeof(cnt));

		cin >> N;

		for (int i = 0; i < N; i++)
		{
			cin >> height[i];
			maxHeight = max(maxHeight, height[i]);
		}

		for (int i = 0; i < N; i++)
		{
			// 키가 가장 큰 나무와 같아지기 위해 필요한 길이 계산
			height[i] = maxHeight - height[i];

			// 짝수 개수
			cnt[0] += height[i] / 2;
			// 홀수 개수
			cnt[1] += height[i] % 2;
		}

		// 짝수 개수와 홀수 개수 중 최소값
		int minCnt = min(cnt[0], cnt[1]);
		// 홀수 번째 날에 1만큼, 짝수 번째 날에 2만큼 키울 수 있으니 minCnt*2 만큼 소요
		ans += minCnt * 2;

		// 남은 개수 계산
		for (int i = 0; i < 2; i++)
			cnt[i] -= minCnt;

		// 짝수 개수가 남은 경우
		// 필요한 길이 : cnt[0] * 2
		// #1. 필요한 길이를 3만큼 키울 수 있을 만큼 키우고 => cnt[0] * 2 / 3 * 2
		// #2. 남은 길이값 더해주기(0 or 1 or 2) => cnt[0] * 2 % 3
		if (cnt[0] != 0)
			ans += cnt[0] * 2 / 3 * 2 + cnt[0] * 2 % 3;
		// 홀수 개수가 남은 경우
		// 홀수 번째 날마다 물 주기
		else if (cnt[1] != 0)
			ans += cnt[1] * 2 - 1;

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}
