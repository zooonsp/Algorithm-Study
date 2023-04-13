#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int TRIE_KIND = 30; // TRIE 가지 수 ( 영문자 )

struct Trie {
	Trie* Node[TRIE_KIND];
	bool node_end;
	int node_cnt;

	Trie()
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			Node[i] = nullptr;
		}
		node_end = false;
		node_cnt = 0;
	}

	~Trie() // 소멸자로 모두 해제 해줘야한다
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			if (Node[i] != nullptr)
			{
				delete Node[i];
			}
		}
	}

	int insert(int index, string& str)
	{
		if (str.size() == index)
		{
			node_end = true;
			return 0;
		}

		int num = (int)(str[index] - 'a');

		if (Node[num] == nullptr)
		{
			Node[num] = new Trie();
			node_cnt++; // 가지수가 늘어나서 cnt ++
		}
		Node[num]->insert(index + 1, str);
		return 0;
	}

	int find_cnt(int index, string& str, int cnt) // index : 어디 문자열 보고 있는지, cnt : 문자열 찾기위해 타이핑한 갯수
	{
		if (str.size() == index) // 기저조건 : 문자열 끝까지 탐색
		{
			return cnt;
		}

		if ((node_cnt > 1 || node_end == true) &&
			index != 0) // node_cnt 와 node_end 부분을 따로 만들면 틀림 ( 타입 '한번'하면 맞는 가지로 들어가서)
		{
			cnt++;
		}

		int num = (int)(str[index] - 'a');
		return Node[num]->find_cnt(index + 1, str, cnt);
	}

};

int N; // 사전에 속한 단어 갯수


int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);

	cout << fixed;
	cout.precision(2);

	while (cin >> N)
	{
		Trie* dictionary = new Trie();
		vector<string> words;
		words.resize(101010);
		int ans = 0;

		for (int i = 0; i < N; i++)
		{
			string temp;
			cin >> temp;
			words[i] = temp;
			dictionary->insert(0, temp);
		}

		for (int i = 0; i < N; i++)
		{
			ans += dictionary->find_cnt(0, words[i], 1);
		}

		cout << (double)ans / N << endl;

		delete dictionary;
	}

	return 0;
}