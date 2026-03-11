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

const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

int N, M;
int Map[1001][1001];
int Dist[1001][1001][2];

struct Man {
    int row;
    int col;
    bool chance_used{ false };
};

bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}

int moveToEnd() {
    queue<Man>q; q.push({ 1, 1, false }); Dist[1][1][0] = 1;

    while (!q.empty()) {
        Man now = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = now.row + Dr[d]; int nc = now.col + Dc[d];
            if (inBound(nr, nc)) {
                
                if (Map[nr][nc] == '0') {
                    if (now.chance_used == false && Dist[nr][nc][0] == 0) {
                        Dist[nr][nc][0] += Dist[now.row][now.col][0] + 1;
                        q.push({ nr,nc,false });
                    }
                    else if(now.chance_used == true && Dist[nr][nc][1] == 0) {
                        Dist[nr][nc][1] += Dist[now.row][now.col][1] + 1;
                        q.push({ nr,nc,true });
                    }
                }

                else if (Map[nr][nc] == '1') {
                    if (now.chance_used == false && Dist[nr][nc][1] == 0) {
                        Dist[nr][nc][1] += Dist[now.row][now.col][0] + 1;
                        q.push({ nr,nc,true });
                    }
                }
            }
        }
    }

    int a = Dist[N][M][0];
    int b = Dist[N][M][1];
    if (a == 0 && b == 0) return -1;
    if (a == 0) return b;
    if (b == 0) return a;
    return min(a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int row = 1; row <= N; row++) {
        string cols; cin >> cols;
        for (int col = 1; col <= M; col++) {
            Map[row][col] = cols[col - 1];
        }
    }

    cout << moveToEnd();
}