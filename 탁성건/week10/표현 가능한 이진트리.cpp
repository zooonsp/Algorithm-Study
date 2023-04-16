#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string tree;

// 현재 탐색하는 tree는 left부터 right까지의 구간
// tree를 탐색했을 때 만나는 실제 노드의 개수 반환
int dfs(int left, int right) {
  // left와 right가 같다면 leaf node
  if (left == right)
    return tree[left] - '0';

  // mid: 현재 트리의 root
  int mid = left + (right - left) / 2;

  // 만약 root가 더미 노드라면 0 반환
  if (tree[mid] == '0')
    return 0;

  // 1: root
  // dfs(left, mid - 1): 왼쪽 sub tree의 실제 노드 개수
  // dfs(mid + 1, right): 오른쪽 sub tree의 실제 노드 개수
  return 1 + dfs(left, mid - 1) + dfs(mid + 1, right);
}

vector<int> solution(vector<long long> numbers) {
  vector<int> answer;

  for (long long num : numbers) {
    tree.clear();
    // totalCnt: 포화 이진트리로 만들었을 때 노드 개수
    // nodeCnt: 더미 노드가 아닌 실제 노드의 개수
    int totalCnt = 1, nodeCnt = 0;

    // num을 이진수로 변경(문자 형태로 tree에 역순 저장)
    while (num > 0) {
      nodeCnt += num & 1;
      tree.push_back((num & 1) + '0');
      num >>= 1;
    }

    // 포화 이진트리의 노드 개수 계산
    while (totalCnt - 1 < tree.size())
      totalCnt <<= 1;

    totalCnt -= 1;

    // 부족한 노드 개수만큼 더미 노드 추가
    while (tree.size() < totalCnt)
      tree.push_back('0');

    // tree 뒤집기
    reverse(tree.begin(), tree.end());

    // tree 탐색 시 만나는 실제 노드 개수가 nodeCnt와 같은지 확인
    dfs(0, tree.size() - 1) == nodeCnt ? answer.push_back(1)
                                       : answer.push_back(0);
  }

  return answer;
}
