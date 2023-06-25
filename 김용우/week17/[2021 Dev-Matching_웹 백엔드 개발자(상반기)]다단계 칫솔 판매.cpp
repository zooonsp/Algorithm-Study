#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::string> parent;	// parent[i]: i 번째 자식 부모 정보 -> <자식, 부모>
std::unordered_map<std::string, int> profit;	// profit[i]: i 번째 사람과 이익 정보 -> <사람, 이익>

void updateProfit(std::string name, int money){	// name: 사람 이름, money: 이익
	if(name == "-") return;	// 더 이상 부모 정점이 없다면 return

	int parentMoney = money * 0.1;	// parentMoney: 부모에게 배분하는 이익 -> 10%, 10%를 계산한 금액이 1원 미만인 경우 이득을 분배하지 않고 자신이 모두 가짐
	profit[name] += (money - parentMoney);	// 부모에게 배분하고 남은 자신의 이익 더함

	if(parentMoney < 1) return;	// 1원 미만인 경우에는 이득을 분배하지 않음

	updateProfit(parent[name], parentMoney);	// 부모에게 전달된 이익을 계속 해서 계산 -> 최상위 부모에게 까지 가거나 1원 미만일 때 까지

	return;
}

std::vector<int> solution(std::vector<std::string> enroll, std::vector<std::string> referral, std::vector<std::string> seller, std::vector<int> amount) {
    std::vector<int> answer;

	// 트리 구조 생성
	for(int i=0; i<enroll.size(); i++){
		if(referral[i] == "-") parent[enroll[i]] = "-";	// 부모가 없는 최 상단 정점은 "-"의 값을 가짐
		else parent[enroll[i]] = referral[i];	// 부모 정보 입력
	}

	// 이익 계산
	for(int i=0; i<seller.size(); i++){
		int money = amount[i] * 100;	// money: 칫솔 판매 이익 -> 칫솔 한 개를 판매하여 얻어지는 이익은 100원
		updateProfit(seller[i], money);
	}

	// 출력
	for(int i=0; i<enroll.size(); i++){	// enroll에 이름이 포함된 순서에 따라 나열
		answer.push_back(profit[enroll[i]]);
	}

    return answer;
}

int main(){

	std::vector<std::string> enroll = {"john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young"};
	std::vector<std::string> referral = {"-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward"};
	std::vector<std::string> seller = {"young", "john", "tod", "emily", "mary"};
	std::vector<int> amount = {12, 4, 2, 5, 10};

	std::vector<int> answer = solution(enroll, referral, seller, amount);

	for(int i=0; i<answer.size(); i++){	// 출력 확인
		std::cout << answer[i] << ' ';
	}

	return 0;
}