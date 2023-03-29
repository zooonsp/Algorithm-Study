#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int TRIE_KIND = 10; // TRIE 가지 수
const int MAX_STR = 10101; // 문자열 얼마나 들어오는지

struct Trie {
	Trie* Node[TRIE_KIND];
	bool node_end;

	Trie()
	{
		for (int i = 0; i < TRIE_KIND; i++)
		{
			Node[i] = nullptr; // 미리 nullptr로 초기화
		}
		node_end = false;
	}

	bool insert(int index, string &str)
	{
		if (str.size() == index)
		{
			node_end = true; // 마지막 문자 다음 문자에 node_end 삽입
			return true;
		}

		int num = (int)(str[index] - '0'); // char -> 10진수로

		if (Node[num] == nullptr)
		{
			Node[num] = new Trie();
		}
		else if(Node[num]->node_end == true) // 만약 이게 접두사 라면
		{
			return false;
		}

		return Node[num]->insert(index + 1, str);
	}

};

int N; // 문자열의 갯수
vector<string> vec_str;

int input()
{
	cin >> N;
	vec_str.resize(N); // 여기서 사이즈 설정
	for (int i = 0; i < N; i++)
	{
		cin >> vec_str[i];
	}
	return 0;
}

bool solve_func()
{
	sort(vec_str.begin(), vec_str.end()); // insert에서 같이 탐색 하기위해 정렬

	Trie num_trie;

	for (int i = 0; i < vec_str.size(); i++)
	{
		if (!num_trie.insert(0, vec_str[i]))
		{
			return false;
		}
	}

	return true;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int tc = 0; tc < T; tc++)
	{
		// init
		vector<string>().swap(vec_str); // 벡터 초기화

		input();
		if (solve_func())
			cout << "YES\n";
		else
			cout << "NO\n";
	}


	return 0;
}