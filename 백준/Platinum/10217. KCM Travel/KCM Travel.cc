#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

struct Edge {
    int to;
    int cost;
    int distance;
};

struct Node {
    int nownum;
    int distsum;
    int costsum;
    bool operator<(const Node& other) const {
        return distsum > other.distsum; // 최소 시간 기준
    }
};

vector<Edge>GRAPH[101];

const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

int N, M, K;

bool sortGreater(const Node& A, const Node& B) {
    return A.distsum < B.distsum;
}


void findMinimum() {
    priority_queue<Node> pq;

    vector<vector<int>>DP(N + 1, vector<int>(M + 1, INF));
    pq.push({ 1, 0, 0 });
    DP[1][0] = 0;

    while (!pq.empty()) {
        Node now = pq.top(); pq.pop();

        if (now.nownum == N) {
            break;
        }

        if (now.distsum > DP[now.nownum][now.costsum]) {
            continue;
        }

        for (auto& edge : GRAPH[now.nownum]) {
            if (now.costsum + edge.cost <= M && DP[edge.to][now.costsum + edge.cost] > DP[now.nownum][now.costsum] + edge.distance) {
                for (int cost = now.costsum + edge.cost; cost <= M; cost++) {
                    if (DP[edge.to][cost] > DP[now.nownum][now.costsum] + edge.distance) {
                        DP[edge.to][cost] = DP[now.nownum][now.costsum] + edge.distance;
                    }        
                    else {
                        break;
                    }
                }
                pq.push({ edge.to , DP[edge.to][now.costsum + edge.cost], now.costsum + edge.cost });
            }
        }
        
    }

    int min_time{ INF };

    for (int i = 0; i <= M; i++) {
        if (DP[N][i] != INF && DP[N][i] < min_time) {
            min_time = DP[N][i];
        }
    }

    if (min_time == INF) {
        cout << "Poor KCM";
    }
    else {
        cout << min_time;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;

    for (int t = 0; t < T; t++) {

        cin >> N >> M >> K;

        for (int i = 0; i < K; i++) {
            int u, v, c, d; cin >> u >> v >> c >> d;
            GRAPH[u].push_back({ v,c,d });
        }

        for (int i = 1; i <= N; i++) {
            sort(GRAPH[i].begin(), GRAPH[i].end(), [](const Edge& A, const Edge& B) {
                return A.cost < B.cost;
                });
        }

        findMinimum();

    }
}


/*
bool inbound(int nr, int nc) {
    if (nr >= 0 && nr <= h + 1 && nc >= 0 && nc <= w + 1) {
        return true;
    }
    return false;
}
*/