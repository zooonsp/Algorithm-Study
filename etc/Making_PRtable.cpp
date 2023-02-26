/*    PR table 만들기 - By 영훈    */

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

// https://en.cppreference.com/w/cpp/numeric/random/random_device
// https://en.cppreference.com/w/cpp/algorithm/next_permutation
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

/*
1 : 이충혁
2 : 김용우
3 : 이재홍
4 : 정영훈
5 : 탁성건
*/

using std::vector;
using std::cout;
using std::endl;

int main() {
	vector<vector<int>> result;
	vector<int> vec{ 1, 2, 3, 4, 5 };
	do {
		result.push_back(vec);
	} while (std::next_permutation(begin(vec), end(vec)));

	cout << result.size() << '\n'; // 120

	/*for (auto& row : result) {
	for (int& i : row) {
	cout << i << ' ';
	}
	cout << endl;
	}*/

	std::random_device seed;
	std::uniform_int_distribution<int> UintD(0, 119); // [0, 119]
	int index = UintD(seed);

	for (int& i : result[index]) cout << i << ' ';

	cout << "\n";

	return 0;
}