/*
N : 1 ~ 1000, M : 1 ~ 1000
백준이가 책을 줄 수 있는 최대 학생 수를 구하시오.
Greedy
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	int T;
	cin >> T;
	while (T--) {
		int N, M;
		cin >> N >> M;
		vector<pair<int, int>> wants(M, { 0,0 });
		for (pair<int, int>& p : wants) {
			cin >> p.first >> p.second;
			p.first--, p.second--;
		}

		sort(begin(wants), end(wants), [](const pair<int, int>& p1, const pair<int, int>&p2) {
			return p1.second < p2.second;
		});

		vector<int> bookChk(N, 0);
		int answer = 0;
		for (pair<int, int>& p : wants) {
			for (int i = p.first; i <= p.second; ++i) {
				if (!bookChk[i]) {
					bookChk[i] = 1;
					++answer;
					break;
				}
			}
		}
		cout << answer << '\n';

	}

	return 0;
}