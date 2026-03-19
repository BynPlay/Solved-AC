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

    int N, M; cin >> N >> M;

    vector<set<int>>GRAPH(N + 1);
    vector<int>DEGREE(N + 1, 0);

    for (int i = 0; i < M; i++) {
        int cnt; cin >> cnt; int a; cin >> a;
        for (int j = 1; j < cnt; j++) {
            int b; cin >> b;
            int chk = GRAPH[a].size();
            GRAPH[a].insert(b);
            if (GRAPH[a].size() != chk) {
                DEGREE[b]++;
            }
            a = b;
        }
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

        for (auto& i : GRAPH[now]) {
            DEGREE[i]--;
            if (DEGREE[i] == 0) {
                q.push(i);
            }
        }
    }

    if (ans.size() < N) {
        cout << 0;
    }
    else {
        for (auto& i : ans) {
            cout << i << '\n';
        }
    }
}