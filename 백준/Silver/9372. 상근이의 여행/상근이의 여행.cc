#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const long long INF{ INT_MAX };


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<int> ROUTES[1001];
        for (int i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            ROUTES[a].push_back(b);
            ROUTES[b].push_back(a);
        }

        queue<int> q;
        vector<bool> visited(N + 1, false);
        int cnt = 0;

        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int now = q.front(); q.pop();
            for (auto& i : ROUTES[now]) {
                if (!visited[i]) {
                    visited[i] = true;
                    cnt++;
                    q.push(i);
                }
            }
        }

        if (cnt == N - 1) cout << cnt << "\n";
        else cout << "Unconnected\n";
    }
}