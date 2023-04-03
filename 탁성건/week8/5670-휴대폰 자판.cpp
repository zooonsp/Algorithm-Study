#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 26;

struct Node {
  bool isEnd;        // 문자열의 끝인가?
  int childCnt;      // child의 개수
  Node *child[SIZE]; // child node를 가리킬 포인터 배열

  Node() { // 생성자를 이용한 초기화
    isEnd = false;
    childCnt = 0;
    memset(child, 0, sizeof(child));
  }

  ~Node() { // 동적할당 해제
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
    Node *ptr = head.child[str[0] - 'a']; // 첫 글자부터 시작

    int pushCnt = 1; // 첫 글자는 반드시 버튼을 눌러야 한다.

    // 모든 글자를 확인하며
    for (int i = 1; i < str.length(); i++) {
      // 자식이 2개 이상이거나 다른 문자열의 끝인 경우 버튼을 눌러야 한다.
      if (ptr->childCnt > 1 || ptr->isEnd)
        pushCnt++;

      ptr = ptr->child[str[i] - 'a'];
    }

    return pushCnt;
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  // 소수점 둘째 자리까지 반올림하여 출력
  cout << fixed;
  cout.precision(2);

  int N;

  while (cin >> N) {
    vector<string> dict(N);
    Trie trie;

    // N개의 단어를 Trie에 insert
    for (int i = 0; i < N; i++) {
      cin >> dict[i];

      trie.insert(dict[i]);
    }

    int sum = 0;

    // N개의 단어를 Trie에서 find하며 버튼을 누른 횟수의 합 구하기
    for (int i = 0; i < N; i++)
      sum += trie.find(dict[i]);

    // 각 단어를 입력하기 위해 버튼을 눌러야 하는 횟수의 평균
    cout << (double)sum / N << '\n';
  }

  return 0;
}
