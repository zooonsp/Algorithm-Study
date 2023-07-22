#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double t(double x1, double x2, double x3, double y1, double y2, double y3) {
	double res = x1 * y2 + x2 * y3 + x3 * y1;
	res += (-y1 * x2 - y2 * x3 - y3 * x1);
	return res / 2;
}

int main() {

	int n; cin >> n;

	vector<pair<int, int>> v;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		v.push_back({ x, y });
	}

	double res = 0;
	for (int i = 1; i < n; i++) {
		res += t(v[0].first, v[i - 1].first, v[i].first, v[0].second, v[i - 1].second, v[i].second);
	}

	printf("%.1lf", abs(res));
	return 0;
}
