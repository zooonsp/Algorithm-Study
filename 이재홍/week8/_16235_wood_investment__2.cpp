#include <iostream>
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
    static const int age_max = 300;
    int amount[age_max];
    Wood();
};

Wood::Wood() {for(register int i = 0; i < age_max; ++i) {amount[i] = 0;}};

struct Field {
    int length;
    int live_wood;
    int tg;
    static const int length_max = 10;
    Wood live[2][length_max][length_max];
    int dead_fertilize[length_max][length_max];
    int reproduce[length_max][length_max];
    int nutrients[length_max][length_max];
    int fertilize[length_max][length_max];
    int max_age[length_max][length_max];
    Field(int length_);
    int & operator[](const Coordinate pos);
    void read_fertilize();
    void plant(const Coordinate pos, int age, int amount);
    void spring();
    void summer();
    void autumn();
    void winter();
};

Field::Field(int length_): length(length_), live_wood(0), tg(0) {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {dead_fertilize[x][y] = 0;}}
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {reproduce[x][y] = 0;}}
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {nutrients[x][y] = 5;}}
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {max_age[x][y] = 0;}}
}
void Field::read_fertilize() {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {cin >> fertilize[x][y];}}
}
void Field::plant(const Coordinate pos, int age, int amount) {
    if(pos.x < 0 || length <= pos.x || pos.y < 0 || length <= pos.y) {return;}
    live[tg][pos.x][pos.y].amount[age] += amount;
    live_wood += amount;
    max_age[pos.x][pos.y] = max_age[pos.x][pos.y] > age ? max_age[pos.x][pos.y] : age;
}
void Field::spring() {
    int tg_next = tg ^ 1;
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            register int age;
            int age_end = max_age[x][y];
            for(age = 1; age <= age_end; ++age) {
                int & amount = live[tg][x][y].amount[age];
                if(!amount) {continue;}
                int growable = nutrients[x][y] / age;
                if(amount <= growable) {
                    nutrients[x][y] -= age * amount;
                    live[tg_next][x][y].amount[age + 1] = amount;
                    if(!((age + 1) % 5)) {reproduce[x][y] += amount;}
                    max_age[x][y] = age + 1;
                    amount = 0;
                }
                else {
                    nutrients[x][y] -= age * growable;
                    live[tg_next][x][y].amount[age + 1] = growable;
                    if(!((age + 1) % 5)) {reproduce[x][y] += growable;}
                    live_wood -= amount - growable;
                    dead_fertilize[x][y] += (age >> 1) * (amount - growable);
                    max_age[x][y] = age + 1;
                    amount = 0;
                    break;
                }
            }
            for(; age <= age_end; ++age) {
                int & amount = live[tg][x][y].amount[age];
                live_wood -= amount;
                dead_fertilize[x][y] += (age >> 1) * amount;
                amount = 0;
            }
        }
    }
    tg = tg_next;
}
void Field::summer() {
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            nutrients[x][y] += dead_fertilize[x][y];
            dead_fertilize[x][y] = 0;
        }
    }
}
void Field::autumn() {
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            int & amount = reproduce[x][y];
            plant(Coordinate(x, y) + d[0], 1, amount);
            plant(Coordinate(x, y) + d[1], 1, amount);
            plant(Coordinate(x, y) + d[2], 1, amount);
            plant(Coordinate(x, y) + d[3], 1, amount);
            plant(Coordinate(x, y) + d[4], 1, amount);
            plant(Coordinate(x, y) + d[5], 1, amount);
            plant(Coordinate(x, y) + d[6], 1, amount);
            plant(Coordinate(x, y) + d[7], 1, amount);
            amount = 0;
        }
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
        field.plant(Coordinate(--x, --y), age, 1);
    }
    for(int k = 0; k < K; ++k) {
        field.spring();
        field.summer();
        field.autumn();
        field.winter();
    }
    cout << field.live_wood;
    return 0;
}