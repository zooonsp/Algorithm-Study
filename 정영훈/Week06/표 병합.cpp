#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parent; // index : 원래 index, value : 어느 그룹에 속해 있는지
vector<string> values; // index : group, value : 그룹에 해당하는 값

int Find(int a) {
    if (parent[a] == -1) return a;
    return parent[a] = Find(parent[a]);
}

bool Merge(int a, int b) {
    int pa = Find(a);
    int pb = Find(b);

    if (pa == pb) return false;

    parent[pb] = pa; // pa 밑에 pb 달기

    if (!values[pa].empty() && !values[pb].empty()) { // 둘 다 값을 가진 경우 -> a위치로
        values[pb] = "";
    }
    else if (!values[pb].empty()) { // pb(r2,c2)만 값을 가진 경우
        values[pa] = values[pb];
        values[pb] = "";
    }
    else { // pa(r1,c1)만 값을 가진 경우 또는 둘 다 ""인 경우
        values[pb] = "";
    }

    return true;
}

inline int coordToIndex(int r, int c) { // 좌표 -> index
    r--; c--;
    return (r * 50 + c);
}

int findIndex(string& r, string& c) { // 해당 좌표가 속한 index까지 반환해주는 함수
    int rInt = stoi(r);
    int cInt = stoi(c);
    int index = coordToIndex(rInt, cInt);
    return Find(index);
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;
    parent.assign(2500, -1);
    values.assign(2500, "");

    for (string& co : commands) {
        istringstream iss(co);
        string in;
        vector<string> command;
        while (getline(iss, in, ' ')) {
            command.push_back(in);
        }

        if (command[0] == "UPDATE") {
            if (command.size() == 4) { // UPDATE r c value
                int index = findIndex(command[1], command[2]);
                values[index] = command[3];
            }
            else { // UPDATE value1 value2
                for (string& value : values) {
                    if (value == command[1]) {
                        value = command[2];
                    }
                }
            }
        }

        else if (command[0] == "MERGE") { // MERGE r1 c1 r2 c2
            int index1 = findIndex(command[1], command[2]);
            int index2 = findIndex(command[3], command[4]);
            Merge(index1, index2);
        }

        else if (command[0] == "UNMERGE") { // UNMERGE r c
            int index = coordToIndex(stoi(command[1]), stoi(command[2])); // 우리 목표
            int realIndex = Find(index); // 목표가 속한 인덱스
            string curValue = values[realIndex]; // copy
            values[realIndex] = ""; // 밑에 거랑 순서 바꾸면 안 됨
            values[index] = curValue;
            
            vector<int> deleteList;
            for (int i{ 0 }; i < 2500; ++i) {
                if (Find(i) == realIndex) {
                    deleteList.push_back(i); // 여기서 바로 제거 하면 제대로 된 부모를 못 찾는 애가 생김
                }
            }
            // 따라서 다 찾은 후 한 번에 원래 대로 복구
            for (int& i : deleteList) {
                parent[i] = -1;
            }
        }

        else if (command[0] == "PRINT") { // PRINT R C
            int index = findIndex(command[1], command[2]);
            if (values[index].empty()) answer.push_back("EMPTY");
            else answer.push_back(values[index]);
        }
    }

    return answer;
}