#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct fish {
    int row;
    int col;
    int id;
    int dir;
    int isAlive;

};
int MAP[5][5];
int row, col;
int dir, id;
vector<fish> v;
int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int point, sum, ans;

bool cmp(fish left, fish right) {
    if (left.id > right.id) return false;
    else if (left.id < right.id) return true;
    return false;
}

void input() {

    v.push_back({ -10,-10,-10,-10 });

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> id >> dir;
            v.push_back({ i, j, id, dir - 1, 1 });
            MAP[i][j] = id;
        }
    }
    sort(v.begin(), v.end(), cmp);
}

void move_fish() {

    int cursize = v.size(); // 17
    // ** 0은 상어의 위치 -> 0에 무조건 쓰레기값만 넣을게 아님
    for (int i = 1; i < cursize; i++) { // i는 현재 이동하려는 물고기의 id값
        fish now = v[i];

        if (now.isAlive == 1) {
            for (int j = 0; j < 8; j++) {

                int ndir = (now.dir + j) % 8; // ** 모듈러 활용 > 멤5
                int nr = now.row + dr[ndir];
                int nc = now.col + dc[ndir];

                if (nr < 0 || nc < 0 || nr >= 4 || nc >= 4) continue;

                if (MAP[nr][nc] == -1) continue; // 상어 마주쳤을때

                int next_id = MAP[nr][nc]; int now_id = MAP[now.row][now.col]; // now_id = i

                if (next_id > 0)
                {
                    swap(MAP[nr][nc], MAP[now.row][now.col]);
                    v[i].row = nr; v[i].col = nc;
                    v[next_id].row = now.row; v[next_id].col = now.col;
                    v[i].dir = ndir;
                    break;
                }
                else if (next_id == 0)
                {
                    MAP[nr][nc] = i;
                    MAP[now.row][now.col] = 0;
                    // v[i].row = now.row; v[i].col = now.col;
                    v[i].row = nr; v[i].col = nc;
                    v[i].dir = ndir;
                    break;
                }
            }
        }

        else if (now.isAlive == 0) continue;

    }
}

vector<int> path; // 상어가 먹은 물고기

void dfs() {

    // 임시 저장 창고
    int tmp_MAP[5][5] = { 0 };
    // fish shark = v[0];

    move_fish();
    vector<fish> tem_v(v.begin(), v.end());
    memcpy(tmp_MAP, MAP, sizeof(MAP));

    int flag = 0;
    for (int count = 1; count < 5; count++) {
        int snr = v[0].row + count * dr[v[0].dir];
        int snc = v[0].col + count * dc[v[0].dir];

        if (snr < 0 || snc < 0 || snr >= 4 || snc >= 4) break;
        if (MAP[snr][snc] == 0) continue;

        int next_shark_place = MAP[snr][snc];

        // point = next_shark_place; // 상어 점수 추가

        flag++;

        // 상어 이동(맵)
        MAP[snr][snc] = -1;
        MAP[v[0].row][v[0].col] = 0;
        sum += next_shark_place;
        // 상어 이동(벡터)
        v[0].col = snc;
        v[0].row = snr;
        v[0].dir = v[next_shark_place].dir;
        v[next_shark_place].isAlive = 0;

        path.push_back(next_shark_place);
        dfs();
        path.pop_back();

        v[next_shark_place].isAlive = 1;
        // 상어 복구(벡터)
        v[0].dir = tem_v[0].dir;
        v[0].row = tem_v[0].row;
        v[0].col = tem_v[0].col;
        sum -= next_shark_place;
        // 상어 복구(맵)
        memcpy(MAP, tmp_MAP, sizeof(tmp_MAP));
        // MAP[v[0].row][v[0].col] = -1;
    }

    if (flag == 0) {
        if (sum > ans)
            ans = sum;
        return;
    }
}



int main() {


    input();

    v[0].dir = v[MAP[0][0]].dir;
    v[0].col = v[MAP[0][0]].col;
    v[0].row = v[MAP[0][0]].row;
    v[MAP[0][0]].isAlive = 0;
    sum += MAP[0][0];
    MAP[0][0] = -1;

    //move_fish();

    dfs();

    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << MAP[i][j] << " ";
        }
        cout << "\n";
    }*/

    cout << ans;

    return 0;

}