#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
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
int edges;

bool operator< (const Node& rhs) const {return dist > rhs.dist;}
};

int N,M,K;
int S,D;

vector<Edge> edges[1001];

vector<vector<long long>> dijkstra(){

    priority_queue<Node>pq; vector<vector<long long>>DIST(N + 1, vector<long long>(N, INF));
    pq.push({S,0,0}); DIST[S][0] = 0;

    while(!pq.empty()){
        Node now = pq.top(); pq.pop();

        if(now.dist > DIST[now.pos][now.edges]){
            continue;
        }
        if (now.edges + 1 >= N) continue;

        for(auto& edge: edges[now.pos]){
            if(now.dist + edge.weight < DIST[edge.next][now.edges + 1]){
                DIST[edge.next][now.edges + 1] = now.dist + edge.weight;
                pq.push({edge.next,DIST[edge.next][now.edges + 1],now.edges + 1});
            }
        }
        
    }

    return DIST;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;
    cin >> S >> D;

    for(int i = 0; i < M; i++){
        int a,b; long long w; cin >> a >> b >> w;
        edges[a].push_back({b,w});
        edges[b].push_back({a,w});
    }

    vector<vector<long long>>DIST = dijkstra();
    long long min_ans{INF};
    for(int i = 0; i <= N - 1 ;i++){
        if(DIST[D][i] < min_ans){
            min_ans = DIST[D][i];
        }
    }
    cout << min_ans << '\n';

    long long up{0};
    for(int i = 0; i < K; i++){
        long long p; cin >> p; up += p;
        min_ans = INF;
        
        for(int i = 0; i <= N - 1 ;i++){
            if (DIST[D][i] == INF) continue;
            if(DIST[D][i] + i * up < min_ans){
                min_ans = DIST[D][i] + i * up;
            }
        }
        cout << min_ans << '\n';
    }
}

