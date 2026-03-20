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
const int INF{ INT_MAX };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;

    for (int t = 0; t < T; t++) {

        int N, K; cin >> N >> K;

        vector<long long>DELAY(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            long long D; cin >> D;
            DELAY[i] = D;

        }

        vector<vector<int>>NEXT(N + 1);
        vector<int>DEGREE(N + 1, 0);

        for (int i = 1; i <= K; i++) {
            int X, Y; cin >> X >> Y;
            NEXT[X].push_back(Y);
            DEGREE[Y]++;
        }

        int W; cin >> W;

        queue<int>q;  vector<long long>DP(N + 1, 0);

        for (int i = 1; i <= N; i++) {

            if (DEGREE[i] == 0) {
                q.push(i);
                DP[i] = DELAY[i];
            }

        }

        while (!q.empty()) {
            int now = q.front(); q.pop();

            for (auto& i : NEXT[now]) {

                DP[i] = max(DP[i], DP[now] + DELAY[i]);
                DEGREE[i]--;

                if (DEGREE[i] == 0) {
                    q.push(i);
                }
            }

        }

        cout << DP[W] << endl;
    }
}
