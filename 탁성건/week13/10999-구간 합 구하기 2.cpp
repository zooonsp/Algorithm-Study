// https://www.acmicpc.net/blog/view/26
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct SegTree {
  vector<long long> tree;
  vector<long long> lazy;

  SegTree(const vector<long long> &nums) {
    int h = ceil(log2(nums.size()));
    int sz = (1 << (h + 1));

    vector<long long>(sz).swap(tree);
    vector<long long>(sz).swap(lazy);

    init(1, 1, nums.size(), nums);
  }

  long long init(int cur, int start, int end, const vector<long long> &nums) {
    if (start == end)
      return tree[cur] = nums[start - 1];

    int mid = start + (end - start) / 2;
    return tree[cur] = init(cur * 2, start, mid, nums) +
                       init(cur * 2 + 1, mid + 1, end, nums);
  }

  void updateLazy(const int cur, const int start, const int end) {
    if (lazy[cur] != 0) {
      tree[cur] += lazy[cur] * (end - start + 1);
      if (start != end) {
        lazy[cur * 2] += lazy[cur];
        lazy[cur * 2 + 1] += lazy[cur];
      }
      lazy[cur] = 0;
    }
  }

  void updateTree(int cur, int start, int end, const int left, const int right,
                  const long long plus) {
    updateLazy(cur, start, end);

    if (end < left || right < start)
      return;

    if (left <= start && end <= right) {
      tree[cur] += plus * (end - start + 1);
      if (start != end) {
        lazy[cur * 2] += plus;
        lazy[cur * 2 + 1] += plus;
      }
      return;
    }

    int mid = start + (end - start) / 2;
    updateTree(cur * 2, start, mid, left, right, plus);
    updateTree(cur * 2 + 1, mid + 1, end, left, right, plus);
    tree[cur] = tree[cur * 2] + tree[cur * 2 + 1];
  }

  long long query(int cur, int start, int end, const int left,
                  const int right) {
    updateLazy(cur, start, end);

    if (end < left || right < start)
      return 0;
    if (left <= start && end <= right)
      return tree[cur];

    int mid = start + (end - start) / 2;
    return query(cur * 2, start, mid, left, right) +
           query(cur * 2 + 1, mid + 1, end, left, right);
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  int N, M, K;
  cin >> N >> M >> K;

  vector<long long> nums(N);
  for (long long &num : nums)
    cin >> num;

  SegTree segTree(nums);

  for (int k = 0; k < M + K; k++) {
    int cmd, left, right;
    long long plus;

    cin >> cmd >> left >> right;

    if (cmd == 1) {
      cin >> plus;
      segTree.updateTree(1, 1, N, left, right, plus);
    } else if (cmd == 2) {
      cout << segTree.query(1, 1, N, left, right) << '\n';
    }
  }

  return 0;
}
