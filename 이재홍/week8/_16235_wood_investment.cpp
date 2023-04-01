#include <iostream>
#include <queue>
#define DIR 8
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate(int x_, int y_);
    Coordinate operator+(const Coordinate &pos) const;
};

Coordinate::Coordinate(int x_, int y_): x(x_), y(y_) {};
Coordinate Coordinate::operator+(const Coordinate &pos) const {return Coordinate(x + pos.x, y + pos.y);}

Coordinate d[DIR] = {{-1,-1}, { 0,-1}, { 1,-1}, {-1, 0}, { 1, 0}, {-1, 1}, { 0, 1}, { 1, 1}};

struct Wood {
    int age;
    Coordinate pos;
    bool operator<(const Wood &w) const;
    Wood(Coordinate pos_);
    Wood(int age_, Coordinate pos_);
};

Wood::Wood(Coordinate pos_): age(1), pos(pos_) {};
Wood::Wood(int age_, Coordinate pos_): age(age_), pos(pos_) {};
bool Wood::operator<(const Wood &w) const {return age > w.age;}

struct Field {
    priority_queue<Wood> live[2];
    int tg;
    queue<Wood> dead;
    queue<Wood> reproduce;
    int length;
    static const int length_max = 10;
    int nutrients[length_max][length_max];
    int fertilize[length_max][length_max];
    Field(int length_);
    int & operator[](const Coordinate pos);
    void read_fertilize();
    int live_wood();
    void plant(const Wood wood);
    void spring();
    void summer();
    void autumn();
    void winter();
};

Field::Field(int length_): length(length_), tg(0) {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {nutrients[x][y] = 5;}}
}
int & Field::operator[](const Coordinate pos) {return nutrients[pos.y][pos.x];}
void Field::read_fertilize() {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {cin >> fertilize[x][y];}}
}
int Field::live_wood() {return live[tg].size();}
void Field::plant(const Wood wood) {
    if(wood.pos.x < 0 || length <= wood.pos.x || wood.pos.y < 0 || length <= wood.pos.y) {return;}
    live[tg].push(wood);
}
void Field::spring() {
    int tg_next = tg ^ 1;
    int live_size = live[tg].size();
    while(live_size) {
        Wood wood = live[tg].top();
        live[tg].pop();
        int & nutrient = nutrients[wood.pos.x][wood.pos.y];
        if(wood.age <= nutrient) {
            nutrient -= wood.age;
            wood.age += 1;
            if(!(wood.age % 5)) {reproduce.push(wood);}
            else {live[tg_next].push(wood);}
        }
        else {dead.push(wood);}
        --live_size;
    }
    tg = tg_next;
}
void Field::summer() {
    int dead_size = dead.size();
    while(dead_size) {
        Wood wood = dead.front();
        dead.pop();
        nutrients[wood.pos.x][wood.pos.y] += wood.age >> 1;
        --dead_size;
    }
}
void Field::autumn() {
    int reproduce_size = reproduce.size();
    while (reproduce_size) {
        Wood wood = reproduce.front();
        reproduce.pop();
        plant(wood);
        plant(Wood(wood.pos + d[0]));
        plant(Wood(wood.pos + d[1]));
        plant(Wood(wood.pos + d[2]));
        plant(Wood(wood.pos + d[3]));
        plant(Wood(wood.pos + d[4]));
        plant(Wood(wood.pos + d[5]));
        plant(Wood(wood.pos + d[6]));
        plant(Wood(wood.pos + d[7]));
        --reproduce_size;
    }
}
void Field::winter() {
    for(int x = 0; x < length; ++x) {for(int y = 0; y < length; ++y) {nutrients[x][y] += fertilize[x][y];}}
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    Field field(N);
    field.read_fertilize();
    for(int m = 0; m < M; ++m) {
        int x;
        int y;
        int age;
        cin >> x >> y >> age;
        Wood wood(age, Coordinate(--x, --y));
        field.plant(wood);
    }
    for(int k = 0; k < K; ++k) {
        field.spring();
        field.summer();
        field.autumn();
        field.winter();
    }
    cout << field.live_wood();
    return 0;
}