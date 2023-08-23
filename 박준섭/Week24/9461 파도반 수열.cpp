#include <iostream>

using namespace std;

int main() {

	long long arr[101] = {};
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 1;

	for (int i = 4; i <= 100; ++i) {
		arr[i] = arr[i - 2] + arr[i - 3];
	}

	int T; cin >> T;

	while (T--) {
		int n; cin >> n;
		cout << arr[n] << '\n';
	}

	return 0;
}
