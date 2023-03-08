#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N; // 나무 수

int FromDay(vector<int>& DAT, int day) {
	while (1) {
		bool chk = false;
		for (int index = 1; index < DAT.size(); ++index) {
			if (DAT[index] != 0) {
				chk = true; // 물을 줄수 있든 없든 남아있기 때문에
				if (day % 2) { // 홀수
					if (index >= 1) { // 높이가 1보다 클 때(없어도 되긴 함)
						DAT[index]--;
						DAT[index - 1]++; // 뿌린만큼 깎아서 값 추가
						break;
					}
				}
				else { // 짝수
					if (index >= 2) { // 높이가 2보다 클 때
						DAT[index]--;
						DAT[index - 2]++; // 뿌린만큼 깎아서 값 추가
						break;
					}
				}
			}
		}
		if (!chk) break;
		++day; // 다음 날
	}
	return day - 1; // 마지막 날에 물을 안 뿌리기 때문에 day - 1 리턴
}

int main() {
	int T{};
	cin >> T;

	for (int tc{ 1 }; tc <= T; ++tc) {
		// reset
		// input
		cin >> N;
		vector<int> trees(N, 0);
		int maxHeight{ -1 };
		for (int& t : trees) {
			cin >> t;
			maxHeight = max(maxHeight, t);
		}
		vector<int> DAT(maxHeight); // index : 높이차이, value : 개수
		for (int& t : trees) DAT[maxHeight - t]++;
		vector<int> copyDAT(begin(DAT), end(DAT)); // copy
		// solve
		int ans1 = FromDay(copyDAT, 1); // 1일차 물뿌리개를 사용
		int ans2 = FromDay(DAT, 2); // 1일차 물뿌리개를 사용하지 않음.
		
		// output
		cout << "#" << tc << ' ' << min(ans1, ans2) << endl;
	}
	return 0;
}