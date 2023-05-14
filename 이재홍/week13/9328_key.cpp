#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

enum FieldValue {
    WALL = '*',
    PATH = '.',
    DOCS = '$'
};

enum FieldPositioning {
    MARGIN = 2,
    DIR = 4
};

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) {return {x + rhs.x, y + rhs.y};}
};

Coordinate d[DIR] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}};

int testcase;
int row, column;
vector<string> field;
vector<vector<int>> visited;
vector<int> keys;

bool out(Coordinate position) {
    return position.x < 0 || position.y < 0 || column + MARGIN <= position.x || row + MARGIN <= position.y;
}

void init_field() {
    cin >> row >> column;
    field = vector<string>(row + MARGIN, string());
    field[0] = string(column + MARGIN, PATH);
    for(int it = 1; it <= row; ++it) {
        field[it].reserve(column + MARGIN);
        string field_row;
        cin >> field_row;
        field[it] += PATH;
        field[it] += field_row;
        field[it] += PATH;
    }
    field[row + 1] = string(column + MARGIN, PATH);
}

void init_visited() {
    visited = vector<vector<int>>(row + MARGIN, vector<int>(column + MARGIN, 0));
}

void init_keys() {
    keys = vector<int>(256, 0);
    string key_string;
    cin >> key_string;
    for(char &key : key_string) {
        keys[key] = 1;
    }
}

int bfs() {
    queue<Coordinate> q;
    queue<Coordinate> locked;
    q.push({0, 0});
    visited[0][0] = 1;
    bool changed = true;
    int collected_documents = 0;
    while(changed) {
        changed = false;
        int q_size = q.size();
        for(int it = 0; it < q_size; ++it) {
            Coordinate now = q.front();
            q.pop();
            char now_value = field[now.y][now.x];
            if('a' <= (now_value | 0x20) && (now_value | 0x20) <= 'z') {
                if('a' <= now_value) {
                    keys[now_value] = 1;
                }
                else if(!keys[now_value | 0x20]) {
                    locked.push(now);
                    continue;
                }
            }
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate next = now + d[dir];
                if(out(next)) {continue;}
                if(visited[next.y][next.x]) {continue;}
                char &field_value = field[next.y][next.x];
                if(field_value == WALL) {continue;}
                if(field_value == DOCS) {++collected_documents;}
                q.push(next);
                visited[next.y][next.x] = 1;
                ++q_size;
                changed = true;
            }
        }
        while(!locked.empty()) {
            q.push(locked.front());
            locked.pop();
        }
    }
    return collected_documents;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> testcase;
    for(int tc_it = 1; tc_it <= testcase; ++tc_it) {
        init_field();
        init_visited();
        init_keys();
        cout << bfs() << '\n';
    }
    return 0;
}