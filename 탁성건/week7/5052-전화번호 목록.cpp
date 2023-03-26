#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  bool isEnd;
  Node *child[10];
  Node() {
    isEnd = false;
    memset(child, 0, sizeof(child));
  }
};

class Trie {
private:
  Node head;

public:
  bool insert(string str) {
    Node *ptr = &head;

    for (int i = 0; i < str.size(); i++) {
      int num = str[i] - '0';

      if (ptr->child[num] == nullptr)
        ptr->child[num] = new Node();

      if (ptr->isEnd)
        return false;

      ptr = ptr->child[num];
    }

    ptr->isEnd = true;

    return true;
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++) {
    int N;
    cin >> N;

    string ans = "YES";
    Trie trie;
    vector<string> phone(N);

    for (int i = 0; i < N; i++)
      cin >> phone[i];

    sort(phone.begin(), phone.end());

    for (int i = 0; i < N; i++) {
      if (!trie.insert(phone[i])) {
        ans = "NO";
        break;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
