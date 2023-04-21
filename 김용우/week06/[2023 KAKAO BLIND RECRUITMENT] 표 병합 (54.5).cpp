#include <string>
#include <vector>
using namespace std;

std::string TABLE[51][51];  // TABLE[r][c]: r행 c열의 값
int MARGE[51][51];  // MARGE[r][c]: r행 c열의 병합 값
int margeNum = 1;	// margeNum: 병합 값
std::vector<string> answer;

vector<string> solution(vector<string> commands) {
    // 초기화
    for(int j = 0; j <= 50; j++){
        for(int i = 0; i<= 50; i++){
            TABLE[j][i] = "";
            MARGE[j][i] = 0;
        }
    }
    
    for(int com = 0; com < commands.size(); com++){   // 명령어 실행 commands[com]
        std::vector<std::string> cur_command;
        std::string result;
        int position;
        int cur_position = 0;
        while((position = commands[com].find(" ", cur_position)) != std::string::npos){
            int len = position - cur_position;
            result = commands[com].substr(cur_position, len);
            cur_command.push_back(result);
            cur_position = position + 1;
        }
        result = commands[com].substr(cur_position);
        cur_command.push_back(result);
        
        if(cur_command[0] == "UPDATE"){ // UPDATE
            if(cur_command.size() == 4){    // UPDATE r c value
                int r = std::stoi(cur_command[1]);
                int c = std::stoi(cur_command[2]);
                std::string value = cur_command[3];
                if(MARGE[r][c] != 0){   // (r, c) 셀이 병합되어 있다면
                    int num = MARGE[r][c];  // num: 병합 번호
                    for(int j = 1; j <= 50; j++) {
                        for(int i = 1; i <= 50; i++) {
                            if(MARGE[j][i] != num) continue;    // 병합된 셀 아니면 continue
                            TABLE[j][i] = value;    // 병합된 셀은 value로 값 변경
                        }
                    }
                } else {    // (r, c) 셀이 병합되어 있지 않다면
                    TABLE[r][c] = value;
                }
            }
            else if(cur_command.size() == 3){    // UPDATE value1 value2
                std::string value1 = cur_command[1];
                std::string value2 = cur_command[2];
                for(int j = 1; j <= 50; j++){
                    for(int i = 1; i <= 50; i++){
                        if(TABLE[j][i] == value1){  // value1을 값으로 가지고 있는 모든 셀을 선택
                            TABLE[j][i] = value2;   // 선택한 셀의 값을 value2로 바꿈
                        }
                    }
                }
            }            
        }
        if(cur_command[0] == "MERGE"){  // MERGE r1 c1 r2 c2
            int r1 = std::stoi(cur_command[1]);
            int c1 = std::stoi(cur_command[2]);
            int r2 = std::stoi(cur_command[3]);
            int c2 = std::stoi(cur_command[4]);
            std::string value;
            if(r1 == r2 && c1 == c2) continue;  // 선택한 두 위치의 셀이 같은 셀인 경우 무시
            
            if(TABLE[r1][c1] == "" && TABLE[r2][c2] != "") { // (r2, c2) 셀에만 값이 있음
                value = TABLE[r2][c2];  // 값은 (r2, c2) 셀에 있는 값을 갖게 됨
            } else {   // (r1, c1) 셀만 값이 있을 경우, 두 셀 모두 값을 가지고 있을 경우
                value = TABLE[r1][c1];  // 값은 (r1, c1)에 있는 값을 갖게 됨
            }
            
            int num1 = MARGE[r1][c1], num2 = MARGE[r2][c2]; // num1: (r1, c1) 셀의 병합 값, num2: (r2, c2) 셀의 병합 값
            
            if(num1 == 0 && num2 == 0){ // 두 셀 모두 병합된 셀 없으면 -> 두 셀 병합 값 부여
                MARGE[r1][c1] = margeNum;
                MARGE[r2][c2] = margeNum;
                margeNum++;
            } else if(num1 != 0 && num2 == 0){  // (r1, c1) 셀이 병합되어 있다면
                MARGE[r2][c2] = num1;
            } else if(num1 == 0 && num2 != 0){  // (r2, c2) 셀이 병합되어 있다면
                MARGE[r1][c1] = num2;
            } else if(num1 != 0 && num2 != 0){  // 두 셀 모두 병합된 셀 있다면
                for(int j = 0; j <= 50; j++){
                    for(int i = 0; i <= 50; i++){
                        if(MARGE[j][i] == num1) // (r1, c1)의 병합 값을 갖고 있는 모든 셀에 대하여
                            MARGE[j][i] = num2; // (r2, c2)의 병합 값을 갖도록 함
                    }
                }
            }            
            
            int num = MARGE[r1][c1];    // num: (r1, c1) 셀의 병합 값
            for(int j = 1; j <= 50; j++){
                for(int i = 1; i <= 50; i++){
                    if(MARGE[j][i] == num)  // 같은 병합 값을 갖고 있는 셀에 대하여
                        TABLE[j][i] = value;    // 값 갱신
                }
            }
            
        }
        if(cur_command[0] == "UNMERGE"){    // UNMERGE r c
            int r = std::stoi(cur_command[1]);
            int c = std::stoi(cur_command[2]);
            int num = MARGE[r][c];  // num: (r, c) 셀의 병합 값
            for(int j = 1; j <= 50; j++){
                for(int i = 1; i <= 50; i++){
                    if(MARGE[j][i] != num) continue;    // (r, c) 셀과 다른 병합 값 셀은 continue
                    MARGE[j][i] = 0;    // 같은 병합 값을 갖는 셀의 병합을 해지
                    if(j == r && i == c) continue;  // (r, c) 셀은 값 보존
                    TABLE[j][i] = "";   // 다른 셀은 값 프로그램 실행 초기의 상태로 돌아감
                }
            }
        }
        if(cur_command[0] == "PRINT"){  // PRINT
            int r = std::stoi(cur_command[1]);
            int c = std::stoi(cur_command[2]);
            if(TABLE[r][c] == "")   // 선택한 셀이 비어있는 경우
                answer.push_back("EMPTY");
            else    // 선택한 셀의 값이 있는 경우
                answer.push_back(TABLE[r][c]);
        }
    }
    
    return answer;
}