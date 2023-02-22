#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX_DESK = 11;
const int MAX_custom = 1111;

bool comp(int a, int b)
{
	if (a > b)
		return true;

	return false;
}

struct Info{
	int num;
	int time;
	int counter;
	int repair;

	bool operator < (Info next) const
	{
		if (time < next.time)
			return false;
		if (time > next.time)
			return true;

		if (counter < next.counter)
			return false;
		if (counter > next.counter)
			return true;

		return false;
	}
};


int N, M, K, A, B; // 접수창구, 정비창구, 고객수, 두고간접수창구 A , 정비창구 B
int counter_time[MAX_DESK]; // 접수 시간
int repair_time[MAX_DESK]; // 정비 시간
vector<int> customer_time; // 손님들이 오는 시간

int init()
{
	customer_time.clear();
	return 0;
}

int input()
{
	cin >> N >> M >> K >> A >> B;

	for (int i = 0; i < N; i++)
		cin >> counter_time[i];
	for (int i = 0; i < M; i++)
		cin >> repair_time[i];
	for (int i = 0; i < K; i++)
	{
		int temp;
		cin >> temp;
		customer_time.push_back(temp);
	}

	return 0;
}

int solve_func()
{
	int time = 0;
	int ans = 0;

	queue<Info> counter_line; // 접수창구 줄
	priority_queue<Info>repair_line; // 정비창구 줄 - 정비 창구는 도착한 시간, 시간이 같다면 접수창구 번호 순으로 서게됨.
	int visited_counter[MAX_DESK] = { 0, }; // 접수 창구에서 접수 하고 있는지
	Info counter_desk[MAX_DESK] = { 0, }; // 접수 창구에 있는 사람들의 정보
	int visited_repair[MAX_DESK] = { 0, }; // 정비 창구에서 정비 하고 있는지
	Info repair_desk[MAX_DESK] = { 0, }; // 정비 창구에 있는 사람들의 정보
	int cnt = 1; // 손님 번호 생성용 cnt
	int customer_size = customer_time.size(); // 손님의 수
	int repair_complete = 0; // 수리 창구 배정이 완료 되었는지
	// 손님의수 == 수리창구 배정이 완료되면 종료

	sort(customer_time.begin(), customer_time.end(), comp);

	while (1)
	{
		//손님 도착
		while (1)
		{
			if (customer_time.empty()) break;

			if (time >= customer_time.back())
			{
				counter_line.push({ cnt, time, 0, 0 });
				customer_time.pop_back();
				cnt++;
			}
			else
				break;
		}

		// 수리 완료
		for (int i = 0; i < M; i++)
		{
			if (visited_repair[i] == 0) continue;

			if (repair_desk[i].time <= time)
			{
				visited_repair[i] = 0;
			}
		}

		// 수리 창구 배정
		while (1)
		{
			if (repair_line.empty()) break;

			int repair = -1;
			for (int i = 0; i < M; i++)
			{
				if (visited_repair[i] == 0)
				{
					visited_repair[i] = 1;
					repair = i;
					repair_desk[i] = repair_line.top();
					repair_desk[i].repair = repair;
					repair_desk[i].time = time + repair_time[i]; // 정비 종료시간을 저장
					repair_line.pop();

					// 종료 변수
					repair_complete++;

					if (i == B - 1)
						if (repair_desk[i].counter == A - 1)
						{
							ans += repair_desk[i].num;
						}

					break;
				}
			}

			if (repair == -1)
				break;
		}

		// 접수 완료
		for (int i = 0; i < N; i++)
		{
			if (visited_counter[i] == 0) continue;

			if (counter_desk[i].time <= time)
			{
				repair_line.push(counter_desk[i]);
				visited_counter[i] = 0;
			}
		}

		// 접수 창구 배정
		while (1)
		{
			if (counter_line.empty()) break;

			int counter = -1;
			for (int i = 0; i < N; i++)
			{
				if (visited_counter[i] == 0)
				{
					visited_counter[i] = 1;
					counter = i;
					counter_desk[i].num = counter_line.front().num;
					counter_desk[i].counter = counter;
					counter_desk[i].time = time + counter_time[i]; // 접수 종료시간을 저장
					counter_line.pop();

					break;
				}
			}

			if (counter == -1)
				break;
		}


		if (repair_complete == customer_size)
			break;

		time++;
	}

	return ans;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();
		int temp = solve_func();
		if (temp > 0)
			cout << "#" << test_case << " " << temp << "\n";
		else
			cout << "#" << test_case << " " << -1 << "\n";


	}
	return 0;
}