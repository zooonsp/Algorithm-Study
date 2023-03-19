// 13, 14, 16, 19 틀림
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
놓친 부분)
UPDATE
UNMERGE
두 부분에서 미리 만들어 놓은 teams와 um을 통해서 계산하도록 구현이 되어 있었는데,
제대로 된 parent를 찾지 못하는 경우들이 있었던 것 같음.

이를 해결함.
*/

vector<int> parent; // index : 원래 index, value : 어느 그룹에 속해 있는지
vector<string> values; // index : group, value : 그룹에 해당하는 값
vector<vector<int>> teams; // index : group , value : group에 속한 멤버들
unordered_map<string, vector<int>> um; // key : string, value : 해당 key를 값으로 가진 그룹

inline int coordToIndex(int r,int c){ // 좌표 -> index
    r--; c--;
    return (r * 50 + c);
}

int Find(int a) {
    if (parent[a] == -1) return a;
    return parent[a] = Find(parent[a]);
}

bool Merge(int a, int b) {
    int pa = Find(a);
    int pb = Find(b);

    if (pa == pb) return false;

    if (!values[pa].empty() && !values[pb].empty()) { // 둘 다 값을 가진 경우 -> a위치로
        parent[pb] = pa; // pa 밑에 pb 달기
        string& target = values[pa];
        for (int& bp : teams[pb]) { // pb에 속한 팀들
            um[target].push_back(bp);
            teams[pa].push_back(bp);
        }
        vector<int> emptyVec;
        um[values[pb]].swap(emptyVec);
        vector<int> emptyVec1;
        teams[pb].swap(emptyVec1);
        values[pb] = "";
    }
    else if (!values[pb].empty()) { // pb(r2, c2)만 값을 가진 경우
        parent[pa] = pb; // pb 밑에 pa 달기
        string& target = values[pb];
        for (int& ap : teams[pa]) { // pa에 속한 팀들
            um[target].push_back(ap);
            teams[pb].push_back(ap);
        }
        vector<int> emptyVec;
        vector<int> emptyVec1;
        teams[pa].swap(emptyVec);
        um[values[pa]].swap(emptyVec1);
        values[pa] = "";
    }
    else { // pa(r1,c1)가 값을 가진 경우 (둘 다 비어 있는 경우는 상관 없을 듯?)
        parent[pb] = pa; // pa 밑에 pb 달기
        string& target = values[pa];
        for (int& bp : teams[pb]) {
            um[target].push_back(bp);
            teams[pa].push_back(bp);
        }
        vector<int> emptyVec;
        vector<int> emptyVec1;
        um[values[pb]].swap(emptyVec); // 기존 그룹에 있는 애들 초기화
        teams[pb].swap(emptyVec1);
        values[pb] = "";
    }

    return true;
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;
    parent.assign(2500, -1);
    values.assign(2500, "");
    teams.assign(2500, vector<int>());
    for (int i = 0; i < 2500; ++i) {
        teams[i].push_back(i); // 자기 자신
    }

    for (string& co : commands) {
        istringstream iss(co);
        string in;
        vector<string> command;
        while (getline(iss, in, ' ')) {
            command.push_back(in);
        }

        if (command[0] == "UPDATE") {
            if (command.size() == 4) { // UPDATE r c value
                int r = stoi(command[1]), c = stoi(command[2]);
                int index = coordToIndex(r,c);
                index = Find(index);
                values[index] = command[3];
                um[command[3]].push_back(index); // 해당 value를 가진 팀 목록에 index 추가
            }
            else { // UPDATE value1 value2
                for (int& gr : um[command[1]]) { // command[1](value1)을 값으로 가지는 팀들 순회
                    if (values[gr] == command[1]) { // 진짜면
                        values[gr] = command[2];
                        um[command[2]].push_back(gr);
                    }
                }
                vector<int> emptyVec; // empty vector
                um[command[1]].swap(emptyVec);
            }
        }

        else if (command[0] == "MERGE") { // MERGE r1 c1 r2 c2
            int r1 = stoi(command[1]), c1 = stoi(command[2]);
            int index1 = coordToIndex(r1, c1);
            int r2 = stoi(command[3]), c2 = stoi(command[4]);
            int index2 = coordToIndex(r2, c2);
            Merge(index1, index2);
        }

        else if (command[0] == "UNMERGE") { // UNMERGE r c
            int r = stoi(command[1]), c = stoi(command[2]);
            int index = coordToIndex(r, c);
            index = Find(index);
            string curValue = values[index]; // copy
            for (int& t : teams[index]) { // 해당 index에 속한 team들 순회
                parent[t] = -1;
                values[t] = "";
                if (t != index) teams[t].push_back(t);
            }
            vector<int> emptyVec; // empty vector
            um[curValue].swap(emptyVec);
            index = coordToIndex(r, c);
            teams[index].push_back(index);
            um[curValue].push_back(index);
            values[index] = curValue;
        }

        else if(command[0] == "PRINT") { // PRINT R C
            int r = stoi(command[1]), c = stoi(command[2]);
            int index = coordToIndex(r, c);
            index = Find(index);
            if (values[index].empty()) answer.push_back("EMPTY");
            else answer.push_back(values[index]);
        }
    }

    return answer;
}