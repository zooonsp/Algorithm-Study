#include <iostream>
using namespace std;

struct Coordinate {
    long long x;
    long long y;
    static long long outerProduct(Coordinate &lhs, Coordinate &rhs) {return lhs.x * rhs.y - lhs.y *rhs.x;}
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    long long res = 0LL;
    int N;
    cin >> N;
    Coordinate first;
    cin >> first.x >> first.y;
    Coordinate p1, p2;
    p1 = first;
    for(int it = 1; it < N; ++it) {
        cin >> p2.x >> p2.y;
        res += Coordinate::outerProduct(p1, p2);
        p1 = p2;
    }
    res += Coordinate::outerProduct(p1, first);
    res = res < 0 ? -res : res;
    cout << (res >> 1) << (res & 1LL ? ".5" : ".0");
    return 0;
}