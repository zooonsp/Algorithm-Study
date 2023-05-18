#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> inorder;
vector<int> inorderIdx;
vector<int> postorder;

void solve(int inLeft, int inRight, int postLeft, int postRight) {
  if (inLeft > inRight || postLeft > postRight)
    return;

  int root = postorder[postRight];
  cout << root << ' ';

  int rootIdx = inorderIdx[root];
  int leftSize = rootIdx - inLeft;

  solve(inLeft, rootIdx - 1, postLeft, postLeft + leftSize - 1);
  solve(rootIdx + 1, inRight, postLeft + leftSize, postRight - 1);
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N;

  vector<int>(N).swap(inorder);
  vector<int>(N + 1).swap(inorderIdx);
  vector<int>(N).swap(postorder);

  for (int i = 0; i < N; i++) {
    cin >> inorder[i];
    inorderIdx[inorder[i]] = i;
  }

  for (int i = 0; i < N; i++)
    cin >> postorder[i];

  solve(0, N - 1, 0, N - 1);

  return 0;
}
