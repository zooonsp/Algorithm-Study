#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point() = default;
};
using Vector = Point;

ll Cross(const Vector& a, const Vector& b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

int main() {
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	int N;
	cin >> N;
	vector<Point> points(N);
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	double area{};
	for (int i{ 1 }; i < N - 1; ++i) {
		Vector a(points[i].x - points[0].x, points[i].y - points[0].y);
		Vector b(points[i + 1].x - points[0].x, points[i + 1].y - points[0].y);
		area += static_cast<double>(Cross(a, b)) / 2;
	}
	if (area < 0) area = -area;

	cout << fixed;
	cout.precision(1); // 소수점 아래 둘째 자리에서 반올림
	cout << area << '\n';

	return 0;
}