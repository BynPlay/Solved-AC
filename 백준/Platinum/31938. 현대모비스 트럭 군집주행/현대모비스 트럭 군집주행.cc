#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

const long long INF = LLONG_MAX;

struct Edge{
    int next;
    long long weight;
};
struct Node{
    int pos;
    long long dist;
    bool operator< (const Node& rhs) const { return dist > rhs.dist; }
};

int N, M;
vector<Edge> Edges[200001];

vector<long long> calculateDist(){
    priority_queue<Node> pq;
    vector<long long> DIST(N+1, INF);
    pq.push({1, 0});
    DIST[1] = 0;
    while(!pq.empty()){
        Node now = pq.top(); pq.pop();
        if(now.dist > DIST[now.pos]) continue;
        for(auto& edge: Edges[now.pos]){
            if(now.dist + edge.weight < DIST[edge.next]){
                DIST[edge.next] = now.dist + edge.weight;
                pq.push({edge.next, DIST[edge.next]});
            }
        }
    }
    return DIST;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for(int i = 0; i < M; i++){
        int a, b; long long c;
        cin >> a >> b >> c;
        Edges[a].push_back({b, c});
        Edges[b].push_back({a, c});
    }

    vector<long long> DIST = calculateDist();
    vector<long long> COST(N+1, INF);
    COST[1] = 0;

    for(int i = 1; i <= N; i++){
        for(auto& edge: Edges[i]){
            if(DIST[i] == INF) continue;
            long long realDist = DIST[i] + edge.weight;
            if(realDist != DIST[edge.next]) continue;
            long long newCost = DIST[i] / 10 * 9 + edge.weight;
            COST[edge.next] = min(newCost, COST[edge.next]);
        }
    }

    long long ans_sum = 0;
    for(int i = 2; i <= N; i++){
        ans_sum += COST[i];
    }
    cout << ans_sum;

    return 0;
}