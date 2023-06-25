#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral,
                     vector<string> seller, vector<int> amount) {
  const int N = enroll.size();
  const int M = seller.size();

  vector<int> answer(N);

  unordered_map<string, int> um;
  vector<int> parent(N, -1);

  for (int i = 0; i < N; i++)
    um.insert({enroll[i], i});

  for (int c = 0; c < N; c++) {
    if (referral[c] == "-")
      continue;

    int p = um[referral[c]];
    parent[c] = p;
  }

  for (int i = 0; i < M; i++) {
    int now = um[seller[i]];
    int money = amount[i] * 100;

    while (now != -1 && money > 0) {
      int remain = money * 0.1f;
      answer[now] += money - remain;
      now = parent[now];
      money = remain;
    }
  }

  return answer;
}
