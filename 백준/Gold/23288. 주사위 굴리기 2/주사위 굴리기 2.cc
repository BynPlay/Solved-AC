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
#include <deque>

using namespace std;
const int INF = { INT_MAX };

const int Dr[5] = {0,0,0,1,-1};
const int Dc[5] = {0,1,-1,0,0};

int N, M, K;
int MAP[21][21];
int ans_sum{ 0 };

bool inbound(int nr, int nc);
int calculateScore(int row, int col);

struct Dice {
    int row = 1; int col = 1; int dir = 1;

    int up = 1;
    int east = 3;
    int west = 4;
    int south = 5;
    int north = 2;
    int down = 6;

    void roll();
    void rollEast();  void rollWest(); void rollNorth(); void rollSouth();
};

void Dice::roll() {
    int nr = row + Dr[dir]; int nc = col + Dc[dir];
    if (!inbound(nr,nc)) {
        if (dir == 1) {
            dir = 2;
        }
        else if (dir == 2) {
            dir = 1;
        }
        else if (dir == 3) {
            dir = 4;
        }
        else if (dir == 4) {
            dir = 3;
        }
    }

    if (dir == 1) {
        rollEast();
    }
    else if (dir == 2) {
        rollWest();
    }
    else if (dir == 3) {
        rollSouth();
    }
    else if (dir == 4) {
        rollNorth();
    }

    ans_sum += calculateScore(row, col);

    int A = down; int B = MAP[row][col];
   
    if (A > B) {
        if (dir == 1) {
            dir = 3;
        }
        else if (dir == 2) {
            dir = 4;
        }
        else if (dir == 3) {
            dir = 2;
        }
        else if (dir == 4) {
            dir = 1;
        }
    }
    else if (A < B) {
        if (dir == 1) {
            dir = 4;
        }
        else if (dir == 2) {
            dir = 3;
        }
        else if (dir == 3) {
            dir = 1;
        }
        else if (dir == 4) {
            dir = 2;
        }
    }
}

void Dice::rollEast() {
    col += 1;
    int tmp = up;
    up = west;
    west = down;
    down = east;
    east = tmp;
}
void Dice::rollWest() {
    col -= 1;
    int tmp = up;
    up = east;
    east = down;
    down = west;
    west = tmp;
}
void Dice::rollNorth() {
    row -= 1;
    int tmp = up;
    up = south;
    south = down;
    down = north;
    north = tmp;
}
void Dice::rollSouth() {
    row += 1;
    int tmp = up;
    up = north;
    north = down;
    down = south;
    south = tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> M >> K;

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            cin >> MAP[row][col];
        }
    }
    Dice dice;

    for (int i = 0; i < K; i++) {
        dice.roll();
    }

    cout << ans_sum;
}

int calculateScore(int row, int col) {
    int B = MAP[row][col]; int C{ 0 };
    vector<vector<bool>>visited(N+1, vector<bool>(M+1, false));
    queue<pair<int, int>>q; q.push({ row,col }); visited[row][col] = true;

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop(); C++;

        for (int d = 1; d <= 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (inbound(nr, nc) && visited[nr][nc] == false && MAP[nr][nc] == B) {
                q.push({ nr,nc }); visited[nr][nc] = true;
            }
        }
    }

    return B * C;
}

bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}


