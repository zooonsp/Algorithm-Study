#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility> // pair

using namespace std;
using pii = pair<int, int>;

/*
https://tech.kakao.com/2023/01/25/2023-kakao-recruitment-round-1/#elementor-toc__heading-anchor-6
많은 응시자들이 DSU(Disjoint Set Union, 서로소 집합) 자료구조를 활용해 이 문제를 풀었습니다. 
하지만 테스트케이스의 사이즈가 크지 않기 때문에 DSU와 같은 특별한 자료구조 없이도 문제 풀이가 가능합니다. 
여러 가지 풀이 중 비교적 구현이 간단한 풀이를 설명하겠습니다.

카카오 해설 내용대로 구현한 내용이지만 잘못 구현된 내용이 있을 수도 있습니다.
코드 제출 결과는 정상 통과합니다.
*/

pii merged[52][52]{};
// (r1, c1), (r2, c2) 두 위치에 대해 merged[r1][c1], merged[r2][c2]의 값이 같다면 두 위치는 병합된 한 셀로 판단
string content[52][52]{};
// 병합된 셀의 문자열 값을 저장하기 위해

void init() {
	for (int i{ 1 }; i < 51; ++i) {
		for (int j{ 1 }; j < 51; ++j) {
			merged[i][j] = make_pair(i,j);
			content[i][j] = "EMPTY";
		}
	}
}

vector<string> solution(vector<string> commands) {
	vector<string> answer;

	init();

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
				pii mergedCoord = merged[r][c];
				content[mergedCoord.first][mergedCoord.second] = command[3];
			}
			else { // UPDATE value1 value2
				for (int i{ 1 }; i < 51; ++i) {
					for (int j{ 1 }; j < 51; ++j) {
						if (content[i][j] == command[1]) {
							content[i][j] = command[2];
						}
					}
				}
			}
		}

		else if (command[0] == "MERGE") { // MERGE r1 c1 r2 c2
			int r1 = stoi(command[1]), c1 = stoi(command[2]);
			pii mergedCoord1 = merged[r1][c1]; // (x1, y1)
			
			int r2 = stoi(command[3]), c2 = stoi(command[4]);
			pii mergedCoord2 = merged[r2][c2]; // (x2, y2)

			for (int i{ 1 }; i < 51; ++i) {
				for (int j{ 1 }; j < 51; ++j) {
					if (merged[i][j] == mergedCoord2) {
						merged[i][j] = mergedCoord1;
					}
				}
			}
			if (content[mergedCoord1.first][mergedCoord1.second]=="EMPTY" && content[mergedCoord2.first][mergedCoord2.second]!="EMPTY") {
				content[mergedCoord1.first][mergedCoord1.second] = content[mergedCoord2.first][mergedCoord2.second];
			}
		}

		else if (command[0] == "UNMERGE") { // UNMERGE r c
			int r = stoi(command[1]), c = stoi(command[2]);
			pii mergedCoord = merged[r][c];
			string tmp = content[mergedCoord.first][mergedCoord.second];

			for (int i{ 1 }; i < 51; ++i) {
				for (int j{ 1 }; j < 51; ++j) {
					if (merged[i][j] == mergedCoord) {
						merged[i][j] = make_pair(i,j);
						content[i][j] = "EMPTY";
					}
				}
			}
			content[r][c] = tmp;
		}

		else if (command[0] == "PRINT") { // PRINT R C
			int r = stoi(command[1]), c = stoi(command[2]);
			pii mergedCoord = merged[r][c];
			answer.push_back(content[mergedCoord.first][mergedCoord.second]);
		}
	}

	return answer;
}