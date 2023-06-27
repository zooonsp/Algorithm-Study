/*    PR table 만들기 - By 영훈    */

/*
1 : 김용우
2 : 박준섭
3 : 이재홍
4 : 이충혁
5 : 정영훈
6 : 탁성건
*/

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <ranges> // cpp20

// https://en.cppreference.com/w/cpp/numeric/random/random_device
// https://en.cppreference.com/w/cpp/algorithm/next_permutation
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
// https://en.cppreference.com/w/cpp/ranges

using std::vector; // vector
using std::cout; // iostream
using std::endl; // iostream
using std::string; // string
using std::next_permutation; // algorithm
using std::random_device; // random
using std::uniform_int_distribution; // random
using std::views::iota; // ranges
using std::views::take; // ranges
using std::views::transform; // ranges

template<typename T>
void Print(T& container) {
	for (auto& value : container) {
		cout << value << ' ';
	}
	cout << '\n';
}

int main() {
	vector<string> indexToName{ "", "김용우", "박준섭", "이재홍", "이충혁", "정영훈", "탁성건"};
	int N{ static_cast<int>(indexToName.size()) - 1 }; // 6
	vector<vector<int>> result;

	// vector<int> vec{ 1, 2, 3, 4, 5, 6 };
	vector<int> vec;
	for (int i : iota(1) | take(N)) vec.push_back(i);
	// lazy evaluation(iota) => take를 통해 정해진 개수(N)만큼 넣기.

	// Print<vector<int>>(vec); - 명시적으로 지정 가능
	// Print(vec);

	do {
		result.push_back(vec);
	} while (next_permutation(begin(vec), end(vec)));
	// cout << result.size() << '\n'; // peoples! 개 만큼 결과 나옴.

	// Print(result.back()); // 마지막 꺼만 출력해보자

	random_device seed;
	uniform_int_distribution<int> UintD(0, static_cast<int>(result.size() - 1)); // [0, result.size() - 1]
	int index = UintD(seed);

	// 기존에 숫자로 결과 뽑던 코드(deprecated)
	// for (int& i : result[index]) cout << i << ' ';

	// 바로 이름으로 (by lambda)
	auto func = [&indexToName](const int& i) -> string { return indexToName[i]; };
	vector<string> resultName;
	for (auto i : result[index] | transform(func)) resultName.emplace_back(i);
	Print(resultName);

	/*
	// 10번 반복해보기
	for (int i : iota(0) | take(10)) {
		int idx = UintD(seed);
		vector<string> resultNameRep;
		for (auto i : result[idx] | std::views::transform(func)) resultNameRep.emplace_back(i);
		Print(resultNameRep);
	}
	*/

	return 0;
}
