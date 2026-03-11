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

int n, m, r;

int Graph[101][101];
int Item[101];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    //freopen("input.txt", "r", stdin);
    cin >> n >> m >> r;

    for (int i = 1; i <= n; i++) {
        int t; cin >> t;
        Item[i] = t;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                Graph[i][j] = 0;
            }
            else {
                Graph[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= r; i++) {
        int a, b, l; cin >> a >> b >> l;
        if (l < Graph[a][b]) {
            Graph[a][b] = l;
        }
        if (l < Graph[b][a]) {
            Graph[b][a] = l;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (Graph[i][k] != INF && Graph[k][j] != INF) {
                    Graph[i][j] = min(Graph[i][j], Graph[i][k] + Graph[k][j]);
                }
            }
        }
    }

    

    int max_ans{ 0 };
    for (int i = 1; i <= n; i++) {
        int sum_item{ 0 };
        for (int j = 1; j <= n; j++) {
            if (Graph[i][j] <= m) {
                sum_item += Item[j];
            }
        }
        if (sum_item > max_ans) {
            max_ans = sum_item;
        }
    }

    cout << max_ans;
}