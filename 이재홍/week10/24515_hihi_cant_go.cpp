#include <iostream>
#include <queue>
#include <vector>
#include <set>
#define MAX_N 1002
#define DIR_8 8
#define DIR_4 4
#define DIR_2 2
using namespace std;

struct Node {
    int size;
    vector<int> edge_to;
};

struct Edge {
    int destination;
    int cost;
    bool operator<(const Edge &rhs) const {return cost > rhs.cost;}
};

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) const {return {x + rhs.x, y + rhs.y};}
    bool operator==(const Coordinate &rhs) const {return x == rhs.x && y == rhs.y;}
    bool operator!=(const Coordinate &rhs) const {return x != rhs.x || y != rhs.y;}
};

Coordinate d4[DIR_4] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}};
Coordinate d8[DIR_4] = {{-1,-1}, { 0,-1}, { 1,-1}, {-1, 0}};

int N;
int set_index;
vector<Node> sets;
int field_set[MAX_N][MAX_N];
string field_map[MAX_N];

void read() {
    cin >> N;
    for(int it = 0; it < N; ++it) {
        cin >> field_map[it];
    }
}

bool out(Coordinate &position) {
    return position.x < 1 || position.y < 1 || N < position.x || N < position.y;
}

void init_set() {
    for(int it = 1; it < N; ++it) {
        field_set[0][it] = 2;
        field_set[it][0] = 1;
        field_set[N + 1][it] = 1;
        field_set[it][N + 1] = 2;
    }

    queue<Coordinate> lands;
    for(int col_it = 2; col_it <= N; ++col_it)
        {lands.push({col_it, 1});}
    for(int row_it = 2; row_it < N; ++row_it)
        {for(int col_it = 1; col_it <= N; ++col_it)
            {lands.push({col_it, row_it});}}
    for(int col_it = 1; col_it < N; ++col_it)
        {lands.push({col_it, N});}

    set_index = 3;
    sets = vector<Node>(3, Node());
    while(!lands.empty()) {
        Coordinate land_piece = lands.front();
        lands.pop();
        if(field_set[land_piece.y][land_piece.x]) {continue;}
        queue<Coordinate> merged_lands;
        merged_lands.push(land_piece);
        field_set[land_piece.y][land_piece.x] = set_index;
        sets.push_back(Node());
        while(!merged_lands.empty()) {
            Coordinate now = merged_lands.front();
            merged_lands.pop();
            sets[set_index].size += 1;
            for(int dir = 0; dir < DIR_4; ++dir) {
                Coordinate next = now + d4[dir];
                if(out(next)) {continue;}
                if(field_set[next.y][next.x]) {continue;}
                if(field_map[now.y - 1][now.x - 1] != field_map[next.y - 1][next.x - 1]) {continue;}
                field_set[next.y][next.x] = set_index;
                merged_lands.push(next);
            }
        }
        ++set_index;
    }

    set<pair<int,int>> edge_visited;
    for(int row_it = 1; row_it <= N + 1; ++row_it) {
        for(int col_it = 1; col_it <= N; ++col_it) {
            Coordinate node_1, node_2;
            node_1 = {col_it, row_it};
            for(int dir = 0; dir < DIR_4; ++dir) {
                node_2 = node_1 + d8[dir];
                if(field_set[node_1.y][node_1.x] == field_set[node_2.y][node_2.x]) {continue;}
                if(!field_set[node_1.y][node_1.x] || !field_set[node_2.y][node_2.x]) {continue;}
                if(field_set[node_1.y][node_1.x] < field_set[node_2.y][node_2.x]) {edge_visited.insert(pair<int,int>(field_set[node_1.y][node_1.x], field_set[node_2.y][node_2.x]));}
                else {edge_visited.insert(pair<int,int>(field_set[node_2.y][node_2.x], field_set[node_1.y][node_1.x]));}
            }
        }
    }

    for(pair<int,int> edge : edge_visited) {
        sets[edge.first].edge_to.push_back(edge.second);
        sets[edge.second].edge_to.push_back(edge.first);
    }
}

int bfs() {
    priority_queue<Edge> pq;
    pq.push({1, 0});
    int *visited = new int[set_index + 1];
    for(int it = 1; it <= set_index; ++it) {visited[it] = 0;}
    while(!pq.empty()) {
        Edge now = pq.top();
        pq.pop();
        if(now.destination == 2) {return now.cost;}
        if(visited[now.destination]) {continue;}
        visited[now.destination] = 1;
        for(int set_no : sets[now.destination].edge_to) {
            pq.push({set_no, now.cost + sets[set_no].size});
        }
    }
    return -1;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    read();
    init_set();
    cout << bfs();
    return 0;
}