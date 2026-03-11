#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <queue>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const int INF = { INT_MAX };

int n, m;

int Map[101][101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> n >> m;

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            Map[row][col] = INF;
        }
    }

    for (int i = 0; i < m ; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (c < Map[a][b]) {
            Map[a][b] = c;
        }
    }

    for (int i = 1; i <= n; i++) {
        Map[i][i] = 0;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (Map[i][k] != INF && Map[k][j] != INF) {
                    Map[i][j] = min(Map[i][j], Map[i][k] + Map[k][j]);
                }
            }
        }
    }

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            if (Map[row][col] == INF) {
                cout << 0 << ' ';
            }
            else {
                cout << Map[row][col] << ' ';
            }
        }
        cout << endl;
    }
}
