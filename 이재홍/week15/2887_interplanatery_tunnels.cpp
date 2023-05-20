#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int destination;
    long long cost;
    bool operator<(const Edge &rhs) const {return cost > rhs.cost;}
};

struct Planet {
    int index;
    long long x;
    long long y;
    long long z;
    static bool less_x(const Planet &lhs, const Planet &rhs) {return lhs.x < rhs.x;}
    static bool less_y(const Planet &lhs, const Planet &rhs) {return lhs.y < rhs.y;}
    static bool less_z(const Planet &lhs, const Planet &rhs) {return lhs.z < rhs.z;}
};

void read(int N, vector<Planet> &planets) {
    planets = vector<Planet>(N, Planet());
    for(int it = 0; it < N; ++it) {
        planets[it].index = it;
        cin >> planets[it].x >> planets[it].y >> planets[it].z;
    }
}

void find_edge(vector<Planet> &planets, vector<vector<Edge>> &edges) {
    int planets_size = planets.size();
    edges = vector<vector<Edge>>(planets_size, vector<Edge>());

    sort(planets.begin(), planets.end(), Planet::less_x);
    for(int it = 0; it + 1 < planets_size; ++it) {
        int &planet_1 = planets[it].index;
        int &planet_2 = planets[it + 1].index;
        long long cost = abs(planets[it].x - planets[it + 1].x);
        edges[planet_1].push_back({planet_2, cost});
        edges[planet_2].push_back({planet_1, cost});
    }
    sort(planets.begin(), planets.end(), Planet::less_y);
    for(int it = 0; it + 1 < planets_size; ++it) {
        int &planet_1 = planets[it].index;
        int &planet_2 = planets[it + 1].index;
        long long cost = abs(planets[it].y - planets[it + 1].y);
        edges[planet_1].push_back({planet_2, cost});
        edges[planet_2].push_back({planet_1, cost});
    }
    sort(planets.begin(), planets.end(), Planet::less_z);
    for(int it = 0; it + 1 < planets_size; ++it) {
        int &planet_1 = planets[it].index;
        int &planet_2 = planets[it + 1].index;
        long long cost = abs(planets[it].z - planets[it + 1].z);
        edges[planet_1].push_back({planet_2, cost});
        edges[planet_2].push_back({planet_1, cost});
    }
}

long long get_min_cost(vector<vector<Edge>> &edges) {
    int planets_size = edges.size();
    vector<bool> visited = vector<bool>(planets_size, 0);
    priority_queue<Edge> pq;
    long long total_cost = 0LL;
    int connected = 1;
    for(Edge &edge : edges[0]) {pq.push(edge);}
    visited[0] = true;

    while(connected < planets_size) {
        Edge now = pq.top();
        pq.pop();
        if(visited[now.destination]) {continue;}
        visited[now.destination] = true;
        for(Edge &edge : edges[now.destination]) {pq.push(edge);}
        total_cost += now.cost;
        ++connected;
    }
    return total_cost;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<Planet> planets;
    read(N, planets);
    vector<vector<Edge>> edges;
    find_edge(planets, edges);
    cout << get_min_cost(edges);
    return 0;
}