#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

int n, d, c;

struct Edge {
    int next;
    int weight;
};

struct Node {
    int loc;
    int dist;
    bool operator <(const Node& rhs) const { return dist > rhs.dist; }
};

void dijkstra(const vector<vector<Edge>>& GRAPH) {

    priority_queue<Node>pq; vector<int>DIST(n + 1, INF);
    pq.push({ c,0 }); DIST[c] = 0;

    while (!pq.empty()) {
        Node now = pq.top(); pq.pop();

        if (now.dist > DIST[now.loc]) {
            continue;
        }

        for (auto& edge : GRAPH[now.loc]) {
            if (now.dist + edge.weight < DIST[edge.next]) {
                DIST[edge.next] = now.dist + edge.weight;
                pq.push({ edge.next, DIST[edge.next] });
            }
        }

   }
   
    int infected_num{ 0 }; int max_time{ -1 };

    for (int i = 1; i <= n ; i++) {
        if (DIST[i] != INF) {
            infected_num++;
            if (DIST[i] > max_time) {
                max_time = DIST[i];
            }
        }
    }

    cout << infected_num << ' ' << max_time << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;

    for (int t = 0; t < T; t++) {

        cin >> n >> d >> c;
        vector<vector<Edge>>GRAPH(n + 1);

        for (int i = 0; i < d; i++) {
            int a, b, s; cin >> a >> b >> s;
            GRAPH[b].push_back({ a,s });
        }

        dijkstra(GRAPH);
    }
}