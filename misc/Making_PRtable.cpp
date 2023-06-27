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
#include <random> // random_device, uniform_int_distribution
#include <vector>
#include <algorithm> // next_permutation
#include <string>
#include <chrono>
#include <sstream>
#include <ranges> // iota, take, transform (cpp20 ~)

// https://en.cppreference.com/w/cpp/numeric/random/random_device
// https://en.cppreference.com/w/cpp/algorithm/next_permutation
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
// https://en.cppreference.com/w/cpp/ranges
// https://en.cppreference.com/w/cpp/header/chrono
// https://en.cppreference.com/w/cpp/chrono/zoned_time

using std::vector; // vector
using std::cout; // iostream
using std::string; // string
using namespace std::chrono;

template<typename T>
void Print(T& container) {
	for (auto& value : container) {
		cout << value << ' ';
	}
	cout << '\n';
}

string GetToday() {
	/*
	cout << "UTC Time\n";
	// auto utcTime = std::chrono::system_clock::now();
	system_clock::time_point utcTime = system_clock::now();
	cout << utcTime << '\n';
	*/

	// https://kukuta.tistory.com/410
	// https://en.cppreference.com/w/cpp/chrono/zoned_time
	// local_time<system_clock::duration> localTime = zoned_time("Asia/Tokyo", system_clock::now()).get_local_time();
	local_time<system_clock::duration> localTime = zoned_time(current_zone(), system_clock::now()).get_local_time();
	// cout << localTime << '\n';
	// cout << floor<days>(localTime) << '\n';

	std::ostringstream oss;
	oss << floor<days>(localTime);
	string temp = oss.str(), today;
	// cout << temp << '\n';
	std::istringstream iss(temp);
	int cnt{};
	while (std::getline(iss, temp, '-')) {
		today += temp;
		if (cnt == 0) { today += "년 "; ++cnt; }
		else if (cnt == 1) { today += "월 "; ++cnt; }
		else if (cnt == 2) { today += "일"; ++cnt; }
	}
	// cout << today << '\n';
	return today;

	// cout << floor<months>(localTime);
	// months부터는 출력이 안 되네?
	/*
	__msvc_chrono.hpp
		_EXPORT_STD using nanoseconds  = duration<long long, nano>;
		_EXPORT_STD using microseconds = duration<long long, micro>;
		_EXPORT_STD using milliseconds = duration<long long, milli>;
		_EXPORT_STD using seconds      = duration<long long>;
		_EXPORT_STD using minutes      = duration<int, ratio<60>>;
		_EXPORT_STD using hours        = duration<int, ratio<3600>>;
	#if _HAS_CXX20
		_EXPORT_STD using days   = duration<int, ratio_multiply<ratio<24>, hours::period>>;
		_EXPORT_STD using weeks  = duration<int, ratio_multiply<ratio<7>, days::period>>;
		_EXPORT_STD using years  = duration<int, ratio_multiply<ratio<146097, 400>, days::period>>;
		_EXPORT_STD using months = duration<int, ratio_divide<years::period, ratio<12>>>;
	#endif
	*/
}

int main() {

	string today = GetToday();

	vector<string> indexToName{ "", "김용우", "박준섭", "이재홍", "이충혁", "정영훈", "탁성건"};
	int N{ static_cast<int>(indexToName.size()) - 1 }; // 6
	vector<vector<int>> result;

	// vector<int> vec{ 1, 2, 3, 4, 5, 6 };
	vector<int> vec;
	for (int i : std::views::iota(1) | std::views::take(N)) vec.push_back(i);
	// lazy evaluation(iota) => take를 통해 정해진 개수(N)만큼 넣기.

	// Print<vector<int>>(vec); - 명시적으로 지정 가능
	// Print(vec);

	do {
		result.push_back(vec);
	} while (std::next_permutation(begin(vec), end(vec)));
	// cout << result.size() << '\n'; // peoples! 개 만큼 결과 나옴.

	// Print(result.back()); // 마지막 꺼만 출력해보자

	std::random_device seed;
	std::uniform_int_distribution<int> UintD(0, static_cast<int>(result.size() - 1)); // [0, result.size() - 1]
	int index = UintD(seed);

	// 기존에 숫자로 결과 뽑던 코드(deprecated)
	// for (int& i : result[index]) cout << i << ' ';

	// 바로 이름으로 (by lambda)
	auto func = [&indexToName](const int& i) -> string { return indexToName[i]; };
	vector<string> resultName;
	for (auto i : result[index] | std::views::transform(func)) resultName.emplace_back(i);


	cout << "오늘 날짜 : \t\t" << today << "\n\n이번주 PR Table은 \t";
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
