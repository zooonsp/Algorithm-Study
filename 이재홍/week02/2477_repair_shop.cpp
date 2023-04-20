#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Counter {
    int id;
    int time;
    int cust_id;
};

struct CompareCounter {
    bool operator()(const Counter &c1, const Counter &c2) {
        return c2.time < c1.time || (c2.time == c1.time && c2.id < c1.id);
    }
};

vector<int> reception_time;
priority_queue<int, vector<int>, greater<int>> reception_free;
priority_queue<Counter, vector<Counter>, CompareCounter> reception_process;

vector<int> repair_time;
priority_queue<int, vector<int>, greater<int>> repair_free;
priority_queue<Counter, vector<Counter>, CompareCounter> repair_process;
priority_queue<Counter, vector<Counter>, CompareCounter> repair_wait;

priority_queue<int, vector<int>, greater<int>> customer_queue;

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; testcase++) {
        // prepare
        reception_time.clear();
        reception_free = priority_queue<int, vector<int>, greater<int>>();
        reception_process = priority_queue<Counter, vector<Counter>, CompareCounter>();
        repair_time.clear();
        repair_free = priority_queue<int, vector<int>, greater<int>>();
        repair_process = priority_queue<Counter, vector<Counter>, CompareCounter>();
        repair_wait = priority_queue<Counter, vector<Counter>, CompareCounter>();
        customer_queue = priority_queue<int, vector<int>, greater<int>>();

        // read 5 int
        int N, M, K, A, B; // receptions, repairs, customers, reception used, repair used
        cin >> N >> M >> K >> A >> B;

        // read N reception info
        reception_time.push_back(0);
        for(int i = 0; i < N; i++) {
            int time;
            cin >> time;
            reception_time.push_back(time);
            reception_free.push(i + 1);
        }

        // read M repair info
        repair_time.push_back(0);
        for(int i = 0; i < M; i++) {
            int time;
            cin >> time;
            repair_time.push_back(time);
            repair_free.push(i + 1);
        }

        // read K customer info
        for(int i = 0; i < K; i++) {
            int time;
            cin >> time;
            customer_queue.push(time);
        }

        // simulate history
        int t = 0;
        int count = 0;
        int customer_id = 1;
        while(customer_queue.size() || reception_process.size() || repair_process.size()) {
            // pop customer from repair
            while(repair_process.size() && repair_process.top().time == t) {
                repair_free.push(repair_process.top().id);
                repair_process.pop();
            }
            // pop customer from reception
            while(reception_process.size() && reception_process.top().time <= t) {
                Counter now = reception_process.top();
                reception_free.push(now.id);
                reception_process.pop();
                repair_wait.push(now);
            }
            // pass customer from reception to repair
            while(repair_wait.size() && repair_free.size()) {
                int free_counter = repair_free.top();
                repair_free.pop();
                Counter now = repair_wait.top();
                repair_wait.pop();
                if(now.id == A && free_counter == B)
                    {count += now.cust_id;}
                repair_process.push({free_counter, t + repair_time[free_counter], now.cust_id});
            }
            // pass customer to reception
            while(customer_queue.size() && customer_queue.top() <= t && reception_free.size()) {
                int free_counter = reception_free.top();
                reception_free.pop();
                int now = customer_queue.top();
                customer_queue.pop();
                reception_process.push({free_counter, t + reception_time[free_counter], customer_id});
                ++customer_id;
            }
            ++t;
        }
        // print result
        if(count) {
            cout << '#' << testcase << ' ' << count << '\n';
        }
        else {
            cout << '#' << testcase << ' ' << -1 << '\n';
        }
    }
    return 0;
}