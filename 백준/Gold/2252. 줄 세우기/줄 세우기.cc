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

vector<int>GRAPH[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int N, M; cin >> N >> M;
    vector<vector<int>>GRAPH(N + 1);
    vector<int>DEGREE(N + 1);

    for (int i = 0; i < M; i++) {
        int A, B; cin >> A >> B;
        GRAPH[A].push_back(B);
        DEGREE[B]++;
    }

    queue<int>q;
    for (int i = 1; i <= N; i++) {
        if (DEGREE[i] == 0) {
            q.push(i);
        }
    }

    vector<int>ans;
    while (!q.empty()) {
        int now = q.front(); q.pop();
        ans.push_back(now);

        for (auto& nxt : GRAPH[now]) {
            DEGREE[nxt]--;
            if (DEGREE[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    for (int x : ans)
        cout << x << " ";
    cout << "\n";
}