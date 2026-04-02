#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <climits>

using namespace std;

const long long INF = 4e18;

struct Edge{
int next;
long long weight;
};

struct Node{
int now;
long long dist;

bool operator< (const Node& rhs) const { return dist > rhs.dist; }
};

vector<Edge> EDGES[200001];
set<int>ans;

int N,M;
long long A,B;

vector<long long> dijkstra(const int num){
    vector<long long>DIST(N + 1, INF); 
    priority_queue<Node>pq; pq.push({num,0}); DIST[num] = 0;

    while(!pq.empty()){
        Node now = pq.top(); pq.pop();

        if(now.dist > DIST[now.now]){
            continue;
        }

        for(auto &edge: EDGES[now.now]){
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

    cin >> N >> M >> A >> B;

    for(int i = 0; i < M; i++){
        int a,b,c; cin >> a >> b >> c;
        EDGES[a].push_back({b,c});
        EDGES[b].push_back({a,c});
    }

    vector<long long>ADIST = dijkstra(A);
    vector<long long>BDIST = dijkstra(B);

    for(int i = 1; i <= N; i++){
        if(ADIST[i] + BDIST[i] == ADIST[B]){
            ans.insert(i);
        }
    }

    cout << ans.size() << endl;
    for(auto& n: ans){
        cout << n << ' ';
    }
}