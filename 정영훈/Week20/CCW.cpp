#include <bits/stdc++.h>

using namespace std;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point() = default;
};

int ccw(const Point& p1, const Point& p2, const Point& p3) {
	Point a(p2.x - p1.x, p2.y - p1.y); // p1 -> p2
	Point b(p3.x - p1.x, p3.y - p1.y); // p1 -> p3

	int cross = a.x * b.y - a.y * b.x;
	if (cross > 0) return 1; // 반시계
	else if (cross < 0) return -1; // 시계
	else return 0; // 일직선
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	Point p1, p2, p3;

	cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

	cout << ccw(p1, p2, p3) << '\n';

	return 0;
}