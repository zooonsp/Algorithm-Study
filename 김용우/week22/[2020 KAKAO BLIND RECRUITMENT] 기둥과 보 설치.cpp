#include <string>
#include <vector>

enum structure_type {   // 설치 또는 삭제할 구조물의 종류
    pillar, // pillar: 기둥 -> 0
    beam,   // beam: 보 -> 1
};

enum structure_state {  // 구조물을 설치할 지, 혹은 삭제할 지
    del,    // del: 삭제 -> 0
    add,    // add: 설치 -> 1
};

struct Coordinate { // 좌표
    int x, y;   // x, y: 좌표값
};

std::vector<std::vector<std::vector<bool>>> MAP;    // MAP[i][j][k]: (i, j)에 설치되어 있는 구조물의 상태 -> k == 0 ? 기둥 : 보 -> true면 설치된 상태

bool addItem(int n, Coordinate coordi, int type);    // 설치 작업 -> n: 2차원 벽면의 크기, coordi: 좌표, type: 구조물의 종류
bool delItem(int n, Coordinate coordi, int type); // 삭제 작업 -> n: 2차원 벽면의 크기, coordi: 좌표, type: 구조물의 종류
void sol(int n, std::vector<std::vector<int>>& build_frame);    // 풀이 -> n: 2차원 벽면의 크기, build_frame: 작업
void init(int n);   // 초기화 -> n: 2차원 벽면의 크기

bool addItem(int n, Coordinate coordi, int type) {
    
    if(type == structure_type::pillar) {    // 기둥 설치
        if(coordi.y == 0) return true;  // 바닥 위에 있는 경우 언제나 설치 가능
        if(coordi.x > 0 && MAP[coordi.x - 1][coordi.y][structure_type::beam]) return true;  // 보의 오른쪽 끝에 있는 경우 설치 가능
        if(coordi.y < n && MAP[coordi.x][coordi.y][structure_type::beam]) return true;  // 보의 왼쪽 끝에 있는 경우 설치 가능
        if(coordi.y > 0 && MAP[coordi.x][coordi.y - 1][structure_type::pillar]) return true;    // 다른 기둥 위에 있는 경우 설치 가능
    }
    else {  // 보 설치
        if(coordi.y > 0 && MAP[coordi.x][coordi.y - 1][structure_type::pillar]) return true;    // 왼쪽 아래에 기둥이 있는 경우 설치 가능
        if(coordi.x < n && coordi.y > 0 && MAP[coordi.x + 1][coordi.y - 1][structure_type::pillar]) return true;    // 오른쪽 아래에 기둥이 있는 경우 설치 가능
        if(coordi.x > 0 && coordi.x < n && MAP[coordi.x - 1][coordi.y][structure_type::beam] && MAP[coordi.x + 1][coordi.y][structure_type::beam]) return true; // 양쪽에 보가 있는 경우 설치 가능
    }
    
    return false;
}

bool delItem(int n, Coordinate coordi, int type) {
    
    MAP[coordi.x][coordi.y][type] = false;
    
    if(type == structure_type::pillar) {    // 기둥 삭제
        if(coordi.y < n && MAP[coordi.x][coordi.y + 1][structure_type::pillar] && !addItem(n, {coordi.x, coordi.y + 1}, structure_type::pillar)) return false;  // 위에 기둥이 있을 경우 설치 가능?
        if(coordi.y < n && MAP[coordi.x][coordi.y + 1][structure_type::beam] && !addItem(n, {coordi.x , coordi.y + 1}, structure_type::beam)) return false; // 위에 보가 있을 경우 설치 가능?
        if(coordi.x > 0 && coordi.y < n && MAP[coordi.x - 1][coordi.y + 1][structure_type::beam] && !addItem(n, {coordi.x - 1, coordi.y + 1}, structure_type::beam)) return false;  // 위에 보가 있을 경우 설치 가능?
    }
    else {  // 보 삭제
        if(MAP[coordi.x][coordi.y][structure_type::pillar] && !addItem(n, coordi, structure_type::pillar)) return false;    // 아래에 기둥이 있을 경우 설치 가능?
        if(coordi.x < n && MAP[coordi.x + 1][coordi.y][structure_type::pillar] && !addItem(n, {coordi.x + 1, coordi.y}, structure_type::pillar)) return false;  // 오른쪽에 기둥이 있을 경우 설치 가능?
        if(coordi.x > 0 && MAP[coordi.x - 1][coordi.y][structure_type::beam] && !addItem(n, {coordi.x - 1, coordi.y}, structure_type::beam)) return false;  // 왼쪽에 보가 있을 경우 설치 가능?
        if(coordi.x < n && MAP[coordi.x + 1][coordi.y][structure_type::beam] && !addItem(n, {coordi.x + 1, coordi.y}, structure_type::beam)) return false;  // 오른쪽에 보가 있을 경우 설치 가능?
    }
    
    return true;
}

void sol(int n, std::vector<std::vector<int>>& build_frame) {
    
    for(const std::vector<int>& frame : build_frame){   // frame: 진행할 작업
        Coordinate coordi = {frame[0], frame[1]};   // coordi: 좌표
        int type = frame[2];    // type: 설치 또는 삭제할 구조물의 종류
        int state = frame[3];   // state: 구조물을 설치할 지, 혹은 삭제할 지
        
        if(state == structure_state::del) { // 삭제
            if(!delItem(n, coordi, type)) MAP[coordi.x][coordi.y][type] = true; // 삭제 못함
        }
        else {  // 설치
            if(addItem(n, coordi, type)) MAP[coordi.x][coordi.y][type] = true;  // 설치 함
        }
    }
    
    return;
}

void init(int n) {
    
    MAP.assign(n + 1, std::vector<std::vector<bool>>(n + 1, std::vector<bool>(2, false)));
    
    return;
}

std::vector<std::vector<int>> solution(int n, std::vector<std::vector<int>> build_frame) {
    std::vector<std::vector<int>> answer;
    
    init(n);
    
    sol(n, build_frame);
    
    for(int x=0; x<=n; ++x){
        for(int y=0; y<=n; ++y){
            if(MAP[x][y][structure_type::pillar]) answer.push_back({x, y, structure_type::pillar});
            if(MAP[x][y][structure_type::beam]) answer.push_back({x, y, structure_type::beam});
        }
    }    
    
    return answer;
}