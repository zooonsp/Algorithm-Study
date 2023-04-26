#pragma warning (disable:4996)
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Time {
    int hour;	// hour: 시
    int minute;	// minute: 분
    int second;	// second: 초
};

long long timeLine[360'000];   // timeLine[i]: 00:00:00 부터 i초 경과 -> 최대 100 * 60 * 60
Time play, adv, ans;	// play: "죠르디"의 동영상 재생시간 길이, adv: 공익광고의 재생시간 길이, ans: 공익광고 시작 시간
int playTime, advTime, ansTime;	// playTime: "죠르디"의 동영상 재생시간 초 변환, advTime: 공익광고 재생시간 초 변환, ansTime: 공익광고 시작 시간 초 변환
long long cnt, ansCnt;	// cnt: 공익광고를 보고 있는 시청자의 수, ansCnt: 공익광고를 보는 가장 많은 시청자 수

std::string solution(std::string play_time, std::string adv_time, std::vector<std::string> logs) {
    char answer[10];	// answer: 공익광고 시작 시간

    sscanf(play_time.c_str(), "%d:%d:%d", &play.hour, &play.minute, &play.second);	// "죠르디"의 동영상 재생시간 길이 입력
    sscanf(adv_time.c_str(), "%d:%d:%d", &adv.hour, &adv.minute, &adv.second);	// 공익광고의 재생시간 길이 입력

    playTime = play.hour * 3600 + play.minute * 60 + play.second;	// "죠르디"의 동영상 재생시간 초로 변환
    advTime = adv.hour * 3600 + adv.minute * 60 + adv.second;	// 공익광고의 재생시간 초로 변환

    int logSize = logs.size();	// logSize: 시청자들이 해당 동영상을 재생했던 구간 정보의 수
    for (int log = 0; log < logSize; log++) {
        Time start, end;	// start: 시청 시작 시간, end: 시청 끝 시간
        int startTime, endTime;	// startTime: 시청 시작 시간 초 변환, endTime: 시청 끝 시간 초 변환
        sscanf(logs[log].c_str(), "%d:%d:%d-%d:%d:%d", &start.hour, &start.minute, &start.second, &end.hour, &end.minute, &end.second);	// 시청자들이 해당 동영상을 재생했던 구간 정보 입력
        
        startTime = start.hour * 3600 + start.minute * 60 + start.second;	// 시청 시작 시간 초 변환
        endTime = end.hour * 3600 + end.minute * 60 + end.second;	// 시청 끝 시간 초 변환

        timeLine[startTime] += 1;	// 시청 시작 +1
        timeLine[endTime] -= 1;	// 시청 끝 -1
    }

	for(int i=1; i<=playTime; i++){	// 처음부터 끝까지 순회하며 시청자 수 구함
		timeLine[i] += timeLine[i-1];
	}

    for (int i = 0; i <= advTime; i++) {	// -> 슬라이딩 윈도우를 구성할 때 주의할 점은 시청 끝 시간도 포함시켜야 함
        cnt += timeLine[i];	// 공익 광고를 보고 있는 시청자의 누적 재생 시간
    }
	ansTime = 0;
	ansCnt = cnt;	// 초기값 갱신

    for (int i = advTime + 1; i <= playTime; i++) {
        int startTime = i - advTime;	// startTime: 시청 시작 시간

        cnt += timeLine[i] - timeLine[startTime];

        if (ansCnt < cnt) {	// 공익광고를 보고 있는 시청자의 누적 재생 시간이 더 많다면 갱신
            ansTime = startTime + 1;
            ansCnt = cnt;
        }

    }

    ans.second = ansTime % 60;
    ans.minute = (ansTime / 60) % 60;
    ans.hour = ansTime / 3600;    

    sprintf(answer, "%02d:%02d:%02d", ans.hour, ans.minute, ans.second);	// 00:00:00 형태

    return answer;
}

int main() {

    std::string play_time = "99:59:59";
    std::string adv_time = "25:00:00";
    std::vector<std::string> logs = { "69:59:59-89:59:59", "01:00:00-21:00:00", "79:59:59-99:59:59", "11:00:00-31:00:00" };
    std::cout << solution(play_time, adv_time, logs);
	
    return 0;
}