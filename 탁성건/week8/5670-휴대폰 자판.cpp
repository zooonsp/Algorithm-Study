#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 26;

struct Node {
  bool isEnd;
  int childCnt;
  Node *child[SIZE];

  Node() {
    isEnd = false;
    childCnt = 0;
    memset(child, 0, sizeof(child));
  }

  ~Node() {
    for (int i = 0; i < SIZE; i++)
      if (child[i] != nullptr)
        delete child[i];
  }
};

class Trie {
private:
  Node head;

public:
  void insert(string str) {
    Node *ptr = &head;

    for (int i = 0; i < str.size(); i++) {
      int idx = str[i] - 'a';

      if (ptr->child[idx] == nullptr) {
        ptr->child[idx] = new Node;
        ptr->childCnt++;
      }

      ptr = ptr->child[idx];
    }

    ptr->isEnd = true;
  }

  int find(string str) {
    Node *ptr = head.child[str[0] - 'a'];

    int pushCnt = 1;

    for (int i = 1; i < str.length(); i++) {
      if (ptr->childCnt > 1 || ptr->isEnd)
        pushCnt++;

      ptr = ptr->child[str[i] - 'a'];
    }

    return pushCnt;
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cout << fixed;
  cout.precision(2);

  int N;

  while (cin >> N) {
    vector<string> dict(N);
    Trie trie;

    for (int i = 0; i < N; i++) {
      cin >> dict[i];

      trie.insert(dict[i]);
    }

    int sum = 0;

    for (int i = 0; i < N; i++)
      sum += trie.find(dict[i]);

    cout << (double)sum / N << '\n';
  }

  return 0;
}
