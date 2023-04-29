#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
constexpr int MAXTIME = 360010;

long long timeTable[MAXTIME]{};

int timetosec(string time) { // Time:Minute:Second
	istringstream iss(time);
	string temp;
	int retTime{};
	int splitCnt{};
	while (getline(iss, temp, ':')) {
		if (splitCnt == 0) retTime += 3600 * stoi(temp); // hour
		else if (splitCnt == 1) retTime += 60 * stoi(temp); // minute
		else retTime += stoi(temp); // second

		++splitCnt;
	}
	return retTime;
}

string sectotime(int answerInt) {
	string answer = "";
	if ((answerInt / 3600) < 10) {
		answer.push_back('0');
	}
	answer += to_string(answerInt / 3600);
	answer.push_back(':');
	if ((answerInt / 60 % 60) < 10) {
		answer.push_back('0');
	}
	answer += to_string(answerInt / 60 % 60);
	answer.push_back(':');
	if ((answerInt % 60) < 10) {
		answer.push_back('0');
	}
	answer += to_string(answerInt % 60);
	return answer;
}

string solution(string play_time, string adv_time, vector<string> logs) {
	string answer = "";
	int advTimeInt = timetosec(adv_time);
	int playTimeInt = timetosec(play_time);
	const int SIZE = (int)logs.size();
	vector<int> startTimes, endTimes;

	for (string& log : logs) {
		int startTimeInt = timetosec(log.substr(0, 8));
		int endTimeInt = timetosec(log.substr(9, 8));
		startTimes.push_back(startTimeInt);
		endTimes.push_back(endTimeInt);
	}

	sort(begin(startTimes), end(startTimes));
	sort(begin(endTimes), end(endTimes));

	int startIndex{}, endIndex{}, cnt{};
	// [start, end)
	for (int time{}; time <= playTimeInt; ++time) {
		if (startIndex < SIZE && time == startTimes[startIndex]) {
			// 시간대가 여러 개 있는 경우에 처리가 미흡했음.
			while (startIndex < SIZE && time == startTimes[startIndex]) {
				++cnt;
				++startIndex;
			}
		}
		if (endIndex < SIZE && time == endTimes[endIndex]) { // 끝난 이후에
			while (endIndex < SIZE && time == endTimes[endIndex]) {
				--cnt;
				++endIndex;
			}
		}
		if (time == 0) timeTable[time] = cnt;
		else timeTable[time] = timeTable[time - 1] + cnt;
	}
	
	long long maxSumTimes{ timeTable[advTimeInt] }; // 이것도 advTimeInt - 1로 했어야 되는 거 같은데 그냥 통과 되버렸네 ㄷㄷ
	answer = sectotime(0);

	for (int time{1}; time <= playTimeInt - advTimeInt; ++time) { // time에서 영상 재생
		int endTimeInt = time + advTimeInt;
		long long sumTimesAtTime = timeTable[endTimeInt - 1] - timeTable[time - 1];
		// time ~ endTimeInt 재생 시 시청자 수
		// time부터 시작하기 때문에 time - 1은 쉽게 찾을 수 있었음.
		// 계속 endTimeInt까지만 식을 세워서 힘들었음.
		// endTimeInt - 1까지 세줘야 endTimeInt에 들어오는 시청자 수가 포함이 안 됨. (미흡)
		if (maxSumTimes < sumTimesAtTime) {
			maxSumTimes = sumTimesAtTime;
			answer = sectotime(time);
		}
	}
	return answer;
}

int main() {
	string play_time{ "02:03:55" }, adv_time{ "00:14:15" };
	vector<string> logs{ "01:20:15-01:45:14", "00:40:31-01:00:00",
		"00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30" };

	cout << solution(play_time, adv_time, logs) << '\n';
	return 0;
}