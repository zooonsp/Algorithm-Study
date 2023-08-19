#include <algorithm>
#include <vector>
using namespace std;

struct Node {
  int x;
  int num;
  Node *left;
  Node *right;
  Node(int x, int num) : x(x), num(num), left(nullptr), right(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};

bool cmp(vector<int> lhs, vector<int> rhs) {
  if (lhs[1] > rhs[1])
    return true;
  if (lhs[1] < rhs[1])
    return false;
  return lhs[0] < rhs[0];
}

Node *root;
vector<int> preRes, postRes;

void insert(int x, int num) {
  Node *ins = new Node(x, num);
  Node *parent = nullptr;
  Node *child = root;

  while (child) {
    parent = child;
    x < child->x ? child = child->left : child = child->right;
  }

  if (!parent)
    root = ins;
  else
    x < parent->x ? parent->left = ins : parent->right = ins;
}

void preorder(Node *now) {
  if (!now)
    return;

  preRes.push_back(now->num);
  preorder(now->left);
  preorder(now->right);
}

void postorder(Node *now) {
  if (!now)
    return;

  postorder(now->left);
  postorder(now->right);
  postRes.push_back(now->num);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
  for (int i = 0; i < nodeinfo.size(); ++i)
    nodeinfo[i].push_back(i + 1);

  sort(nodeinfo.begin(), nodeinfo.end(), cmp);

  delete root;
  root = nullptr;

  vector<int>().swap(preRes);
  vector<int>().swap(postRes);

  for (const auto &now : nodeinfo)
    insert(now[0], now[2]);

  preorder(root);
  postorder(root);

  return {preRes, postRes};
}
