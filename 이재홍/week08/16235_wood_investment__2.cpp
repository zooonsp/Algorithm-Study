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
    static const int age_max = 300; // max age of woods (still calculating for exact value)
    int amount[age_max]; // amount of woods with index of age
    Wood(); // constructor initiating amount array 
};

Wood::Wood() {for(register int i = 0; i < age_max; ++i) {amount[i] = 0;}};

struct Field {
    int length; // length of a side of field
    int live_wood; // number of live woods
    int tg; // toggle two live arrays (0,1)
    static const int length_max = 10; // max length of a side of field
    Wood live[2][length_max][length_max]; // two array of woods for odd and even years, store alive woods information
    int dead_fertilize[length_max][length_max]; // store converted nutrients of dead woods
    int reproduce[length_max][length_max]; // store number of parent wood
    int nutrients[length_max][length_max]; // nutrient information of each field position
    int fertilize[length_max][length_max]; // nutrient information that will be added at winter
    int max_age[length_max][length_max]; // max age of each position, used to cut loop execution
    Field(int length_); // constructor of struct, initial toggle value is 0
    void read_fertilize(); // read fertilize array information
    void plant(const Coordinate pos, int age, int amount); // update wood information at live array
    void spring(); // grow woods and update live, dead_fertilize, reproduce array
    void summer(); // add dead_fertilize value to nutrient array
    void autumn(); // plant trees around parent trees
    void winter(); // add fertilize value to nutrient array
};

Field::Field(int length_): length(length_), live_wood(0), tg(0) {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {dead_fertilize[x][y] = 0;}}
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {reproduce[x][y] = 0;}}
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {nutrients[x][y] = 5;}} // initial nutrient value is 5
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {max_age[x][y] = 0;}}
}
void Field::read_fertilize() {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {cin >> fertilize[x][y];}}
}
void Field::plant(const Coordinate pos, int age, int amount) {
    if(pos.x < 0 || length <= pos.x || pos.y < 0 || length <= pos.y) {return;} // check if position to plant wood is valid
    live[tg][pos.x][pos.y].amount[age] += amount; // update number of wood at field position and given age
    live_wood += amount; // update total number of alive wood
    max_age[pos.x][pos.y] = max_age[pos.x][pos.y] > age ? max_age[pos.x][pos.y] : age; // update max age
}
void Field::spring() {
    int tg_next = tg ^ 1; // toggle value for next year
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            register int age;
            int age_end = max_age[x][y]; // save maximum wood age
            for(age = 1; age <= age_end; ++age) {
                int & amount = live[tg][x][y].amount[age]; // amount of woods with given age
                if(!amount) {continue;}
                int growable = nutrients[x][y] / age; // max growable woods with given nutrient
                if(amount <= growable) { // all woods with given age are growable
                    nutrients[x][y] -= age * amount; // update nutrients
                    live[tg_next][x][y].amount[age + 1] = amount; // update next year wood information
                    if(!((age + 1) % 5)) {reproduce[x][y] += amount;} // add to reproduce array and update number of parent woods
                    max_age[x][y] = age + 1; // update maximum wood age
                    amount = 0; // clear amount of woods this year
                }
                else { // part or non of woods are growable
                    nutrients[x][y] -= age * growable; // update nutrients
                    live[tg_next][x][y].amount[age + 1] = growable; // update next year wood information
                    if(!((age + 1) % 5)) {reproduce[x][y] += growable;}
                    live_wood -= amount - growable; // update number of dead woods
                    dead_fertilize[x][y] += (age >> 1) * (amount - growable); // convert dead woods to nutrient
                    max_age[x][y] = age + 1; // update maximum wood age
                    amount = 0; // clear amount of woods this year
                    break; // woods with older age are all dead
                }
            }
            for(; age <= age_end; ++age) { // kill all woods
                int & amount = live[tg][x][y].amount[age];
                live_wood -= amount;
                dead_fertilize[x][y] += (age >> 1) * amount;
                amount = 0;
            }
        }
    }
    tg = tg_next; // toggle to next year
}
void Field::summer() {
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            nutrients[x][y] += dead_fertilize[x][y]; // add converted nutrients to nutriants array
            dead_fertilize[x][y] = 0; // clear dead_fertilize array
        }
    }
}
void Field::autumn() {
    for(register int x = 0; x < length; ++x) {
        for(register int y = 0; y < length; ++y) {
            int & amount = reproduce[x][y];
            plant(Coordinate(x, y) + d[0], 1, amount); // reproduce around parent tree
            plant(Coordinate(x, y) + d[1], 1, amount); // use loop-unrolling for faster execution
            plant(Coordinate(x, y) + d[2], 1, amount);
            plant(Coordinate(x, y) + d[3], 1, amount);
            plant(Coordinate(x, y) + d[4], 1, amount);
            plant(Coordinate(x, y) + d[5], 1, amount);
            plant(Coordinate(x, y) + d[6], 1, amount);
            plant(Coordinate(x, y) + d[7], 1, amount);
            amount = 0; // clear reproduce array
        }
    }
}
void Field::winter() {
    for(int x = 0; x < length; ++x) {for(int y = 0; y < length; ++y) {nutrients[x][y] += fertilize[x][y];}} // add fertilize value to nutrients array
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    Field field(N);
    field.read_fertilize(); // read fertilize array information of field
    for(int m = 0; m < M; ++m) { // read wood information
        int x;
        int y;
        int age;
        cin >> x >> y >> age;
        field.plant(Coordinate(--x, --y), age, 1); // shift postion to range (0,0) ~ (N-1,N-1)
    }
    for(int k = 0; k < K; ++k) { // process field by seasons
        field.spring();
        field.summer();
        field.autumn();
        field.winter();
    }
    cout << field.live_wood; // get number of live woods
    return 0;
}