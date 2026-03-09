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
#include <cstring>

using namespace std; 
const int INF{ INT_MAX };

const int Dr[5][2] = { {},{0,1},{0,-1},{-1,0},{1,0} }; // →, ←, ↑, ↓

int N, K;
int Board[13][13];   
void debugMatrix();

struct Horse {
    int num;
    int row;
    int col;
    int dir;
    int uphorse{ 0 };

    bool move();
    bool is_Finished();
};

Horse Horses[11];

bool Horse:: move() {
    int nr = row + Dr[dir][0]; int nc = col + Dr[dir][1];
    int up = uphorse; int now = num;

    if (nr > N || nr < 1 || nc > N || nc < 1 || Board[nr][nc] == 2) {
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
        nr = row + Dr[dir][0];  nc = col + Dr[dir][1];

        if (nr > N || nr < 1 || nc > N || nc < 1 || Board[nr][nc] == 2) {
            return is_Finished();
        }
        else {
            return move();
        }

    }

    else if (Board[nr][nc] == 0) {
       
        row = nr; col = nc; 
        for (int i = 1; i <= K; i++) {
            if (Horses[i].uphorse == now) {
                Horses[i].uphorse = 0;
            }
        }

        while (true) {
            bool is_piled{ false };
            for (int i = 1; i <= K; i++) {
                if (i == up) {
                    Horses[up].row = nr; Horses[up].col = nc;
                    up = Horses[up].uphorse;
                    is_piled = true;
                    now = i;
                    break;
                }
            }
            if (is_piled == false) {
                break;
            }
        }

        for (int i = 1; i <= K; i++) {
            if (i != now && Horses[i].row == nr && Horses[i].col == nc && Horses[i].uphorse == 0) {
                Horses[i].uphorse = num;
            }
        }
        //debugMatrix();
        return is_Finished();
    }

    else if (Board[nr][nc] == 1) {
        row = nr; col = nc;
        
        for (int i = 1; i <= K; i++) {
            if (Horses[i].uphorse == now) {
                Horses[i].uphorse = 0;
            }
        }

        while (true) {
            bool is_piled{ false };
            for (int i = 1; i <= K; i++) {
                if (i == up) {
                    Horses[i].row = nr; Horses[i].col = nc;
                    up = Horses[i].uphorse;
                    Horses[i].uphorse = now;
                    now = i;
                    is_piled = true;
                    break;
                }
            }
            if (is_piled == false) {
                break;
            }
        }
        uphorse = 0;

        for (int i = 1; i <= K; i++) {
            if (i != num && Horses[i].row == nr && Horses[i].col == nc && Horses[i].uphorse == 0) {
                Horses[i].uphorse = now;
            }
        }
        //debugMatrix();
        return is_Finished();
    }
}

bool Horse::is_Finished() {
    for (int i = 1; i <= K; i++) {
        int up = Horses[i].uphorse; int now = i; int cnt = 1;
        while (true) {
            if (cnt >= 4) {
                return true;
            }
            bool is_piled{ false };
            for (int j = 1; j <= K; j++) {
                if (j == up) {
                    up = Horses[up].uphorse;
                    is_piled = true;
                    now = j;
                    cnt++;
                    break;
                }
            }
            if (is_piled == false) {
                break;
            }
        }
    }
    return false;
}

void debugMatrix() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            bool ishorse{ false };
            for (auto &i : Horses) {
                if (i.row == row && i.col == col) {
                    cout << i.num;
                    ishorse = true;
                }
            }
            if (ishorse == false) {
                cout << 0;
            }
            cout << ' ';
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> K;
    for (int row = 1; row <= N ; row++) {
        for (int col = 1; col <= N; col++) {
            cin >> Board[row][col];
        }
    }
    for (int i = 1; i <= K; i++) {
        Horse horse; horse.num = i;
        cin >> horse.row >> horse.col >> horse.dir;
        Horses[i] = horse;
    }

    int cnt{ 1 };
    while (cnt <= 1000) {
        bool gaem_finished{ false };
        for (int i = 1; i <= K; i++) {
            if (Horses[i].move()) {
                gaem_finished = true;
                break;
            }
        }
        if (gaem_finished == true) {
            break;
        }
        cnt++;
    }
    if (cnt == 1001) {
        cout << -1;
    }
    else {
        cout << cnt;
    }
}
