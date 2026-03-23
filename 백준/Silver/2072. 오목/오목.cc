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

const int length[2][2] = { {1,0},{-1,0} };
const int width[2][2] = { {0,1},{0,-1} };
const int diagonal1[2][2] = { {-1,1},{1,-1} };
const int diagonal2[2][2] = { {-1,-1},{1,1} };
const int CASES[4][2][2] = { { {1,0},{-1,0} } ,{ {0,1},{0,-1} } ,{ {-1,1},{1,-1} } ,{ {-1,-1},{1,1} } };

int BOARD[20][20];

bool inbound(int nr, int nc);
bool checkGame(int row, int col, int color);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N; cin >> N; int game_set{ 0 };
    for (int i = 1; i <= N ; i++) {
        int row, col; cin >> row >> col;
        if (i % 2 == 1) {
            BOARD[row][col] = 1;
            if (checkGame(row,col,1) && game_set == 0) {
                game_set = i;
            }
        }
        else {
            BOARD[row][col] = 2;
            if (checkGame(row, col, 2) && game_set == 0) {
                game_set = i;
            }
        }
    }

    if (game_set == 0) {
        cout << -1;
    }
    else {
        cout << game_set;
    }

}


bool checkGame(int row, int col, int color) {

    for (int i = 0; i < 4; i++) {
        queue<pair<int, int>>q; bool VISITED[20][20] = {}; int cnt{ 0 };
        q.push({ row,col }); VISITED[row][col] = true; cnt++;

        while (!q.empty()) {
            pair<int, int>now = q.front(); q.pop();

            for (int d = 0; d < 2; d++) {
                int nr = now.first + CASES[i][d][0]; int nc = now.second + CASES[i][d][1];
                if (inbound(nr, nc) && BOARD[nr][nc] == color && VISITED[nr][nc] == false) {
                    q.push({ nr,nc }); VISITED[nr][nc] = true; cnt++;
                }
            }


        }

        if (cnt == 5) {
            return true;
        }
    }

    return false;
}

bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= 19 && nc >= 1 && nc <= 19) {
        return true;
    }
    return false;
}