#include <iostream>
#include <vector>
#include <string>

char input[100000][11];	// input[i][j]: i 번째 전화번호
std::vector<std::string> num;

struct Trie{
	Trie *node[10];
	bool finish;
	Trie(){
		finish=false;
		for(int i=0; i<10; i++)
			node[i]=NULL;
	}

	void insert(char *str){
		if(*str==NULL){
			finish=true;
			return;
		}
		int cur = *str-'0';
		if(node[cur]==NULL)
			node[cur] = new Trie();
		node[cur]->insert(str+1);
	}

	bool find(char *str){
		if(*str==NULL){
			return false;
		}
		if(finish==true){
			return true;
		}
		int cur = *str-'0';
		if(node[cur]==NULL) return false;
		return node[cur]->find(str+1);
	}
};

int main(){
	int T;	// T: 테스트 케이스
	std::cin >> T;
	while(T--){
		int n;	// n: 전화번호의 수
		std::cin >> n;
		Trie *root = new Trie();	// *root: Trie 구조의 시작점

		for(int i=0; i<n; i++){
			std::cin >> input[i];	// 전화번호 입력
			num.push_back(input[i]);
			root->insert(input[i]);	// Trie 구조에 넣기
		}
		for(int i=0; i<n; i++){
			if(root->find(input[i])){
				std::cout << "NO\n";
				break;
			}else if(i==n-1){
				std::cout << "YES\n";
			}
		}
	}

	return 0;
}