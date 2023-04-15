/*
1000000000000000
0011 | 1000 1101 | 0111 1110 | 1010 0100 | 1100 0110 | 1000 0000 | 0000 0000
해봤자 62개
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string MakeBinaryNumber(long long& number) {
	string binaryNumber;
	long long temp = number;
	int treeHeight{ 1 };
	while (temp) {
		if (temp & 1) binaryNumber += "1";
		else binaryNumber += "0";
		temp >>= 1;
		if (binaryNumber.length() > ((1 << treeHeight) - 1)) {
			++treeHeight;
		}
	}
	int nodeNumber = (1 << treeHeight) - 1;
	for (int i = (int)binaryNumber.length(); i < nodeNumber; ++i) {
		binaryNumber += "0";
	}
	// 뒤집어야 진짜 의도한 이진수 이긴 하지만 안 뒤집어도 이후 비교엔 지장 없음.
	// reverse(begin(binaryNumber), end(binaryNumber));
	return binaryNumber;
}

bool Check(string& binaryNumber) {
	// leaf node
	vector<int> nodeIndexes;
	for (int i = 0; i < (int)binaryNumber.length(); i += 2) nodeIndexes.push_back(i);
	while (nodeIndexes.size() > 1) {
		vector<int> temp;
		for (int i{}; i < (int)nodeIndexes.size(); i += 2) {
			int mid = (nodeIndexes[i] + nodeIndexes[i + 1]) / 2;
			if (binaryNumber[nodeIndexes[i]] == '1' || binaryNumber[nodeIndexes[i + 1]] == '1') {
				if (binaryNumber[mid] != '1') return false;
			}
			temp.push_back(mid);
		}
		nodeIndexes.swap(temp);
	}
	return true;
}

vector<int> solution(vector<long long> numbers) {
	vector<int> answer;
	for (long long& number : numbers) {
		string binaryNumber = MakeBinaryNumber(number);
		if (Check(binaryNumber)) answer.push_back(1);
		else answer.push_back(0);
	}
	return answer;
}

int main() {
	// vector<long long> numbers{ 7, 42, 5 }; // 1 1 0
	// vector<long long> numbers{ 63, 111, 95, 58 }; // 1 1 0 1
	vector<long long> numbers{ 1000000000000000 };
	vector<int> answer = solution(numbers);
	for (int& i : answer) cout << i << ' ';
	return 0;
}