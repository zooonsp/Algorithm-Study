#include <iostream>

using namespace std;

int arr[70000];
int ans[70000];

int main() {

	int n; // 1 - 70`000
	cin >> n;

	int a, b = 1;
	a = n;

	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		// 현재 남은 돌의 정령중 가장 큰 키의 정령 배치
		if (arr[i] > 0) {
			ans[i] = a--;
		}
		// 현재 남은 돌의 정령 중 가장 키가 작은 정령을 배치
		else ans[i] = b++;
	}

	// 일단 입력받은 A(arr)의 N번쨰가 음수면 무조건 -1
	if (arr[n - 1] < 0) cout << -1;
	else
		for (int i = 0; i < n; ++i) {
			cout << ans[i] << " ";
		}

	return 0;
}
