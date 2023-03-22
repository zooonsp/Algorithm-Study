// 100 (완성본)
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

constexpr int SIZE = 2500;

vector<int> parent; // index : 원래 index, value : 어느 그룹에 속해 있는지
vector<string> values; // index : group, value : 그룹에 해당하는 값
vector<vector<int>> teams; // index : group , value : group에 속한 멤버들

void makeTeamEmpty(int index) {
	vector<int> emptyVec;
	teams[index].swap(emptyVec);
}

inline int coordToIndex(int r, int c) { // 좌표 -> index
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
	//parent[pb] = pa; // pa 밑에 pb 달기

	if (values[pa].empty() && !values[pb].empty()) { // pb(r2, c2)만 값을 가진 경우
		parent[pa] = pb; // pb 밑에 pa 달기
		string& target = values[pb];
		for (int& ap : teams[pa]) { // pa에 속한 팀들
			teams[pb].push_back(ap);
		}
		makeTeamEmpty(pa);
		values[pa] = "";
	}

	else { // otherwise
		parent[pb] = pa; // pa 밑에 pb 달기
		string& target = values[pa];
		for (int& bp : teams[pb]) { // pb에 속한 팀들
			teams[pa].push_back(bp);
		}
		makeTeamEmpty(pb);
		values[pb] = "";
	}

	return true;
}

vector<string> solution(vector<string> commands) {
	vector<string> answer;
	parent.assign(SIZE, -1);
	values.assign(SIZE, "");
	teams.assign(SIZE, vector<int>());
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
				int index = coordToIndex(r, c);
				index = Find(index);
				values[index] = command[3];
			}
			else { // UPDATE value1 value2
				vector<int> visited(SIZE, 0);
				for (int i{}; i < SIZE; ++i) {
					int idx = Find(i); // parent 갱신
					if (!visited[idx]) {
						if (values[idx] == command[1]) {
							values[idx] = command[2];
						}
						visited[idx] = 1;
					}
				}
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
			int parIndex = Find(index);
			string curValue = values[parIndex]; // copy

			for (int& t : teams[parIndex]) { // 해당 index에 속한 team들 순회
				parent[t] = -1;
				values[t] = "";
				if (t != parIndex) {
					makeTeamEmpty(t);
					teams[t].push_back(t);
				}
			}
			// 이걸 빼먹었어 ㅜㅜ
			makeTeamEmpty(parIndex);
			teams[parIndex].push_back(parIndex); // for문 안에서 하면 iterator 망가짐
			values[index] = curValue;
		}

		else if (command[0] == "PRINT") { // PRINT R C
			int r = stoi(command[1]), c = stoi(command[2]);
			int index = coordToIndex(r, c);
			index = Find(index);
			if (values[index].empty()) answer.push_back("EMPTY");
			else answer.push_back(values[index]);
		}
	}

	return answer;
}