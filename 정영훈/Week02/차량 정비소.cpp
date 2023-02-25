// N개의 접수 창구, M개의 정비 창구, 고객 수 = K
// 접수 창구에서 고장 접수 -> 정비 창구에서 차량 정비
// 접수 창구 i에서 고객 한 명의 고장을 접수하는데 걸리는 시간 = ai
// 정비 창구 j에서 고객 한 명의 차량을 정비하는데 걸리는 시간 = bj
// 지금까지 정비소를 방문한 고객 = K명
// 고객번호 k의 고객이 차량 정비소에 도착하는 시간은 tk (계산이 아닌 입력)
// 빈 접수 창구가 있는 경우 빈 접수 창구에 가서 고장 접수 (없다면 기다리기)
// 고장 접수 완료 후 정비 창구로 이동
// 빈 정비 창구가 있다면 바로 이동 없다면 기다리기.
 
// 접수 창구의 우선순위
// 1. 고객번호가 낮은 순서대로
// 2. 접수 창구번호가 작은 곳으로
 
// 정비 창구의 우선순위
// 1. 먼저 기다리는 고객이 우선
// 2. 이용했던 접수 창구번호가 작은 고객이 우선
// 3. 정비 창구번호가 작은 곳으로
 
// 접수 -> 정비 이동은 0
// 지갑을 분실한 고객과 같은 접수 창구와 같은 정비 창구를 
// 이용한 고객의 고객번호들을 찾아 합 출력하기
 
// 1<= N, M <= 9
// 1 <= ai, bj <= 20
// 2 <= K <= 1000
// 0 <= tk <= 1000
// 1 <= A <= N
// 1 <= B <= M
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
 
using namespace std;
 
struct changgu {
    int repair;
    int reception;
    changgu(int repair, int reception) : repair(repair), reception(reception) {}
};
 
// 고객 번호에 해당하는 창구 사용 내용
vector<changgu> used;
 
vector<int> repairs; // 정비 창구 - 정비 창구 별 시간 저장(0인 경우 빈 창구)
vector<int> nowUsedReceptions; // index : 창구 번호, value : 창구를 쓰는 사람의 index
vector<int> receptions; // 접수 창구 - 접수 창구 별 시간 저장(0인 경우 빈 창구)
 
int N, M, K; // 접수 창구, 정비 창구, 고객 수
int A, B; // 지갑을 두고 간 사람의 창구 번호(접수, 정비) 
vector<int> repairTimes; // ai
vector<int> receptionTimes; // bj
vector<int> customer; // 고객들의 도착시간과 번호
 
queue<int> waitRepair;
 
int customerCnt; // 서비스를 완료한 사람 카운트
int ans{-1};
 
int main() {
    //freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N >> M >> K >> A >> B;
        used.assign(K + 1, changgu(0, 0));
        customer.assign(K, 0);
        repairs.assign(M + 1, 0); // 현재 정비 창구 관리
        repairTimes.assign(M + 1, 0); // 1부터 가자
        receptions.assign(N + 1, 0); // 현재 접수 창구 관리
        receptionTimes.assign(N + 1, 0); // 1부터 가자
        nowUsedReceptions.assign(N + 1, 0);
        customerCnt = 0;
        ans = -1;
 
        for (int i = 1; i <= N;++i) cin >> receptionTimes[i];
        for (int i = 1; i <= M;++i) cin >> repairTimes[i];
        for (auto& in : customer) cin >> in;
 
        sort(begin(customer), end(customer)); // 도착 시간 별 정렬
 
        int index{1}; // customer index
        for (int time{};;++time) {
 
            if (customerCnt == K) break; // 서비스 다 받았어
 
            // 매 time마다 정비 창구 비우기.
            // 정비
            for (int j = 1; j <= M; ++j) { // j는 정비 창구 번호
                if (repairs[j] && repairs[j] == time) { // 밀리는 거 없어서 같아도 될 듯
                    // 창구 비우기
                    repairs[j] = 0;
                }
                if (repairs[j] == 0 && !waitRepair.empty()) { // q에서 pop
                    int custIndex = waitRepair.front(); // 사람 index
                    waitRepair.pop();
                    repairs[j] = time + repairTimes[j]; // 현재 시간 + 창구별 수리 시간
                    used[custIndex].repair = j;
                    customerCnt++;
                }
            }
 
            // 접수
            // 1. 고객번호가 낮은 순서대로 (이거 그냥 온 순서대로 번호 지정)
            // 2. 접수 창구번호가 작은 곳으로
            for (int i = 1; i <= N; ++i) { // i는 접수 창구 번호
                if (receptions[i] && receptions[i] <= time) { // 먼저 접수 창구 비우면서 정비 창구 보낼지말지
                    // 정비 창구로 이동
                    // 1. 먼저 기다리는 고객이 우선 - 큐로 관리 해야겠네..
                    // 2. 이용했던 접수 창구번호가 작은 고객이 우선
                    // 3. 정비 창구번호가 작은 곳으로
                    bool flag = false;
                    for (int j = 1; j <= M; ++j) { // j는 정비 창구 번호
                        if (repairs[j] == 0) {
                            repairs[j] = receptions[i] + repairTimes[j]; // 접수 시간 + 창구별 수리 시간
                            used[nowUsedReceptions[i]].repair = j; // i번째 창구를 썼던 사람의 repair 창구 기록
                            receptions[i] = 0; // 창구 초기화
                            customerCnt++; // 어차피 자료 다 정리되어서 여기서 추가해도 무관하다 생각함.
                            flag = true;
                            break; // 넣고 나면 뒤에 볼 필요 없음
                        }
                    }
                    if (!flag) { // 정비 창구가 없어서 대기
                        waitRepair.push(nowUsedReceptions[i]); // 기다리는 사람 번호
                        receptions[i] = 0; // 접수 창구 초기화
 
                    }
                }
 
                if (receptions[i] == 0 && index <= K && time>=customer[index - 1]) { // 빈 접수 창구 & 남은 사람이 있다면
                    receptions[i] = time + receptionTimes[i]; // 현재 시간 + 창구별 접수 시간
                    nowUsedReceptions[i] = index; // i번 창구를 쓰는 사람은 index
                    used[index].reception = i;
                    index++; // 다음 사람
                }
            }
 
        }
        for (int i = 1; i <= K;++i) { // i : 고객 index
            if (used[i].reception == A && used[i].repair == B) {
                if (ans == -1) ans = i;
                else ans += i;
            }
        }
 
        cout << "#" << tc << ' ' << ans << endl;
    }
 
    return 0;
}