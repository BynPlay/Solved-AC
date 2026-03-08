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

using namespace std; 
// 1 - 오른쪽, 2 - 왼쪽 3 - 위쪽 4 - 아래쪽 // 0 - 처음 1, 2, 3 - 이후
const int SpreadWindRow[5][4] = { {}, {0,-1,0,1}, {0,-1,0,1}, {-1,-1,-1,-1}, {1,1,1,1} };
const int SpreadWindCol[5][4] = { {}, {1,1,1,1}, {-1,-1,-1,-1}, {0,-1,0,1}, {0,-1,0,1} };
int Dir[5][2] = { {}, {0,1}, {0,-1}, {-1,0}, {1,0} };

int R, C, K;
int W;
int Room[21][21];
bool Wall[21][21][5]; // L / R / U / D   0 - 아래위 1 - 왼오른 벽


struct Heater{
    int row;
    int col;
    int dir{ 0 };
    int tmp[21][21] = {};

    void makeWind() {
        queue<tuple<int, int,int>>q; 
        int nr = row + SpreadWindRow[dir][0]; int nc = col + SpreadWindCol[dir][0];
        if (nr >= 1 && nr <= R && nc >= 1 && nc <= C) {
            tmp[nr][nc] = 5;
            q.push({ nr,nc,5 - 1 });
        }
        
        while (!q.empty()) {
            tuple<int, int, int>now = q.front(); q.pop();

            for (int d = 1; d <= 3; d++) {
                int nr = get<0>(now) + SpreadWindRow[dir][d]; int nc = get<1>(now) + SpreadWindCol[dir][d];
                if (nr >= 1 && nr <= R && nc >= 1 && nc <= C && checkWall(get<0>(now), get<1>(now), nr, nc)) {
                    tmp[nr][nc] = get<2>(now);
                    if (get<2>(now) >= 2) {
                        q.push({ nr,nc,get<2>(now)-1 });
                    }
                }
            }
        }
        
        addRoomTmp();
    }

    bool checkWall(int now_row, int now_col, int nr, int nc) {
        

        if (dir == 1 || dir == 2) {
            if (Wall[nr][now_col][dir] == true) {
                return false;
            }

            if (nr - now_row == -1 && Wall[now_row][now_col][3] == true) {
                return false;
            }
            else if (nr - now_row == 1 && Wall[now_row][now_col][4] == true) {
                return false;
            }
        }

        if (dir == 3 || dir == 4) {
            if (Wall[now_row][nc][dir] == true) {
                return false;
            }

            if (nc - now_col == -1 && Wall[now_row][now_col][2] == true) {
                return false;
            }
            else if (nc - now_col == 1 && Wall[now_row][now_col][1] == true) {
                return false;
            }
        }

        return true;
        
    }

    void addRoomTmp() {
        for (int x = 1; x <= R; x++) {
            for (int y = 1; y <= C; y++) {
                Room[x][y] += tmp[x][y];
            }
        }
    }

    void checkTmp() {
        for (int x = 1; x <= R; x++) {
            for (int y = 1; y <= C; y++) {
                cout << tmp[x][y] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
};

Heater heaters[21][21];
bool checkSlot[21][21];

void temperatureSpread();
void temperatureDownEdge();

bool isFinished();

void checkRoom();
//void checkWall();


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   //freopen("input.txt", "r", stdin);
   cin >> R >> C >> K;
    
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            int a; cin >> a;
            if (a >= 1 && a <= 4) {
                heaters[row][col].row = row;
                heaters[row][col].col = col;
                heaters[row][col].dir = a;
            }
            else if (a == 5) {
                checkSlot[row][col] = true;
            }
        }
    }

    cin >> W;

    
    for (int i = 0; i < W; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        if (t == 0) {
            Wall[x][y][3] = true; 
            if (x-1 >= 1) {
                Wall[x-1][y][4] = true; 
            }
        }
        else if (t == 1) {
            Wall[x][y][1] = true; 
            if (y + 1 <= C) {
                Wall[x][y+1][2] = true;
            } 
        }
    }

    int chocolate{ 0 };
    while (true) {
        for (int row = 1; row <= R; row++) {
            for (int col = 1; col <= C; col++) {
                if (heaters[row][col].dir != 0) {
                    heaters[row][col].makeWind();
                }
            }
        }
        temperatureSpread();
        temperatureDownEdge();
        chocolate++;
        if (isFinished() || chocolate == 101) {
            break;
        }
    }
    
    cout << chocolate;
    return 0;
}

void temperatureSpread() {
    int tmpRoom[21][21] = {};
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            int spread_sum{ 0 }; 
            for (int d = 1; d <= 4; d++) {
                int nr = row + Dir[d][0]; int nc = col + Dir[d][1];
                if (nr >= 1 && nr <= R && nc >= 1 && nc <= C && Wall[row][col][d] == false) {
                    int movetmp = (Room[row][col] - Room[nr][nc]) / 4;
                    if (movetmp > 0) {
                        tmpRoom[nr][nc] += movetmp; spread_sum += movetmp;
                    }
                }
            }
            tmpRoom[row][col] -= spread_sum;
        }
    }
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            Room[row][col] += tmpRoom[row][col];
        }
    }
}

void temperatureDownEdge(){
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            if (row == 1 || row == R || col == 1 || col == C) {
                if (Room[row][col] >= 1) {
                    Room[row][col]--;
                }
            }
        }
    }
}


bool isFinished() {
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            if (checkSlot[row][col] == true && Room[row][col] < K) {
                return false;
            }
        }
    }
    return true;
}

void checkRoom() {
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            cout << Room[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

/*
void checkWall() {
    for (int row = 1; row <= R; row++) {
        for (int col = 1; col <= C; col++) {
            bool no_wall = true;
            for (int depth = 0; depth < 1; depth++) {
                if (Wall[row][col][depth] != '\0') {
                    cout << Wall[row][col];
                    no_wall = false;
                }
            }
            if (no_wall == true) {
                cout << '0';
            }
            cout << ' ';

        }
        cout << endl;
    }
    cout << endl;
}
*/

