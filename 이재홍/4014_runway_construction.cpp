#include <iostream>
#include <algorithm>
using namespace std;

struct Field {
    int *field_map;
    int h;
    int w;
    Field(int h_, int w_) {
        create_map(h_, w_);
    }
    void create_map(int h_, int w_) {
        h = h_;
        w = w_;
        field_map = new int[h_ * w_];
    }
    void delete_map() {
        delete[] field_map;
    }
    int &operator()(int y, int x) {
        return field_map[w * y + x];
    }
    int diff(int y1, int x1, int y2, int x2) {
        return (*this)(y1, x1) - (*this)(y2, x2);
    }
};

int validate_row(int n, int x, Field &field) {
    int res = 0;
    for(int i = 0; i < n; i++) {
        int valid = 1;
        int up = 1;
        int down = x;
        for(int j = 1; j < n; j++) {
            int diff = field.diff(i, j, i, j - 1);
            if(diff < -1 || 1 < diff) // two step
                {valid = 0; break;}
            else if(diff == 1) { // step up
                if(up != x) {valid = 0; break;}
                up = 0;
            }
            else if(diff == -1) { //step down
                if(down != x) {valid = 0; break;}
                down = 0;
                up = 0;
            }
            if(down == x) // update status
                {up = min(up + 1, x);}
            else
                {down = min(down + 1, x);}
        }
        if(down != x) {valid = 0;}
        res += valid;
    }
    return res;
}

int validate_col(int n, int x, Field &field) {
    int res = 0;
    for(int i = 0; i < n; i++) {
        int valid = 1;
        int up = 1;
        int down = x;
        for(int j = 1; j < n; j++) {
            int diff = field.diff(j, i, j - 1, i);
            if(diff < -1 || 1 < diff) // two step
                {valid = 0; break;}
            else if(diff == 1) { // step up
                if(up != x) {valid = 0; break;}
                up = 0;
            }
            else if(diff == -1) { //step down
                if(down != x) {valid = 0; break;}
                down = 0;
                up = 0;
            }
            if(down == x) // update status
                {up = min(up + 1, x);}
            else
                {down = min(down + 1, x);}
        }
        if(down != x) {valid = 0;}
        res += valid;
    }
    return res;
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 2 int
        int N, X; // map edge length, slide length
        cin >> N >> X;
        // read N*N field info
        Field field(N, N);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                cin >> field(i, j);
            }
        }
        // validate row
        int res = validate_row(N, X, field) + validate_col(N, X, field);
        // print result
        cout << '#' << testcase << ' ' << res << '\n';
    }
}