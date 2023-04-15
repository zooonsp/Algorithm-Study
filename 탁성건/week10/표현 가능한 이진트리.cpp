#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string tree;

int dfs(int left, int right) {
  if (left == right)
    return tree[left] - '0';

  int mid = left + (right - left) / 2;

  if (tree[mid] == '0')
    return 0;

  return 1 + dfs(left, mid - 1) + dfs(mid + 1, right);
}

vector<int> solution(vector<long long> numbers) {
  vector<int> answer;

  for (long long num : numbers) {
    tree.clear();
    int totalCnt = 1, nodeCnt = 0;

    while (num > 0) {
      nodeCnt += num & 1;
      tree.push_back((num & 1) + '0');
      num >>= 1;
    }

    while (totalCnt - 1 < tree.size())
      totalCnt <<= 1;

    totalCnt -= 1;

    while (tree.size() < totalCnt)
      tree.push_back('0');

    reverse(tree.begin(), tree.end());

    dfs(0, tree.size() - 1) == nodeCnt ? answer.push_back(1)
                                       : answer.push_back(0);
  }

  return answer;
}
