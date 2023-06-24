/*
각 판매원의 이름을 담은 배열 enroll
	길이 = 1 이상 10,000 이하
	민호의 이름은 없음.
각 판매원을 다단계 조직에 참여시킨 다른 판매원의 이름을 담은 배열 referral
	enroll과 길이 동일
	i번째에 있는 이름은 enroll 내에서 i번째에 있는 판매원을 조직에 참여시킨 사람의 이름.
	"-"인 경우에 누구의 추천도 없이 조직에 가입 => center 밑에
	enroll에 등장하는 이름은 조직에 참여한 순서에 따름
판매량 집계 데이터의 판매원 이름을 나열한 배열 seller
	길이 = 1 이상 100,000 이하
	i번째 이름은 i번재 판매 집계 데이터가 어느 판매원에 의한 것인지를 나타냄.
	같은 이름 중복도 가능!
판매량 집계 데이터의 판매 수량을 나열한 배열 amount
	seller의 길이와 동일.
	i번째 판매 집계 데이터의 판매량을 나타냄.
	판매량의 범위는 1 이상 100이하인 자연수

칫솔 한 개를 판매하여 얻어지는 이익 = 100원
모든 조직 구성원들의 이름은 10 글자 이내의 영문 알파벳 소문자들로만 이루어짐.

각 판매원이 득한 이익금을 나열한 배열을 return 하도록 solution 함수를 완성해주세요.
	판매원에게 배분된 이익금의 총합을 계산하여(정수형으로), 
	입력으로 주어진 enroll에 이름이 포함된 순서에 따라 나열하면 됩니다
*/

#include <bits/stdc++.h>

using namespace std;

constexpr int PRICE = 100;

unordered_map<string, int> um;

vector<vector<int>> graph;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
	vector<int> answer;
	const int SIZE = static_cast<int>(enroll.size()); // 사람 수
	answer.assign(SIZE, 0);
	graph = vector<vector<int>>(SIZE);

	for (int i = 0; i < SIZE; ++i) {
		um.emplace(enroll[i], i); // 현재 enroll string에 해당하는 index 저장
		if (referral[i] == "-") continue;
		graph[i].push_back(um[referral[i]]); // 현재 index와 과거에 저장했던 enroll string에 해당하는 index 연결 (부모 index 연결)
	}

	const int ALLSALE = static_cast<int>(seller.size());
	for (int i = 0; i < ALLSALE; ++i) {
		int earning = PRICE * amount[i];
		int index = um[seller[i]];
		while (earning) {
			int upper = earning / 10;
			if (upper == 0) {
				answer[index] += earning;
				break;
			}
			answer[index] += (earning - upper);
			earning /= 10;
			if (graph[index].size() == 0) break; // 부모가 center
			index = graph[index][0];
		}
	}

	return answer;
}

int main() {
	cin.tie(0); // nullptr
	cout.tie(0); // nullptr
	ios::sync_with_stdio(0); // false

	// TC 1
	vector<string> enroll1{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral1{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller1{ "young", "john", "tod", "emily", "mary" };
	vector<int> amount1{ 12,4,2,5,10 };
	for (int& a : solution(enroll1, referral1, seller1, amount1)) {
		cout << a << ' ';
	}
	cout << '\n';

	// TC 2
	vector<string> enroll2{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral2{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller2{ "sam", "emily", "jaimie", "edward" };
	vector<int> amount2{ 2, 3, 5, 4 };
	for (int& a : solution(enroll2, referral2, seller2, amount2)) {
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}