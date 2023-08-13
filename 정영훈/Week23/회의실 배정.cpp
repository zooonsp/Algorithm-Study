// 그리디
// 2808KB, 24ms
#include <bits/stdc++.h>

using namespace std;

struct Info {
	int s, f;
	Info(int s, int f) : s(s), f(f) {}
	Info() = default;
	bool operator<(const Info& other) const {
		if (f == other.f) return s < other.s; // 추가해야 함..
		return f < other.f;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<Info> infos(N);
	for (Info& in : infos) cin >> in.s >> in.f;
	sort(begin(infos), end(infos));

	int answer{1}, lastFinish = infos[0].f;
	for (int i = 1; i < N; ++i) {
		if (lastFinish <= infos[i].s) {
			lastFinish = infos[i].f;
			++answer;
		}
	}
	cout << answer << '\n';
	return 0;
}