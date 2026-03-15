#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int TC;
    cin >> TC;

    while (TC--) {
        int N, M, W;
        cin >> N >> M >> W;

        vector<Edge> edges;

        for (int i = 0; i < M; i++) {
            int S, E, T;
            cin >> S >> E >> T;

            edges.push_back({S, E, T});
            edges.push_back({E, S, T});
        }

        for (int i = 0; i < W; i++) {
            int S, E, T;
            cin >> S >> E >> T;

            edges.push_back({S, E, -T});
        }

        vector<int> dist(N + 1, 0);

        bool hasCycle = false;

        for (int i = 1; i <= N; i++) {
            for (auto &e : edges) {
                if (dist[e.v] > dist[e.u] + e.w) {
                    dist[e.v] = dist[e.u] + e.w;

                    if (i == N) {
                        hasCycle = true;
                    }
                }
            }
        }

        if (hasCycle) cout << "YES\n";
        else cout << "NO\n";
    }
}