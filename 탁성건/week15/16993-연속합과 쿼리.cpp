#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 100000001;

struct Node {
  int leftSum;
  int rightSum;
  int totalSum;
  int maxSum;
};

struct SegmentTree {
  vector<Node> tree;

  SegmentTree(const vector<int> &nums) {
    int h = (int)ceil(log2(nums.size()));
    int sz = (1 << (h + 1));

    vector<Node>(sz).swap(tree);
    init(1, 1, nums.size(), nums);
  }

  Node init(int cur, int start, int end, const vector<int> &nums) {
    Node &now = tree[cur];

    if (start == end)
      return now = {nums[start - 1], nums[start - 1], nums[start - 1],
                    nums[start - 1]};

    int mid = start + (end - start) / 2;
    Node leftChild = init(cur * 2, start, mid, nums);
    Node rightChild = init(cur * 2 + 1, mid + 1, end, nums);

    now.leftSum =
        max(leftChild.leftSum, leftChild.totalSum + rightChild.leftSum);
    now.rightSum =
        max(leftChild.rightSum + rightChild.totalSum, rightChild.rightSum);
    now.totalSum = leftChild.totalSum + rightChild.totalSum;
    now.maxSum = max({leftChild.maxSum, rightChild.maxSum,
                      leftChild.rightSum + rightChild.leftSum});

    return now;
  }

  Node query(int cur, int start, int end, const int left, const int right) {
    if (right < start || end < left)
      return {-INF, -INF, 0, -INF};
    if (left <= start && end <= right)
      return tree[cur];

    int mid = start + (end - start) / 2;
    Node leftChild = query(cur * 2, start, mid, left, right);
    Node rightChild = query(cur * 2 + 1, mid + 1, end, left, right);

    Node res;
    res.leftSum =
        max(leftChild.leftSum, leftChild.totalSum + rightChild.leftSum);
    res.rightSum =
        max(leftChild.rightSum + rightChild.totalSum, rightChild.rightSum);
    res.totalSum = leftChild.totalSum + rightChild.totalSum;
    res.maxSum = max({leftChild.maxSum, rightChild.maxSum,
                      leftChild.rightSum + rightChild.leftSum});

    return res;
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  int N, M;
  int left, right;

  cin >> N;
  vector<int> nums(N);
  for (int i = 0; i < N; i++)
    cin >> nums[i];

  SegmentTree segTree(nums);

  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> left >> right;
    cout << segTree.query(1, 1, N, left, right).maxSum << '\n';
  }

  return 0;
}
