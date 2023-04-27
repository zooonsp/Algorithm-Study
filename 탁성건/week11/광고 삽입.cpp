#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int time2sec(const string &t) {
  int sec = 0;

  for (int i = 0; i < t.size(); i += 3)
    sec = sec * 60 + stoi(t.substr(i, 2));

  return sec;
}

string sec2time(int sec) {
  ostringstream oss;
  oss << setfill('0');

  for (int i = 60 * 60; i > 0; i /= 60) {
    oss << ':' << setw(2) << to_string(sec / i);
    sec %= i;
  }

  return oss.str().substr(1);
}

string solution(string playTime, string advTime, vector<string> logs) {
  int playSec = time2sec(playTime), advSec = time2sec(advTime);
  vector<int> viewCnt(playSec);

  for (string &log : logs) {
    int startSec = time2sec(log.substr(0, 8));
    int endSec = time2sec(log.substr(9));

    for (int i = startSec; i < endSec; i++)
      viewCnt[i]++;
  }

  long long sum = 0, maxSum = 0;
  int left = 0, right = advSec - 1, ans = 0;

  for (int i = 0; i < right; i++)
    sum += viewCnt[i];

  while (right < playSec) {
    sum += viewCnt[right];

    if (maxSum < sum) {
      maxSum = sum;
      ans = left;
    }

    sum -= viewCnt[left];

    right++;
    left++;
  }

  return sec2time(ans);
}
