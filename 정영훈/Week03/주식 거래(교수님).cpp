#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

int Ms, Ma;
int N, L;
int board[15][16];
int buy_signal[15];
int max_profit;

void dfs(int id, int month, int budget, int profit) { // 현재 달에서 최대한 낼 수 있는 수익 계산하기
    if (id == N) {
        max_profit = max(max_profit, profit);
        return;
    }
    if (buy_signal[id] == 0) // 수익이 나지 않는 종목은 그냥 스킵
        dfs(id + 1, month, budget, profit);
    else {
        int n = 0;
        while (board[id][month] * n <= budget) { // 살 수 있을만큼 사보기(1개부터 ~ 최대)
            dfs(id + 1, month, budget - board[id][month] * n, profit + (board[id][month + 1] - board[id][month]) * n);
            n++;
        }
    }
}

int solution() {
    int budget = Ms;
    for (int month = 0; month < L; month++) {
        memset(buy_signal, 0, sizeof(buy_signal));
        for (int id = 0; id < N; id++) {
            if (board[id][month + 1] - board[id][month] <= 0)
                continue;
            buy_signal[id] = 1;
        }
        max_profit = 0;
        dfs(0, month, budget, 0);
        budget += Ma + max_profit;
    }
    return budget - (Ms + Ma * L);
}
void input() {
    cin >> Ms >> Ma;
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L + 1; j++) {
            cin >> board[i][j];
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        input();
        cout << "#" << tc << " " << solution() << "\n";
    }

    return 0;
}