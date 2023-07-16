#include <iostream>
using namespace std;

int main() {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    x3 -= x2; y3 -= y2;
    x2 -= x1; y2 -= y1;
    int res = x2 * y3 - x3 * y2;
    cout << (res ? (res < 0 ? -1 : 1) : 0);
    return 0;
}