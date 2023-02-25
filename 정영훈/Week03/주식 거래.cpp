// 이론상 실현 가능한 최대 수익 계산
// 초기 시드액 : Ms ( 300 ~ 1000)
// 매달 추가 투자 : Ma (0 ~ 100)
// 과거 데이터 기간 L : 8 ~ 15 (월 단위)
// 과거 데이터 종목 N : 3 ~ 15
// 종목별 주식의 가격 = 100 ~ 2000 (정수)
// 월별 각 등락폭의 최대 범위는 -30% ~ 30%
// 주식은 보유한 현금 내에서만 정수 개 단위로만 매수, 거래 가능
// 주식 수수료 없음
// 매월 보유한 주식은 다음 달에 모두 매도해야 함
// 꼭 주식을 살 필요는 없다.

// DP (?)
// Greedy
// 어차피 다음 달에 다 팔아야 함.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int Ms, Ma; // 첫 시드, 월별 투자 금액
int N, L; // 종목 수, 과거 데이터 기간

struct Info {
	int index; // 종목 번호
	int profits; // 얻을 수 있는 수익
	int cnt; // 몇 개 살 건지
};

int main() {
	// cin.tie(NULL)->sync_with_stdio(false);

	int T;
	// 매월 수익을 낼 수 있으면 다 해라 그냥
	cin >> T;
	for (int tc{ 1 }; tc <= T; ++tc) {
		// reset
		vector<vector<int>> Datas;

		// input
		cin >> Ms >> Ma;
		cin >> N >> L; 
		Datas.assign(N, vector<int>(L + 1, 0));
		for (auto& row : Datas) {
			for (int& i : row) {
				cin >> i;
			}
		}

		// solve
		auto cmp = [](const Info& i1, const Info& i2) {
			return i1.profits > i2.profits;
		}; // 수익 내림차순 정렬
		vector<vector<Info>> eachMonths(L); // 수익 정리
		for (int i = 0; i < L; ++i) { // 달
			for (int n = 0; n < N; ++n) { // 매 종목마다
				if (Datas[n][i + 1] - Datas[n][i] > 0) {
					eachMonths[i].push_back({ n, Datas[n][i + 1] - Datas[n][i], 0 });
				}
			}
			sort(begin(eachMonths[i]), end(eachMonths[i]), cmp);
		}

		int curMoney{ Ms }; // 현재 돈
		vector<Info> curBuying; // 이번에 살 칭구들
		for (int i = 0; i <= L; ++i) {
			// 수익 실현
			for (auto& info : curBuying) {
				curMoney += Datas[info.index][i] * info.cnt;
			}
			curBuying.clear();

			// 매월 입금 (첫달은 없네)
			if(i) curMoney += Ma;
			auto compare = [](const Info& i1, const Info& i2) {
				return i1.profits * i1.cnt < i2.profits * i2.cnt;
			}; // 벌 수 있는 수익 내림차순 정렬
			
			if (i < L) {
				// 살거 사기
				while(1) {
					priority_queue<Info, vector<Info>, decltype(compare)> pq(compare);
					// Info : index, profits, cnt
					for (auto& nowMonth : eachMonths[i]) {
						// 현재 금액으로 살 수 있는 애들 넣기
						if (curMoney >= Datas[nowMonth.index][i]) {
							pq.push({ nowMonth.index, nowMonth.profits, curMoney / Datas[nowMonth.index][i] });
						}
					}

					if (pq.empty()) break;

					auto most = pq.top();
					// curMoney -= Datas[most.index][i] * most.cnt; // 현재 금액 * 개수
					curMoney -= Datas[most.index][i]; // 1개씩만 사기
					// curBuying.push_back({ most.index, most.profits, most.cnt }); // 인덱스, 얻을 수 있는 수익, 개수
					curBuying.push_back({ most.index, most.profits, 1 });
				}
			}
		}

		// output
		int firstInvest = Ms + Ma * L;
		cout << "#" << tc << ' ' << curMoney - firstInvest << endl;
	}
	return 0;
}