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

bool inbound(int nr, int nc);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N, M; cin >> N >> M;
    
    vector<int>v(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
    }

    vector<int>Diff(N + 1,0);
    for (int i = 1; i <= M; i++) {
        int a, b, k; cin >> a >> b >> k;
        Diff[a] += k; if (b + 1 <= N) { Diff[b + 1] -= k; }
    }

    int weight{ 0 };
    for (int i = 1; i <= N; i++) {
        weight += Diff[i];
        v[i] += weight;
        cout << v[i] << ' ';
    }

    return 0;
}

bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= 19 && nc >= 1 && nc <= 19) {
        return true;
    }
    return false;
}