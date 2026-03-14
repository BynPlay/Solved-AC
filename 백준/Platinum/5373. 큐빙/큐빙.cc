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
const int INF { INT_MAX };

enum side { U = 0, D, F, B, L, R };

int n;

struct Cube {
    char side[6][3][3];

    Cube(char u, char d, char f, char b, char l, char r) {
        char color[6] = { u, d, f, b, l, r };
        for (int s = 0; s < 6; s++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    side[s][i][j] = color[s];
                }
            }
        }
    }

    void rollUpSide(char dir); 
    void rollDownSide(char dir);
    void rollFrontSide(char dir);
    void rollBackSide(char dir);
    void rollLeftSide(char dir);
    void rollRightSide(char dir);
};

void Cube::rollUpSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }
    
    for (int cnt = 0; cnt < move; cnt++) {
        for (int col = 0; col < 3; col++) {
            char tmp = side[F][0][col];
            side[F][0][col] = side[R][0][col];
            side[R][0][col] = side[B][0][col];
            side[B][0][col] = side[L][0][col];
            side[L][0][col] = tmp;
        }

        char copied_cube[3][3]; memcpy(copied_cube, side[U], sizeof(side[U]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[U][3 - 1 - col][row];
            }
        }
        memcpy(side[U], copied_cube, sizeof(copied_cube));
    }
}

void Cube::rollDownSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }

    for (int cnt = 0; cnt < move; cnt++) {
        for (int col = 0; col < 3; col++) {
            char tmp = side[L][2][col];
            side[L][2][col] = side[B][2][col];
            side[B][2][col] = side[R][2][col];
            side[R][2][col] = side[F][2][col];
            side[F][2][col] = tmp;
        }

        char copied_cube[3][3]; memcpy(copied_cube, side[D], sizeof(side[D]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[D][3 - 1 - col][row];
            }
        }
        memcpy(side[D], copied_cube, sizeof(copied_cube));
    }
}


void Cube::rollFrontSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }

    for (int cnt = 0; cnt < move; cnt++) {
        for (int i = 0; i < 3; i++) {
            char tmp = side[R][i][0];
            side[R][i][0] = side[U][2][i];
            side[U][2][i] = side[L][2 - i][2];
            side[L][2 - i][2] = side[D][0][2 - i];
            side[D][0][2 - i] = tmp;
        }

        char copied_cube[3][3]; memcpy(copied_cube, side[F], sizeof(side[F]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[F][3 - 1 - col][row];
            }
        }
        memcpy(side[F], copied_cube, sizeof(copied_cube));
    }
}


void Cube::rollBackSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }

    for (int cnt = 0; cnt < move; cnt++) {
        for (int i = 0; i < 3; i++) {
            char tmp = side[D][2][2 - i];
            side[D][2][2 - i] = side[L][2 - i][0];
            side[L][2 - i][0] = side[U][0][i];
            side[U][0][i] = side[R][i][2];
            side[R][i][2] = tmp;
        }

        char copied_cube[3][3]; memcpy(copied_cube, side[B], sizeof(side[B]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[B][3 - 1 - col][row];
            }
        }
        memcpy(side[B], copied_cube, sizeof(copied_cube));
    }
}
   

void Cube::rollLeftSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }

    for (int cnt = 0; cnt < move; cnt++) {
        for (int row = 0; row < 3; row++) {

            char tmp = side[F][row][0];
            side[F][row][0] = side[U][row][0];
            side[U][row][0] = side[B][2-row][2];
            side[B][2-row][2] = side[D][row][0];
            side[D][row][0] = tmp;
        }


        char copied_cube[3][3]; memcpy(copied_cube, side[L], sizeof(side[L]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[L][3 - 1 - col][row];
            }
        }
        memcpy(side[L], copied_cube, sizeof(copied_cube));
    }
}


void Cube::rollRightSide(char dir) {
    int move;
    if (dir == '+') {
        move = 1;
    }
    else {
        move = 3;
    }

    for (int cnt = 0; cnt < move; cnt++) {
        for (int row = 0; row < 3; row++) {

            char tmp = side[D][row][2];
            side[D][row][2] = side[B][2-row][0];
            side[B][2-row][0] = side[U][row][2];
            side[U][row][2] = side[F][row][2];
            side[F][row][2] = tmp;
        }

        char copied_cube[3][3]; memcpy(copied_cube, side[R], sizeof(side[R]));
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                copied_cube[row][col] = side[R][3 - 1 - col][row];
            }
        }
        memcpy(side[R], copied_cube, sizeof(copied_cube));
    }
}



void DebugDice(Cube cube);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        Cube cube('w', 'y', 'r', 'o', 'g', 'b');
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            char side = s[0]; char dir = s[1];
            if (side == 'U') {
                cube.rollUpSide(dir);
            }
            else if (side == 'D') {
                cube.rollDownSide(dir);
            }
            else if (side == 'F') {
                cube.rollFrontSide(dir);
            }
            else if (side == 'B') {
                cube.rollBackSide(dir);
            }
            else if (side == 'L') {
                cube.rollLeftSide(dir);
            }
            else if (side == 'R') {
                cube.rollRightSide(dir);
            }
        }
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                cout << cube.side[U][row][col];
            }
            cout << endl;
        }
    }

}

void DebugDice(Cube cube) {

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 12; col++) {
            if (col >= 3 && col < 6) {
                cout << cube.side[U][row][col-3];
            }
            else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 12; col++) {
            if (col >= 0 && col < 3) {
                cout << cube.side[L][row][col];
            }
            else if (col >= 3 && col < 6) {
                cout << cube.side[F][row][col - 3];
            }
            else if (col >= 6 && col < 9) {
                cout << cube.side[R][row][col - 6];
            }
            else if (col >= 9 && col < 12) {
                cout << cube.side[B][row][col - 9];
            }
        }
        cout << '\n';
    }
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 12; col++) {
            if (col >= 3 && col < 6) {
                cout << cube.side[D][row][col - 3];
            }
            else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
    cout << '\n';
}
