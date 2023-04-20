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
    int age; // age of wood
    Coordinate pos; // position of wood
    bool operator<(const Wood &w) const; // operator overloading for priority queue element compare
    Wood(Coordinate pos_); // constructor using coordinate and default age 1
    Wood(int age_, Coordinate pos_); // constructor using coordinate and age
};

Wood::Wood(Coordinate pos_): age(1), pos(pos_) {};
Wood::Wood(int age_, Coordinate pos_): age(age_), pos(pos_) {};
bool Wood::operator<(const Wood &w) const {return age > w.age;}

struct Field {
    priority_queue<Wood> live[2]; // two priority queue for odd and even years, store alive tree information
    int tg; // toggle two priority queue (0,1)
    queue<Wood> dead; // store dead tree information between spring and summer
    queue<Wood> reproduce; // store trees that can reproduce at autumn 
    int length; // length of a side of field
    static const int length_max = 10; // max length
    int nutrients[length_max][length_max]; // nutrient information of each field position
    int fertilize[length_max][length_max]; // nutrient information that will be added at winter
    Field(int length_); // constructor of struct, initial toggle value is 0
    void read_fertilize(); // read fertilize array information
    int live_wood(); // return number of alive woods
    void plant(const Wood wood); // generate new wood instance and add to live queue
    void spring(); // grow woods and update live, dead, reproduce queue
    void summer(); // convert woods in dead queue to nutrient
    void autumn(); // plant new wood around wood in reproduce queue
    void winter(); // add fertilize array value to nutrients array
};

Field::Field(int length_): length(length_), tg(0) {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {nutrients[x][y] = 5;}}
}
void Field::read_fertilize() {
    for(register int x = 0; x < length; ++x) {for(register int y = 0; y < length; ++y) {cin >> fertilize[x][y];}}
}
int Field::live_wood() {return live[tg].size();}
void Field::plant(const Wood wood) {
    if(wood.pos.x < 0 || length <= wood.pos.x || wood.pos.y < 0 || length <= wood.pos.y) {return;} // check if position to plant wood is valid
    live[tg].push(wood);
}
void Field::spring() {
    int tg_next = tg ^ 1; // toggle value for next year
    int live_size = live[tg].size();
    while(live_size) { // run loop live queue size times
        Wood wood = live[tg].top();
        live[tg].pop();
        int & nutrient = nutrients[wood.pos.x][wood.pos.y];
        if(wood.age <= nutrient) { // wood is able to grow
            nutrient -= wood.age;
            wood.age += 1;
            if(!(wood.age % 5)) {reproduce.push(wood);} // add to reproduce queue if age is multiple of 5
            else {live[tg_next].push(wood);} // add to next year live queue
        }
        else {dead.push(wood);} // wood is dead
        --live_size;
    }
    tg = tg_next; // toggle to next year
}
void Field::summer() {
    int dead_size = dead.size();
    while(dead_size) { // run loop dead queue size times
        Wood wood = dead.front();
        dead.pop();
        nutrients[wood.pos.x][wood.pos.y] += wood.age >> 1; // use bit operator for faster calculation
        --dead_size;
    }
}
void Field::autumn() {
    int reproduce_size = reproduce.size();
    while (reproduce_size) { // run loop repruduce queue size times
        Wood wood = reproduce.front();
        reproduce.pop();
        plant(wood); // add this wood back to live queue
        plant(Wood(wood.pos + d[0])); // reproduce around parent tree
        plant(Wood(wood.pos + d[1])); // use loop-unrolling for faster execution
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
        Wood wood(age, Coordinate(--x, --y)); // shift postion to range (0,0) ~ (N-1,N-1)
        field.plant(wood); // add to live queue
    }
    for(int k = 0; k < K; ++k) { // process field by seasons
        field.spring();
        field.summer();
        field.autumn();
        field.winter();
    }
    cout << field.live_wood(); // get number of live woods
    return 0;
}