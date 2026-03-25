#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

struct Monkey {
    int row;
    int col;
    int k;
};

const int DR[4] = { -1,1,0,0 };
const int DC[4] = { 0,0,-1,1 };

const int D[4][2] = { {1,0},{-1,0},{0,1},{ 0,-1 } };
const int Dh[8][2] = { {-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2} };

int K; int W, H;
int MAP[201][201];
int DISTANCE[201][201][31];

bool inbound(int nr, int nc);

int monkeyMove() {

    queue<Monkey>q; 
    q.push({ 1,1,K });


    while (!q.empty()) {
        Monkey now = q.front(); q.pop();

        if (now.row == H && now.col == W) {
            return DISTANCE[now.row][now.col][now.k];
        }

        for (int d = 0; d < 4; d++) {
            int nr = now.row + D[d][0]; int nc = now.col + D[d][1];
            if (inbound(nr, nc) && DISTANCE[nr][nc][now.k] == 0) {
                q.push({ nr,nc,now.k }); DISTANCE[nr][nc][now.k] = DISTANCE[now.row][now.col][now.k] + 1;
            }
        }
        for (int d = 0; d < 8; d++) {
            int nr = now.row + Dh[d][0]; int nc = now.col + Dh[d][1];
            if (inbound(nr, nc) && now.k > 0 && DISTANCE[nr][nc][now.k - 1] == 0) {
                q.push({ nr,nc,now.k - 1 }); DISTANCE[nr][nc][now.k - 1] = DISTANCE[now.row][now.col][now.k] + 1;
            }
        }

    }


    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> K;
    cin >> W >> H;

    for (int row = 1; row <= H; row++) {
        for (int col = 1; col <= W; col++) {
            cin >> MAP[row][col];
            if (MAP[row][col] == 1) {
                MAP[row][col] = -1;
            }
        }
    }

    cout << monkeyMove();

}


bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= H && nc >= 1 && nc <= W && MAP[nr][nc] != -1) {
        return true;
    }
    return false;
}