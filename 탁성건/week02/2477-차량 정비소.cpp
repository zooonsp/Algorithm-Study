#include <iostream>
#include <queue>
using namespace std;

int N, M, K, A, B;
int a[10], b[10], t[1001];

struct Node {
	int hour;
	int id;
	int registId;
	bool operator < (Node next) const {
		if (hour < next.hour)
			return false;
		if (hour > next.hour)
			return true;
		if (registId < next.registId)
			return false;
		if (registId > next.registId)
			return true;
		if (id < next.id)
			return false;
		if (id > next.id)
			return true;
		return false;
	}
};

int solve() {
	priority_queue<Node> registCust;
	priority_queue<Node> registDesk;

	priority_queue<Node> repairCust;
	priority_queue<Node> repairDesk;

	for (int i = 1; i <= K; i++)
		registCust.push({ t[i], i });

	for (int i = 1; i <= N; i++)
		registDesk.push({ 0, i });

	for (int i = 1; i <= M; i++)
		repairDesk.push({ 0, i });

	int ans = 0;
	int hour = 0;

	while (true) {
		// regist
		while (true) {
			if (registCust.empty()) break;
			if (registCust.top().hour > hour) break;
			if (registDesk.top().hour > hour) break;

			while (registDesk.top().hour < hour) {
				registDesk.push({ hour, registDesk.top().id });
				registDesk.pop();
			}

			Node cust = registCust.top(); registCust.pop();
			Node desk = registDesk.top(); registDesk.pop();

			repairCust.push({ hour + a[desk.id], cust.id, desk.id });
			registDesk.push({ hour + a[desk.id], desk.id });
		}

		// repair
		while (true) {
			if (repairCust.empty()) break;
			if (repairCust.top().hour > hour) break;
			if (repairDesk.top().hour > hour) break;

			while (repairDesk.top().hour < hour) {
				repairDesk.push({ hour, repairDesk.top().id });
				repairDesk.pop();
			}

			Node cust = repairCust.top(); repairCust.pop();
			Node desk = repairDesk.top(); repairDesk.pop();

			repairDesk.push({ hour + b[desk.id], desk.id });

			if (cust.registId == A && desk.id == B) ans += cust.id;
		}

		hour++;

		if (registCust.empty() && repairCust.empty()) break;
	}

	if (ans == 0)
		return -1;

	return ans;
}

int main(void) {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cout << '#' << tc << ' ';
		cin >> N >> M >> K >> A >> B;

		for (int i = 1; i <= N; i++)
			cin >> a[i];

		for (int i = 1; i <= M; i++)
			cin >> b[i];

		for (int i = 1; i <= K; i++)
			cin >> t[i];

		cout << solve() << '\n';
	}

	return 0;
}
