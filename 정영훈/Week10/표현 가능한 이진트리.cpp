// lambda
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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
	//reverse(begin(binaryNumber), end(binaryNumber));
	return binaryNumber;
}

vector<int> solution(vector<long long> numbers) {
	vector<int> answer;
	for (long long& number : numbers) {
		string binaryNumber = MakeBinaryNumber(number);

		auto ret = [binaryNumber]() -> bool {
			// leaf node
			vector<int> nodeIndexes;
			for (int i = 0; i < binaryNumber.length(); i += 2) nodeIndexes.push_back(i);
			while (nodeIndexes.size() > 1) {
				vector<int> tempEvens;
				for (int i{}; i < (int)nodeIndexes.size(); i += 2) {
					int mid = (nodeIndexes[i] + nodeIndexes[i + 1]) / 2;
					if (binaryNumber[nodeIndexes[i]] == '1' || binaryNumber[nodeIndexes[i+1]] == '1') {
						if (binaryNumber[mid] != '1') return false;
					}
					tempEvens.push_back(mid);
				}
				nodeIndexes.swap(tempEvens);
			}
			return true;
		} ();

		if (ret) answer.push_back(1);
		else answer.push_back(0);
	}
	return answer;
}