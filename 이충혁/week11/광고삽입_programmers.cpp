#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_SEC = 363636; // 3600 * 100시간

int ab_cnt[MAX_SEC]; // 해당 시간의 광고 카운트
int ab_sum[MAX_SEC]; // 해당 시간 광고 prefix sum

// 1. 시간이 다돌아도 360000 안되니까 각 시간마다 광고 몇개 하는지 센다.
// 2. 시간 마다 광고 갯수 누적합 구해놓기
// 3. 광고 시간 맞춰서 완전 탐색

int strTosec(string s)
{
    int ret;

    ret = stoi(s.substr(0, 2)) * 3600 + stoi(s.substr(3, 2)) * 60 + stoi(s.substr(6, 2));

    return ret;
}

string secTostr(int sec)
{
    string ret = "";
  
    ret += to_string(sec / 36000);
    ret += to_string((sec % 36000) / 3600);
    ret += ":";
    ret += to_string((sec % 3600) / 600);
    ret += to_string((sec % 600) / 60);
    ret += ":";
    ret += to_string((sec % 60) / 10);
    ret += to_string((sec % 10));

    return ret;
}



string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";

    int broad_time = strTosec(play_time); // 총 방송 시간 정수값
    int ad_time = strTosec(adv_time); // 광고 시간
    int max_time = 0; // 최대 누적 광고시간
    int ans_int = 0;

    // 1. 시간마다 광고 카운트
    for (auto log : logs) 
    { 
        int st = strTosec(log.substr(0, 8));
        int ed = strTosec(log.substr(9));

        for (int i = st; i < ed; i++) {
            ab_cnt[i]++;
        }
    }

    // 2. 광고 카운트 누적합
    ab_sum[0] = ab_cnt[0];
    for (int i = 1; i < broad_time; i++)
    {
        ab_sum[i] = ab_cnt[i] + ab_sum[i - 1];
    }

    // 3. 누적합 에서 제일 큰 값 찾기
    max_time = ab_sum[ad_time - 1];
    ans_int = 0;
    for (int i = 0; i < broad_time - ad_time; i++)
    {
        int temp = ab_sum[i + ad_time] - ab_sum[i];
        if (max_time < temp)
        {
            max_time = temp;
            ans_int = i + 1;
        }
    }

    answer = secTostr(ans_int);

    return answer;
}

int main()
{
    string ans;
    ans = solution("50:00:00", "50:00:00", { "15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45" });

    /*
    ans = solution("99:59:59", "25:00:00", 	{"69:59:59-89:59:59", "01:00:00-21:00:00",
        "79:59:59-99:59:59", "11:00:00-31:00:00"});
            ans = solution("02:03:55", "00:14:15", { "01:20:15-01:45:14", "00:40:31-01:00:00",
        "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30" });
    */
    cout << ans;
    return 0;
}