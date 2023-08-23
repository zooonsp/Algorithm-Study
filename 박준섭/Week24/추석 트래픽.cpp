#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<string> lines) {
    int answer = 0;
    
    vector<int> startVector, endVector;
    
    int linesLength = lines.size();
    for (int i{}; i < linesLength; ++i) {
        int h, m, s, ms, processingTime;
                
        // ms 단위로 변경
        h = stoi(lines[i].substr(11, 2)) * 3600000;
        m = stoi(lines[i].substr(14, 2)) * 60000;
        s = stoi(lines[i].substr(17, 2)) * 1000;
        ms = stoi(lines[i].substr(20, 3));
        processingTime = stof(lines[i].substr(24, 5)) * 1000;
        
        // 시작 시간 저장
        startVector.push_back(h + m + s + ms - processingTime + 1);
        // 끝나는 시간 저장
        endVector.push_back(h + m + s + ms);
    }

    for (int i {}; i < linesLength; ++i) {
        
        // 처리시간은 시작시간과 끝시간을 포함하기에 기준을
        // 끝시간을 기준으로 1초 동안의 시간들을 비교
        int nowEndTime = endVector[i] + 1000;
        int count = 0;
        
        for (int j = i; j < linesLength; ++j) {
            if (startVector[j] <= nowEndTime) count++;
        }
        
        answer = max(answer, count);
    }
    
    return answer;
}
