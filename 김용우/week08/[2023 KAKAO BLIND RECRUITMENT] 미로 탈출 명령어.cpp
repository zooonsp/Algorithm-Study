#include <string>
#include <vector>
#include <cmath>

using namespace std;

int dirX[] = {1, 0, 0, -1};
int dirY[] = {0, -1, 1, 0};

string solution(int n, int m, int x, int y, int r, int c, int k) {
    std::string answer = "";
    int distance = std::abs(x-r) + std::abs(y-c);

    if(k < distance || k % 2 != distance % 2)
        return "impossible";

    for(int i = 1; i <= k; i++) {
        for(int d = 0; d < 4; d++) {
            int nextX = x + dirX[d];
            int nextY = y + dirY[d];

            if(nextX < 1 || nextY < 1 || nextX > n || nextY > m) continue;            
            if(k - i < std::abs(r - nextX) + std::abs(c - nextY)) continue;
            
            if(d==0) answer += 'd';
            if(d==1) answer += 'l';
            if(d==2) answer += 'r';
            if(d==3) answer += 'u';

            x = nextX;
            y = nextY;

            break;
        }
    }
    return answer;
}