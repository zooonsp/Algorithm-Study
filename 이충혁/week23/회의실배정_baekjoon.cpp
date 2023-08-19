#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> ii;

vector<ii> v;

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N;
	int time = -1; // 0부터 시작하는 회의가 있으니 조심하자
	int ans = 0;

	cin >> N;

	v.resize(N);

	for (int i = 0; i < N; i++)
	{
		int st, ed;
		cin >> st >> ed;

		v[i] = { st, ed };
	}

	sort(v.begin(), v.end(),
		[](ii a, ii b)
		{
			if (a.second == b.second)
				return a.first < b.first;
			else
				return a.second < b.second;

			return false;
		});

	
	for (auto& val : v)
	{
		if (val.first >= time)
		{
			ans++;
			time = val.second;
		}
	}

	cout << ans << "\n";

	return 0;
}