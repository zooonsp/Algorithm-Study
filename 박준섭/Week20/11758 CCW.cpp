#include <iostream>

using namespace std;

struct node {
	int x, y;
};

int cross(int x1, int y1, int x2, int y2) {
	return x1 * y2 - x2 * y1;
}

int main() {

	node p1, p2, p3;
	cin >> p1.x >> p1.y;
	cin >> p2.x >> p2.y;
	cin >> p3.x >> p3.y;

	int ans = cross(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y);

	if (ans > 0) cout << 1;
	else if (ans < 0) cout << -1;
	else cout << 0;

	return 0;
}
