#include <iostream>
#define NUM 4
#define TEETH 8
using namespace std;

struct Magnet {
    int touch = 2;
    int pol[TEETH];
    int pol_f() {
        return pol[touch];
    }
    int pol_r() {
        return pol[(touch + TEETH / 2) % TEETH];
    }
    int pol_top() {
        return pol[(touch + TEETH * 3 / 4) % TEETH];
    }
    void rotate(int direction) {
        if(direction == -1) {touch = (touch + 1) % TEETH;}
        else if(direction == 1) {touch = (touch + TEETH - 1) % TEETH;}
        return;
    }
};

Magnet mag[NUM];
int match[NUM - 1]; // different pole: -1, same pole: 0

void match_update() {
    for(int i = 0; i < NUM - 1; i++)
        {match[i] = (mag[i].pol_f() != mag[i + 1].pol_r()) ? -1 : 0;}
    return;
}

void turn(int mag_idx, int direction) {
    int d = direction;
    mag[mag_idx].rotate(d); // rotate center
    for(int i = mag_idx + 1; i < NUM; ++i) { // propagate forward
        d *= match[i - 1];
        mag[i].rotate(d);
    }
    d = direction;
    for(int i = mag_idx - 1; 0 <= i; --i) { // propagate backward
        d *= match[i];
        mag[i].rotate(d);
    }
    return;
}

int score() {
    int score = 1;
    int total_score = 0;
    for(int i = 0; i < NUM; ++i) {
        total_score += mag[i].pol_top() * score;
        score = score << 1;
    }
    return total_score;
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // read 1 int
        int K;
        cin >> K;
        // read magnet info
        for(int i = 0; i < NUM; ++i) {
            mag[i].touch = 2;
            for(int j = 0; j < TEETH; ++j) {
                cin >> mag[i].pol[j];
            }
        }
        // rotate magnets
        for(int i = 0; i < K; ++i) {
            int m, d;
            cin >> m >> d;
            match_update();
            turn(m - 1, d);
        }
        // calculate score
        cout << '#' << testcase << ' ' << score() << '\n';
    }
    return 0;
}