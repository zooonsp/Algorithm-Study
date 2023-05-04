#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Time {
    string time_str;
    int time_second;
    Time(string time_str_): time_str(time_str_), time_second(0) {
        time_second += (time_str[0] - '0') * 10;
        time_second += time_str[1] - '0';
        time_second *= 60;
        time_second += (time_str[3] - '0') * 10;
        time_second += time_str[4] - '0';
        time_second *= 60;
        time_second += (time_str[6] - '0') * 10;
        time_second += time_str[7] - '0';
    }
    Time(int time_second_): time_str(""), time_second(time_second_) {
        char time_char[9];
        time_char[8] = '\0';
        time_char[7] = (time_second % 10) + '0';
        time_char[6] = ((time_second % 60) / 10) + '0';
        time_char[5] = ':';
        time_second /= 60;
        time_char[4] = (time_second % 10) + '0';
        time_char[3] = ((time_second % 60) / 10) + '0';
        time_char[2] = ':';
        time_second /= 60;
        time_char[1] = (time_second % 10) + '0';
        time_char[0] = (time_second / 10) + '0';
        time_str = string(time_char);
    }
};

struct TimeSegment {
    int start;
    int end;
    bool operator<(const TimeSegment &rhs) {
        if(start != rhs.start) {return start < rhs.start;}
        return end < rhs.end;
    }
};

int play_time_seconds;
int adv_time_seconds;
vector<long long> watches;
vector<int> candidates;

void parse_data(string play_time, string adv_time, vector<string> &logs) {
    play_time_seconds = Time(play_time).time_second;
    adv_time_seconds = Time(adv_time).time_second;
    watches = vector<long long>(play_time_seconds + 1, 0);
    candidates = vector<int>();
    candidates.reserve((logs.size() << 1) + 1);
    vector<bool> candidates_visited(play_time_seconds + 1, false);
    for(string &log : logs) {
        Time start_time = Time(log.substr(0, 8));
        Time end_time = Time(log.substr(9, 8));
        TimeSegment watch_time{start_time.time_second, end_time.time_second};
        watches[watch_time.start] += 1;
        watches[watch_time.end] -= 1;
        int candidate[2] = {watch_time.start, watch_time.end - adv_time_seconds};
        if(0 <= candidate[0] && !candidates_visited[candidate[0]]) {candidates.push_back(candidate[0]); candidates_visited[candidate[0]] = true;}
        if(0 <= candidate[1] && !candidates_visited[candidate[1]]) {candidates.push_back(candidate[1]); candidates_visited[candidate[1]] = true;}
    }
    long long sum = 0LL;
    for(int it = 0; it <= play_time_seconds; ++it) {
        sum += watches[it];
        watches[it] = sum;
    }
    candidates.push_back(play_time_seconds - adv_time_seconds);
    sort(candidates.begin(), candidates.end());
    int candidates_size = candidates.size();
    for(int it = 0; it < candidates_size; ++it) {
        if(0 <= candidates[it]) {
            while(0 <= --it) {candidates[it] = candidates[it + 1];}
            break;
        }
    }
    for(int rit = candidates_size - 1; 0 <= rit; --rit) {
        if(candidates[rit] + adv_time_seconds <= play_time_seconds) {
            while(++rit < candidates_size) {candidates[rit] = candidates[rit - 1];}
            break;
        }
    }
}

long long new_window(int start) {
    long long value = 0;
    for(int it = 0; it < adv_time_seconds; ++it) {
        value += watches[start + it];
    }
    return value;
}

long long slide_window(long long value, int position, int distance) {
    for(int it = 0; it < distance; ++it) {value -= watches[position + it];}
    for(int it = 0; it < distance; ++it) {value += watches[position + adv_time_seconds + it];}
    return value;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    parse_data(play_time, adv_time, logs);
    long long max_value = new_window(0);
    int max_position = 0;
    long long value = max_value;
    int previous_position = 0;
    const int half_adv_time_seconds = (adv_time_seconds + 1) >> 1;
    for(int &position : candidates) {
        if(previous_position == position) {continue;}
        if(half_adv_time_seconds <= (position - previous_position + 1)) {value = new_window(position);}
        else {value = slide_window(value, previous_position, position - previous_position);}
        if(max_value < value) {
            max_value = value;
            max_position = position;
        }
        previous_position = position;
    }
    return Time(max_position).time_str;
}