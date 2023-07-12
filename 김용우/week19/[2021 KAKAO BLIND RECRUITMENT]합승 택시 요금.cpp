#include <string>
#include <vector>
#include <queue>

constexpr int INF = 7e8;    // INF: 나올 수 없는 값

struct Edge{    // Edge: 간선 정보
    int to, cost;   // to: 연결되어 있는 지점 번호, cost: 택시 요금
    
    bool operator < (Edge next) const { // 택시 요금을 기준으로 오름차순 정렬
        if(cost != next.cost) return cost > next.cost;
        
        return false;
    }
};

int N, S, A, B; // N: 지점의 개수, S: 출발지점, A: A의 도착지점, B: B의 도착지점
std::vector<std::vector<Edge>> v;   // v[i][j]: i 지점과 연결되어있는 간선 정보
std::vector<int> aToPoint;  // aToPoint[i]: A 지점에서 출발하였을 경우의 택시 요금
std::vector<int> bToPoint;  // bToPoint[i]: B 지점에서 출발하였을 경우의 택시 요금
std::vector<int> startToPoint;  // startToPoint[i]: 출발 지점에서 출발하였을 경우의 택시 요금
int ans = INF;  // ans: 합승하였을 경우의 최저 택시요금 -> 합승이 필요없다면 하지 않아도 됨

void dijkstra(int idx, int start){  // idx: 출발 지점에 따른 구분 -> 0: A에서 출발, 1: B에서 출발, 2: 출발 지점에서 출발
    
    std::vector<int> tmpCost;   // tmpCost[i]: 지정된 출발 지점에서 i 지역까지의 최소 택시 비용
    std::priority_queue<Edge> pq;   // pq: 택시 비용에 따라 오름차순 정렬
    
    tmpCost.assign(N+1, INF);
    
    tmpCost[start] = 0; // 출발 지점의 비용은 0
    pq.push({start, 0});
    
    while(!pq.empty()){
        Edge curr = pq.top();   // curr: 현재 탐색할 간선
        pq.pop();
        
        if(tmpCost[curr.to] < curr.cost) continue;  // 이미 더 낮은 비용으로 갈 수 있는 지역이면 continue
        
        int toSize = v[curr.to].size(); // toSize: 현재 지점에 연결되어 있는 간선의 개수
        for(int i=0; i<toSize; i++){
            Edge next = v[curr.to][i];  // next: 연결되어 있는 간선
            int nextCost = next.cost + tmpCost[curr.to];    // nextCost: next 간선을 사용하여 이동하였을 때의 택시 비용
            
            if(tmpCost[next.to] <= nextCost) continue;  // 이미 더 작거나 같은 비용으로 해당 지역을 방문할 수 있다면 continue
            
            tmpCost[next.to] = nextCost;    // 비용 갱신
            pq.push({next.to, nextCost});   // 해당 지역부터 다시 탐색
        }        
    }
    
    // idx: 출발 지점에 따른 값 복사 -> 0: A에서 출발, 1: B에서 출발, 2: 출발 지점에서 출발
    if(idx==0) std::copy(tmpCost.begin(), tmpCost.end(), aToPoint.begin());
    else if(idx==1) std::copy(tmpCost.begin(), tmpCost.end(), bToPoint.begin());
    else if(idx==2) std::copy(tmpCost.begin(), tmpCost.end(), startToPoint.begin());
    
    return;
}

void solution(){
    
    // 각 간선 공간 할당
    aToPoint.assign(N+1,0);
    bToPoint.assign(N+1,0);
    startToPoint.assign(N+1,0);
    
    dijkstra(0, A); // A 에서 각 지역의 비용
    
    dijkstra(1, B); // B 에서 각 지역의 비용
    
    dijkstra(2, S); // 출발 지역에서 각 지역의 비용
    
    for(int i=1; i<=N; i++){
        if(i == INF || i == INF || i == INF) continue;  // 세 지역 중 갈 수 없는 곳이 있다면 continue
        ans = std::min(ans, startToPoint[i] + aToPoint[i] + bToPoint[i]);   // 최저 택시 비용 갱신
    }
    
    return;
}

void input(int n, int s, int a, int b, std::vector<std::vector<int>> &fares){
    
    N = n;
    S = s;
    A = a;
    B = b;
    
    v.assign(N + 1, std::vector<Edge>(0, {0, 0}));  // 간선 공간 할당
    
    int edgeNum = fares.size(); // edgeNum: 총 간선의 개수
    for(int i=0; i<edgeNum; ++i){
        int from = fares[i][0]; // from: 출발 지역
        int to = fares[i][1];   // to: 도착 지역
        int cost = fares[i][2]; // cost: 택시 비용
    
        v[from].push_back({to, cost});
        v[to].push_back({from, cost});  // 양방향 간선
    }
    
    return;
}

int solution(int n, int s, int a, int b, std::vector<std::vector<int>> fares) {
    int answer = 0;
    
    input(n, s, a, b, fares);   // 입력
    
    solution();
    
    answer = ans;
    
    return answer;
}
