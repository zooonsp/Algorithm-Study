// Segment Tree 공부
// Lazy Propagation (구간에 대한 변경이므로 그냥 segment tree로는 시간내에 불가능함)
// https://yabmoons.tistory.com/442

#include <iostream>
#include <cmath> // ceil, log2
#include <vector>

using namespace std;

vector<long long> SegmentTree, Arr, Lazy;

long long Make_SegmentTree(int Node, int Start, int End)
{
    if (Start == End)
        return SegmentTree[Node] = Arr[Start];

    int Mid = (Start + End) / 2; // overflow 주의

    long long Left_Result = Make_SegmentTree(Node * 2, Start, Mid);        // 왼쪽 자식
    long long Right_Result = Make_SegmentTree(Node * 2 + 1, Mid + 1, End); // 오른쪽 자식

    return SegmentTree[Node] = Left_Result + Right_Result;
}

void Lazy_Update(int Node, int Start, int End)
{
    if (Lazy[Node] != 0) // 0이 아닐 때
    {
        SegmentTree[Node] = SegmentTree[Node] + (End - Start + 1) * Lazy[Node];
        if (Start != End) // 구간인 경우 자식에게 전파
        {
            Lazy[Node * 2] += Lazy[Node];
            Lazy[Node * 2 + 1] += Lazy[Node];
        }
        Lazy[Node] = 0;
    }
}

void UpdateSegmentTree(int Node, int Start, int End, int Left, int Right, long long Value)
{
    Lazy_Update(Node, Start, End); // 처음에 기존 lazy 갱신하기
    if (Right < Start || Left > End)
        return;
    if (Left <= Start && End <= Right) // 내가 찾는 구간[Left, Right]이 더 큰 경우
    {
        SegmentTree[Node] = SegmentTree[Node] + (End - Start + 1) * Value;
        if (Start != End) // 구간이라면 자식에게 전파
        {
            Lazy[Node * 2] += Value;
            Lazy[Node * 2 + 1] += Value;
        }
        return; // 더 갈 필요 없으니 return
    }

    int Mid = (Start + End) / 2;
    UpdateSegmentTree(Node * 2, Start, Mid, Left, Right, Value);       // 왼쪽 자식
    UpdateSegmentTree(Node * 2 + 1, Mid + 1, End, Left, Right, Value); // 오른쪽 자식
    SegmentTree[Node] = SegmentTree[Node * 2] + SegmentTree[Node * 2 + 1];
}

long long Sum(int Node, int Start, int End, int Left, int Right)
{
    Lazy_Update(Node, Start, End); // 처음에 기존 lazy 갱신
    if (Right < Start || Left > End)
        return 0; // 갈 필요 없음(필요한 구간이 아님)
    if (Left <= Start && End <= Right)
        return SegmentTree[Node]; // 더 내려갈 필요 없음.

    int Mid = (Start + End) / 2;
    long long Left_Result = Sum(Node * 2, Start, Mid, Left, Right);        // 왼쪽 자식
    long long Right_Result = Sum(Node * 2 + 1, Mid + 1, End, Left, Right); // 오른쪽 자식
    return Left_Result + Right_Result;
}

int main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    int N, M, K;
    cin >> N >> M >> K;
    Arr.resize(N);
    for (int n = 0; n < N; ++n)
    {
        cin >> Arr[n];
    }

    int Tree_Height = (int)ceil(log2(N));
    int Tree_Size = (1 << (Tree_Height + 1));
    SegmentTree.resize(Tree_Size);
    Lazy.resize(Tree_Size);
    Make_SegmentTree(1, 0, N - 1);

    for (int t = 0; t < M + K; ++t)
    {
        int a, b, c;
        long long d;
        cin >> a >> b >> c;
        if (a == 1)
        { // b번째 수 ~ c번째 수에 += d
            cin >> d;
            UpdateSegmentTree(1, 0, N - 1, b - 1, c - 1, d);
        }
        else
        { // [b, c] 합
            cout << Sum(1, 0, N - 1, b - 1, c - 1) << '\n';
        }
    }

    return 0;
}