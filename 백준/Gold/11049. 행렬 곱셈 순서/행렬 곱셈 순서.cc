#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const int INF{ INT_MAX };

struct Matrix {
    int row;
    int col;
};

int N;

int main() {
    ios::sync_with_stdio(false); //앞은 현재 도시, 뒤는 현재 선택한 개수
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N;
  
    Matrix matrix[501];
    for (int i = 1; i <= N; i++) {
        cin >> matrix[i].row >> matrix[i].col;
    }

    vector<vector<int>>DP(N + 1, vector<int>(N+1,INF));

    for (int i = 1; i <= N; i++) {
        DP[i][i] = 0;
    }
    
    for (int len = 2; len <= N; len++) {
        for (int start = 1; start + len - 1 <= N; start++) {
            int now_min{ INF };
            for (int mid = start; mid <= start + len - 2; mid++) {
                int cand = DP[start][mid] + (matrix[start].row * matrix[mid].col * matrix[start + len - 1].col) + DP[mid + 1][start + len - 1];
                if (cand < now_min) {
                    now_min = cand;
                }
            }
            DP[start][start + len - 1] = now_min;
        }
    }

    cout << DP[1][N];
}