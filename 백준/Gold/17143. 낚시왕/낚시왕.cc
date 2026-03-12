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
const int DR[5] = { 0, -1, 1, 0, 0 };
const int DC[5] = { 0, 0, 0, 1, -1 };

struct Shark {
    int speed;
    int direction;
    int size;
};

int fishKing;
vector<Shark> Matrix[101][101];

int R, C, M;

bool inbound(int nr, int nc);
void debugMatrix();
void debugMatrix(const vector<Shark> CopiedMatrix[101][101]);

void directionChange(Shark& shark);
bool sizeGreater(Shark A, Shark B);

int simulateFishGame();
bool fishKingmove();
int catchShark();
void moveShark();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> R >> C >> M;

    fishKing = 0;
    for (int i = 0; i < M; i++) {
        int  r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        Matrix[r][c].push_back({ s,d,z });
    }

    cout << simulateFishGame();

}

int simulateFishGame() {
    int sum_size{ 0 };

    while (fishKingmove()) {
        sum_size += catchShark();
        moveShark();
    }

    return sum_size;
}

bool fishKingmove() {
    fishKing++;
    if (fishKing == C + 1) {
        return false;
    }
    return true;
}

int catchShark() {
    int now_row = 1;
    while (now_row <= R) {
        if (Matrix[now_row][fishKing].size() != 0) {
            int shark_size = Matrix[now_row][fishKing][0].size;
            Matrix[now_row][fishKing].pop_back();
            return shark_size;
        }
        now_row++;
    }
    return 0;
}

void moveShark() {
    Shark CopiedMatrix[101][101] = {};
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            CopiedMatrix[row][col] = { 0,0,0 };
        }
    }

    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            if (Matrix[row][col].size() != 0) {
                Shark shark = Matrix[row][col][0];
                int now_row = row; int now_col = col; int moved_cnt{ 0 }; int speed;
                if (shark.direction == 1 || shark.direction == 2) {
                    speed = shark.speed % (R * 2 - 2);
                }
                else if(shark.direction == 3 || shark.direction == 4) {
                    speed = shark.speed % (C * 2 - 2);
                }
                
                while (moved_cnt < speed) {
                    int nr = now_row + DR[shark.direction]; int nc = now_col + DC[shark.direction];
                    if (inbound(nr, nc)) {
                        now_row = nr; now_col = nc;
                        moved_cnt++;
                    }
                    else {
                        directionChange(shark);
                    }
                }
                
                if (CopiedMatrix[now_row][now_col].size < shark.size) {
                    CopiedMatrix[now_row][now_col] = shark;
                }
                
            }
        }
    }
    
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            Matrix[row][col].clear();
            if (CopiedMatrix[row][col].size != 0) {
                Matrix[row][col].push_back(CopiedMatrix[row][col]);
            }
        }
    }
    
}


bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= R && nc >= 1 && nc <= C) {
        return true;
    }
    return false;
}

void directionChange(Shark& shark) {
    if (shark.direction == 1) {
        shark.direction = 2;
    }
    else if (shark.direction == 2) {
        shark.direction = 1;
    }
    else if (shark.direction == 3) {
        shark.direction = 4;
    }
    else if (shark.direction == 4) {
        shark.direction = 3;
    }
}

bool sizeGreater(Shark A, Shark B) {
    return A.size > B.size;
}

void debugMatrix() {
    cout << fishKing << endl;
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            if (Matrix[row][col].size() != 0) {
                cout << Matrix[row][col][0].speed << ',' << Matrix[row][col][0].size << ' ';
            }
            else {
                cout << "(0,0)" << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void debugMatrix(const vector<Shark> CopiedMatrix[101][101]) {
    cout << fishKing << endl;
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            if (CopiedMatrix[row][col].size() != 0) {
                cout << CopiedMatrix[row][col][0].speed << ',' << CopiedMatrix[row][col][0].size << ' ';
            }
            else {
                cout << "(0,0)" << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}