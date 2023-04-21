#include <iostream>
#include <algorithm>

int Ms;	// Ms: 초기 시드액
int Ma;	// Ma: 매달 추가적으로 투자하는 금액
int L;	// L: 주어지는 과거 데이터 기간 
int N;	// N: 주어지는 과거 데이터의 종목 수
int table[16][16];	// table[i][j]: i 종목의 j 개월의 주식 가격
int buyStock[16];	// buyStock[i]: i 종목의 구매 주식 수
int totalMoney;	// totalMoney: 잔고
int monthProfit;	// monthProfit: 다음 달에 최대로 이득을 보기 위한 돈
int tempBuyStock[16];	// tempBuyStock[i]: 구매 가능한 i 종목의 최대 주식 수
int tempTempBuyStock[16];	// tempTempBuyStock[i]: 가장 이득이 되는 i 종목의 주식 수

void DFS(int month, int money, int profit) {	// month: 달, money: 남은 돈, profit: 다음 달과 비교해서 이득

	if (money >= 0) {
		if (monthProfit < profit) {	// 이전 계산보다 더 이득 보는 경우
			for (int i = 0; i < N; i++) {
				monthProfit = profit;
				buyStock[i] = tempTempBuyStock[i];	// buyStock 갱신
			}
		}
			
	}
	else {
		return;
	}

	for (int i = 0; i < N; i++) {
		if (tempBuyStock[i] == 0) continue;	// i 종목을 더 이상 구매할 수 없으면 continue

		tempBuyStock[i]--;
		tempTempBuyStock[i]++;
		DFS(month, money-table[i][month], profit + table[i][month+1] - table[i][month]);
		tempBuyStock[i]++;
		tempTempBuyStock[i]--;
	}

	return;
}

void buy(int month) {
	for (int i = 0; i < N; i++) {	// 초기화
		tempBuyStock[i] = 0;	// 최대로 구매 가능 주식
		tempTempBuyStock[i] = 0;	// 가장 이득이 되는 구매 주식
	}

	// month와 month + 1의 금액을 비교하여 주식 가격이 오른다면 매수
	for (int i = 0; i < N; i++) {
		if (table[i][month] > table[i][month + 1])	continue;// i 종목이 다음 달에 떨어지면 continue
		tempBuyStock[i] = totalMoney / table[i][month];	// 가지고 있는 돈으로 최대한 많이 사보기
	}

	monthProfit = 0;
	DFS(month, totalMoney, 0);

	return;
}

void sell(int month) {
	for (int i = 0; i < N; i++) {
		if (buyStock[i] == 0) continue;	// i 종목을 구매하지 않았다면 continue
		totalMoney += buyStock[i] * table[i][month];	// i 종목 매도하고 금액 합산
		buyStock[i] = 0;	// i 종목 초기화
	}

	return;
}

int sol() {
	totalMoney = Ms;	// 초기 시드액 지급

	for (int i = 0; i <= L; i++) {	// i 개월
		if (i != 0) {	// 0 개월에는 추가 투자 금액 및 매도 없음
			totalMoney += Ma;	// 투자금 추가
			sell(i);	// 매도 -> 무조건 매도
		}
		
		if (i != L) {	// L 개월에는 매수 없음
			buy(i);	// 매수
			for (int j = 0; j < N; j++) {
				totalMoney -= buyStock[j] * table[j][i];
			}
		}		
	}

	return totalMoney;
}

void input() {
	std::cin >> Ms >> Ma;
	std::cin >> N >> L;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i <= L; i++) {
			std::cin >> table[j][i];
		}
	}

	return;
}

void reset() {
	totalMoney = 0;

	return;
}

int main() {
	int T;	// T: 테스트 케이스

	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();		
		std::cout << "#" << tc << " " << sol() - Ms - Ma * L << std::endl;	// 잔고 - 초기 시드액 - 주기적 투자 금액 * 투자 달
	}

	return 0;
}