#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Trie에서 사용할 Node 구조체
struct Node {
  bool isEnd;      // 전화번호의 끝인가?
  Node *child[10]; // child node를 가리킬 포인터 배열(0~9)
  Node() {         // 생성자를 이용한 초기화
    isEnd = false;
    memset(child, 0, sizeof(child));
  }
};

class Trie {
private:
  Node head; // Trie의 최상단 Node

public:
  bool insert(string str) {
    Node *ptr = &head; // Node를 가리킬 포인터. head를 가리키도록 초기화

    // 전화번호를 처음부터 끝까지 확인하며
    for (int i = 0; i < str.size(); i++) {
      int num = str[i] - '0';

      if (ptr->child[num] == nullptr) // num에 해당하는 child가 없다면 생성
        ptr->child[num] = new Node();

      if (ptr->isEnd) // 이미 해당 전화번호로 끝난 경우가 있다면 false
        return false;

      ptr = ptr->child[num]; // ptr이 child node를 가리키도록 변경
    }

    ptr->isEnd = true; // 전화번호의 끝 표시

    return true;
  }

  bool find(string str) {
    Node *ptr = &head; // Node를 가리킬 포인터. head를 가리키도록 초기화

    // 전화번호를 처음부터 끝까지 확인하며
    for (int i = 0; i < str.size(); i++) {
      int num = str[i] - '0';

      if (ptr->child[num] == nullptr) // num에 해당하는 child가 없다면 false
        return false;

      ptr = ptr->child[num]; // ptr이 child node를 가리키도록 변경
    }

    return ptr->isEnd; // 전화번호의 끝인가?를 return
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

    sort(phone.begin(), phone.end()); // 오름차순 정렬

    for (int i = 0; i < N; i++) {
      if (!trie.insert(phone[i])) { // 접두어가 있다면
        ans = "NO";                 // 일관성 있는 목록이 아니다.
        break;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
