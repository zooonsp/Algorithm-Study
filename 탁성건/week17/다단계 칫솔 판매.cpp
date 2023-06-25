#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral,
                     vector<string> seller, vector<int> amount) {
  const int N = enroll.size();
  const int M = seller.size();

  // 판매원에게 배분된 이익금의 총합
  vector<int> answer(N);

  unordered_map<string, int> um;
  vector<int> parent(N, -1);

  // 조직 구성원에게 번호 부여
  for (int i = 0; i < N; i++)
    um.insert({enroll[i], i});

  // 조직 구성원의 추천인 번호 등록
  for (int c = 0; c < N; c++) {
    if (referral[c] == "-")
      continue;

    int p = um[referral[c]];
    parent[c] = p;
  }

  // 판매원에서부터 시작해 상위로 이익 배분
  for (int i = 0; i < M; i++) {
    int now = um[seller[i]];
    int money = amount[i] * 100;

    while (now != -1 && money > 0) {
      int remain = money * 0.1f;
      answer[now] += money - remain; // 본인의 이익
      now = parent[now];             // 추천인으로 이동
      money = remain;                // 분배되는 이익
    }
  }

  return answer;
}
