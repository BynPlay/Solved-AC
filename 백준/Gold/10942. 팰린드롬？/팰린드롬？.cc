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

    int N; cin >> N;
    vector<int>NUMBERS(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> NUMBERS[i];
    }

    vector<vector<bool>>DP(N + 1, vector<bool>(N + 1, true));

    for (int i = 1; i < N; i++) {
        DP[i][i + 1] = (NUMBERS[i] == NUMBERS[i + 1]);
    }


    for (int length = 3; length <= N; length++) {
        for (int start = 1; start + length - 1 <= N; start++) {
            int end = start + length - 1; 
            if (DP[start+1][end-1] == false || NUMBERS[start] != NUMBERS[end]) {
                DP[start][end] = false;
            }
        }
    }

    int M; cin >> M;
    for (int i = 1; i <= M; i++) {
        int S, E;
        cin >> S >> E;

        cout << DP[S][E] << '\n';
    }
}