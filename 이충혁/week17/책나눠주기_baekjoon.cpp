#include<iostream>
#include<queue>
using namespace std;

struct Info_book {
	int from, to;

	bool operator < (Info_book next) const
	{
		if (to > next.to)
			return true;

		if (from > next.to)
			return true;

		return false;
	}
};

const int MAX_NUM = 1010;

int N, M; // N: 책의 갯수, M: 학생수


int solve_func()
{
	int ans = 0;
	priority_queue<Info_book> pq;
	int visited[MAX_NUM] = { 0, };

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		pq.push({ from, to });
	}

	while (!pq.empty())
	{
		Info_book now = pq.top();
		pq.pop();

		for (int i = now.from; i <= now.to; i++)
		{
			if (visited[i] == 0)
			{
				ans++;
				visited[i] = 1;
				break;
			}
		}
	}

	cout << ans << "\n";
	return 0;
}


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int T;

	cin >> T;

	for (int i = 0; i < T; i++)
	{
		solve_func();
	}
	return 0;
}