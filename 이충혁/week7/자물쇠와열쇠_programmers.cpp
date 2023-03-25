#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MAT_MAX = 55;

struct coordi {
    int y, x;
};

int key_size, lock_size;
int lock_hole = 0; // 자물쇠 홈 갯수

// 끼운 한가지 케이스에 대해 열리는지
bool insert_one(coordi now, vector<vector<int>>& key, vector<vector<int>>& lock)
{
    int fill_hole = 0; // 채워진 홈 갯수
    coordi coordi_lock; // 자물쇠 좌표

    // i, j는 열쇠 좌표
    for (int i = 0; i < key_size; i++)
    {
        coordi_lock.y = now.y + i;
        if (coordi_lock.y < 0 || coordi_lock.y >= lock_size) continue;
        for (int j = 0; j < key_size; j++)
        {
            coordi_lock.x = now.x + j;
            if (coordi_lock.x < 0 || coordi_lock.x >= lock_size) continue;

            // 겹치면 안되는 부분 겹치면 바로 터뜨리기
            if (key[i][j] && lock[coordi_lock.y][coordi_lock.x]) return false;
            if (!key[i][j] && !lock[coordi_lock.y][coordi_lock.x]) return false;

            // 홈 맞춰지면 cnt++
            if (key[i][j] && !lock[coordi_lock.y][coordi_lock.x]) fill_hole++;
        }
    }

    if (fill_hole == lock_hole)
        return true;
    else
        return false;
}

// 선택된 방향으로 다끼워보기
bool insert_all(vector<vector<int>>& key, vector<vector<int>>& lock)
{
    for (int i = 1 - key_size; i < lock_size; i++)
    {
        for (int j = 1 - key_size; j < lock_size; j++)
        {
            if (insert_one({ i, j }, key, lock)) return true;
        }
    }

    return false;
}

// 90도씩 돌리는 함수 
void turn_vec(vector<vector<int>>& key)
{
    vector<vector<int>>tmp{ begin(key), end(key) };
    // 자물쇠 회전
    for (int i = 0; i < key_size; i++)
        for (int j = 0; j < key_size; j++)
            key[key_size - 1 - j][i] = tmp[i][j];
}

bool solution(vector<vector<int>> &key, vector<vector<int>> &lock) {
    bool answer = false;

    key_size = key[0].size();
    lock_size = lock[0].size();
    // 홀 세기
    for (int i = 0; i < lock_size; i++)
    {
        for (int j = 0; j < lock_size; j++)
        {
            if (lock[i][j] == 0)
                lock_hole++;
        }
    }


    // 1. 키 벡터 90도 회전 4번
    for (int i = 0; i < 4; i++)
    {
        if (insert_all(key, lock))
        {
            answer = true;
            break;
        }

        turn_vec(key);
    }


    return answer;
}

int main()
{
    vector<vector<int>> key = { {0, 0, 0},{1, 0, 0},{0, 1, 1} };
    vector<vector<int>> lock = { {1, 1, 1},{1, 1, 0},{1, 0, 1} };

    cout << solution(key, lock) << endl;

      
    return 0;
}