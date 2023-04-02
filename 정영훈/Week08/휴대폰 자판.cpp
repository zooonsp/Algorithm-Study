#include <iostream>
#include <string>
#include <vector>

constexpr int SIZE = 26;

using namespace std;

struct Trie {
	int count;
	Trie* next[SIZE];
	Trie(int count = 0) : count(count) {
		for (int i{}; i < SIZE; ++i) {
			this->next[i] = nullptr;
		}
	}
	~Trie() {
		for (int i{}; i < SIZE; ++i) {
			if (this->next[i] != nullptr) delete this->next[i];
		}
	}

	/**
	* 새 문자 추가 - Trie 만들기
	*/
	void Insert(string& newStr) {
		int index = newStr[0] - 'a';
		if (!this->next[index]) { // nullptr
			this->next[index] = new Trie;
		}
		this->next[index]->count++;

		Trie* now = this->next[index];

		for (int s = 1; s < (int)newStr.length(); ++s) {
			index = newStr[s] - 'a';
			if (!now->next[index]) {
				now->next[index] = new Trie;
			}
			now->next[index]->count++;
			now = now->next[index];
		}
	}

	/**
	* Trie를 탐색하며 버튼을 몇 번 눌러야 하는지 계산
	*/
	int CountAndFind(string& str) {
		int cnt{ 1 }; // 첫 글자는 무조건 눌러야 함.
		int index = str[0] - 'a';
		Trie* now = this->next[index]; // this = head
		for (int s = 1; s < (int)str.length(); ++s) {
			index = str[s] - 'a';
			if (now->count != now->next[index]->count) { // 다른 문자로 가는 길이 존재함
				++cnt;
			}
			now = now->next[index];
		}
		return cnt;
	}
};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	// 소수점 2자리
	cout << fixed;
	cout.precision(2);

	int N;
	while (cin >> N) {
		// 1. Trie 만들기
		Trie* head = new Trie;
		vector<string> strs(N);
		for (int n = 0; n < N; ++n) {
			cin >> strs[n];
			// MakeTrie
			head->Insert(strs[n]);
		}

		// 2. 개수 세기
		double total{};
		for (int n = 0; n < N; ++n) {
			total += head->CountAndFind(strs[n]);
		}

		cout << total / N << '\n';
		delete head;
	}

	return 0;
}