// 출처 : https://www.acmicpc.net/blog/view/26

#include <iostream>
#include <vector>
using namespace std;

const int NUM_MAX = 1010000;
const int DEPTH_MAX = 21; // log_2 1000000 : 약 20

int N, M, K;
long long num[NUM_MAX];
long long tree[1 << DEPTH_MAX];
long long lazy[1 << DEPTH_MAX];

long long init(int node, int start, int end) 
{
    if (start == end) 
    {
        return tree[node] = num[start];
    }
    else 
    {
        return tree[node] = init(node * 2, start, (start + end) / 2) + init(node * 2 + 1, (start + end) / 2 + 1, end);
    }
}

void update_lazy(int node, int start, int end) 
{
    if (lazy[node] != 0) 
    {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) 
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// 바꾸는 구간이 모두 포함된 노드와 아닌 노드를 구별해서 업데이트
void update(int node, int start, int end, int left, int right, long long diff)
{
    update_lazy(node, start, end);

    if (left > end || right < start)
        return;
    
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }

    update(node * 2, start, (start + end) / 2, left, right, diff);
    update(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long sum(int node, int start, int end, int left, int right) 
{
    update_lazy(node, start, end);

    if (left > end || right < start) 
    {
        return 0;
    }
    if (left <= start && end <= right)
    {
        return tree[node];
    }
    return sum(node * 2, start, (start + end) / 2, left, right) + sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}

int input()
{
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
        cin >> num[i];
    return 0;
}

int solve_func()
{
    // 1. 세그 트리 만들기
    init(1, 0, N - 1);

    // 2. 명령 대로 출력하기
    int cmd_size = M + K;
    long long a, b, c, d; // a ( 명령 )
    // 1번 ( b번째 수 c로 바꾸기 )
    // 2번 ( b ~ c 번째 수 합 출력)
    for(int i = 0; i < cmd_size; i++)
    {
        cin >> a >> b >> c;
        if (a == 1) 
        {
            cin >> d;

  
            update(1, 0, N - 1, b-1, c-1, d);
          
        }
        else 
        {
            cout << sum(1, 0, N - 1, b - 1, c - 1) << endl;
        }
    }

    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    solve_func();
    
    return 0;
}