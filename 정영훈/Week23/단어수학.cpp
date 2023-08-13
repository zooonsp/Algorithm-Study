// 10! 해도 널널하다고 생각해서..
// 2024KB, 456ms
#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N;
	cin >> N; // 단어의 수

	vector<int> DAT(26, 0);
	vector<char> chars;
	int cnt{};
	vector<string> strs(N);
	for (auto& str : strs) {
		cin >> str;
		for (auto& c : str) {
			if (DAT[c - 'A'] == 0) {
				DAT[c - 'A'] = 1;
				cnt++;
				chars.push_back(c);
			}
		}
	}

	vector<int> permutationVector;
	for (int  i = 10 - cnt; i < 10 ; ++i) {
		permutationVector.push_back(i);
	}

	int answer{};
	do {
		vector<int> charToInt(26, 0);
		int index{};
		for (auto& c : chars) {
			charToInt[c - 'A'] = permutationVector[index++];
		}
		int sum{};
		for (auto& str : strs) {
			int num{};
			for (auto& c : str) {
				num *= 10;
				num += charToInt[c - 'A'];
			}
			sum += num;
		}
		answer = max(answer, sum);
	} while (next_permutation(begin(permutationVector), end(permutationVector)));

	cout << answer << '\n';
	return 0;
}