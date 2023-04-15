/*
1000000000000000
0011 | 1000 1101 | 0111 1110 | 1010 0100 | 1100 0110 | 1000 0000 | 0000 0000
해봤자 62개
*/

// 처음 의도(Divide And Conquer)
#include <string>
#include <vector>
#include <iostream>

using namespace std;
bool chk;

int dfs(long long& number, int start, int end) { // [start, end]
	if (!chk) return 0;
	int mid = start + (end - start) / 2;
	if (end == start) return number & (1LL << mid);

	if (!chk) return 0; // 더 갈 필요 없음.
	int leftHalf = dfs(number, start, mid - 1);
	if (!chk) return 0; // 더 갈 필요 없음.
	int rightHalf = dfs(number, mid + 1, end);

	if (number & (1LL << mid)) return 1; // 별 문제 없는 상황
	else if ((leftHalf || rightHalf) && !(number & (1LL << mid))) chk = false;
	return 0;
}

vector<int> solution(vector<long long> numbers) {
	vector<int> answer;
	for (long long& number : numbers) {
		chk = true;
		int treeHeight = 1;
		// 1 << nodeNumber 하면 int가 최대
		while ((1LL << ((1 << treeHeight) - 1)) - 1 < number) {
			++treeHeight;
		}
		// number를 2진수로 표현했을 때 길이 = ( 1 << treeHeight ) - 2
		// ex) 42 -> 0101010
		// treeHeight = 3, (1 << treeHeight) - 2 = 6

		// number, 2진수로 표현했을 때 시작 bit, 2진수로 표현했을 때 마지막 bit
		dfs(number, 0, (1 << treeHeight) - 2);

		if (chk) answer.push_back(1);
		else answer.push_back(0);
	}
	return answer;
}

int main() {
	// vector<long long> numbers{ 7, 42, 5 }; // 1 1 0
	vector<long long> numbers{ 63, 111, 95, 58 }; // 1 1 0 1
	// vector<long long> numbers{ 1000000000000000 };
	vector<int> answer = solution(numbers);
	for (int& i : answer) cout << i << ' ';
	return 0;
}