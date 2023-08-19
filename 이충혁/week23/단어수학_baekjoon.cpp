#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

map<char, int> alphabet;

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int N; // 단어의 갯수
	string input_str;
	int num = 9;
	int ans = 0;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> input_str;

		for(int j = 0; j < input_str.size(); j++)
		{
			if (alphabet.find(input_str[j]) == alphabet.end())
			{
				alphabet.insert({ input_str[j], pow(10, input_str.size() - j - 1) });
			}
			else
			{
				alphabet[input_str[j]] += pow(10, input_str.size() - j - 1);
			}

		}
	}


	vector < pair<char, int>> v(alphabet.begin(), alphabet.end());

	sort(v.begin(), v.end(),
		[](pair<char, int> a, pair<char, int> b)
		{
			return a.second > b.second;
		});

	for (auto& val : v)
	{
		ans += val.second * num;
		num--;
	}

	cout << ans << "\n";

	return 0;
}