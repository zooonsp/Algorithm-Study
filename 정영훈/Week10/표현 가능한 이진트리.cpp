// without make binary presentation
#include <vector>

using namespace std;

bool Check(long long& number) {
	int treeHeight = 1;
	// 1 << nodeNumber 하면 int가 최대
	while ((1LL << ((1 << treeHeight) - 1)) - 1 < number) {
		++treeHeight;
	}
	vector<int> nodeIndexes;
	// push_back leaf_nodes
	for (int i = 0; i <= (1 << treeHeight) - 1; i += 2) nodeIndexes.push_back(i);

	while (nodeIndexes.size() > 1) {
		vector<int> temp;
		for (int i{}; i < (int)nodeIndexes.size(); i += 2) {
			int mid = (nodeIndexes[i] + nodeIndexes[i + 1]) / 2;
			if (number & (1LL << nodeIndexes[i]) || number & (1LL << nodeIndexes[i+1])) {
				if (!(number & (1LL << mid))) return false;
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
		if (Check(number)) answer.push_back(1);
		else answer.push_back(0);
	}
	return answer;
}

