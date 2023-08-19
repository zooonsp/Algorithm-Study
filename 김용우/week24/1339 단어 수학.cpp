#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

struct Weight{
	char alpha;	// alpha: 알파벳 대문자
	int weight;	// weight: 알파벳 대문자의 가중치
};

int N;	// N: 단어의 수
std::string word[10];	// word[i]: i 번째 단어
Weight alpha[26];	// alpha[i]: 가중치로 내림차순 정렬한 알파벳
int weight[26];	// weight[i]: i 번째 알파벳 대문자의 가중치
int ans;	// ans: 단어의 합의 최댓값

bool cmp(Weight left, Weight right){
	if(left.weight != right.weight) return left.weight > right.weight;

	return false;
}

void sol(){

	for(int i=0; i<26; i++) alpha[i].alpha = 'A' + i;	// 알파벳 정보 초기화

	for(int i=0; i<N; i++){
		std::string s = word[i];	// s: 알파벳의 가중치를 조사할 단어
		int len = s.length();	// len: 단어의 길이

		for(int j=0; j<len; j++){
			alpha[s[j]-'A'].weight += std::pow(10, len - j - 1);	// 단의 가중치는 자릿수
		}
	}

	std::sort(alpha, alpha + 26, cmp);	// 조사한 가중치에 대하여 내림차순

	int value = 9;	// value: 알파벳의 값
	for(int i=0; i<26; i++){
		if(alpha[i].weight == 0) break;	// 알파벳이 등장한 적 없다면 break
		weight[alpha[i].alpha - 'A'] = value;	// 가중치가 높은 순서대로 높은 값 부여
		value--;
	}

	for(int i=0; i<N; i++){
		std::string s = word[i];	// s: 알파벳의 가중치를 줄 단어
		int len = s.length();	// len: 단어의 길이
		int tmpValue = 0;	// tmpValue: 단어의 값

		for(int j=0; j<len; j++){	// 값 계산
			tmpValue *= 10;
			tmpValue += weight[s[j] - 'A'];
		}

		ans += tmpValue;
	}

	return;
}

void input(){

	std::cin >> N;

	for(int i=0; i<N; i++){
		std::cin >> word[i];	// 단어 입력
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}