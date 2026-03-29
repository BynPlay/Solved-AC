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

int N, M;

struct EDGE {
    int next;
    int weight;
};

struct NODE {
    int location;
    int dist;

    bool operator<(const NODE& A) const { return dist < A.dist; }
};

vector<EDGE>GRAPH[100001];

vector<int> makeDikstra(int start) {

    priority_queue<NODE>pq; vector<int>DIST(N + 1, -1); DIST[start] = INF;
    pq.push({ start, INF });
    

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();

        if (now.dist < DIST[now.location]) {
            continue;
        }

        for (auto& edge : GRAPH[now.location]) {

            if (min(now.dist, edge.weight) > DIST[edge.next]) {
                DIST[edge.next] = min(now.dist,edge.weight);
                pq.push({ edge.next , DIST[edge.next] });
            }

        }
    }

    return DIST;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int A, B, C; cin >> A >> B >> C;
        GRAPH[A].push_back({ B,C });
        GRAPH[B].push_back({ A,C });
    }
    int start, end; cin >> start >> end;

    cout << makeDikstra(start)[end];

}