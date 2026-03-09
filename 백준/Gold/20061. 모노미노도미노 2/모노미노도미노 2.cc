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

int N;

bool Matrix[10][10];
int point{ 0 };

void pileBlock(int t, int x, int y);
void pile1x1(int x, int y);
void pile1x2(int x, int y);
void pile2x1(int x, int y);

void checkExplosion();
bool isExplosionGreen();
bool isExplosionBlue();

void deleteAndPullGreen(int r);
void deleteAndPullBlue(int c);

void checkSafeZone();

int countBlocks();
void debugMatrix();


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N;
    for (int n = 0; n < N ; n++) {
        int t, x, y;
        cin >> t >> x >> y;
        pileBlock(t, x, y);
        checkExplosion(); 
        checkSafeZone();
    }

    cout << point << '\n';
    cout << countBlocks();

}


void pileBlock(int t, int x, int y) {
    if (t == 1) {
        pile1x1(x, y);

    }
    if (t == 2) {
        pile1x2(x, y);
    }
    if (t == 3) {
        pile2x1(x, y);
    }
}

void pile1x1(int x, int y) {
    int now = y;
    while (true) {
        if (Matrix[x][now] == true || now == 10) {
            Matrix[x][now - 1] = true;
            break;
        }
        now++;
    }

    now = x;
    while (true) {
        if (Matrix[now][y] == true || now == 10) {
            Matrix[now - 1][y] = true;
            break;
        }
        now++;
    }
}

void pile1x2(int x, int y) {
    int now = y;
    while (true) {
        if (Matrix[x][now] == true || now == 10) {
            Matrix[x][now - 1] = true;
            Matrix[x][now - 2] = true;
            break;
        }
        now++;
    }

    now = x;
    while (true) {
        if (Matrix[now][y] == true || Matrix[now][y+1] == true || now == 10) {
            Matrix[now - 1][y] = true;
            Matrix[now - 1][y+1] = true;
            break;
        }
        now++;
    }
}

void pile2x1(int x, int y) {
    int now = y;
    while (true) {
        if (Matrix[x][now] == true || Matrix[x+1][now] == true || now == 10) {
            Matrix[x][now-1] = true;
            Matrix[x+1][now-1] = true;
            break;
        }
        now++;
    }

    now = x;
    while (true) {
        if (Matrix[now][y] == true || now == 10) {
            Matrix[now - 1][y] = true;
            Matrix[now - 2][y] = true;
            break;
        }
        now++;
    }
}


void checkExplosion() {

    while (isExplosionGreen());
    while (isExplosionBlue());

}

bool isExplosionGreen() {
    for (int row = 9; row >= 6; row--) {
        bool is_success{ true };
        for (int col = 0; col < 4; col++) {
            if (Matrix[row][col] == false) {
                is_success = false;
                break;
            }
        }
        if (is_success == true) {
            deleteAndPullGreen(row);
            point++;
            return true;
        }
    }
    return false;
}
;
bool isExplosionBlue() {
    for (int col = 9; col >= 6; col--) {
        bool is_success{ true };
        for (int row = 0; row < 4; row++) {
            if (Matrix[row][col] == false) {
                is_success = false;
                break;
            }
        }
        if (is_success == true) {
            deleteAndPullBlue(col);
            point++;
            return true;
        }
    }
    return false;
}

void deleteAndPullGreen(int r) {
    for (int row = r; row > 4; row--) {
        for (int col = 0; col < 4; col++) {
            Matrix[row][col] = Matrix[row - 1][col];
        }
    }
    for (int col = 0; col < 4; col++) {
        Matrix[4][col] = 0;
    }
}

void deleteAndPullBlue(int c) {
    for (int col = c; col > 4; col--) {
        for (int row = 0; row < 4; row++) {
            Matrix[row][col] = Matrix[row][col - 1];
        }
    }
    for (int row = 0; row < 4; row++) {
        Matrix[row][4] = 0;
    }
}


void checkSafeZone() {
    bool isGreenFind{ false };
    for (int row = 4; row < 6; row++) {

        if (isGreenFind == true) {
            break;
        }

        for (int col = 0; col < 4; col++) {
            if (isGreenFind == true) {
                break;
            }

            if (Matrix[row][col] == true) {
                isGreenFind = true;
                if (row == 4) {
                    deleteAndPullGreen(9);
                    deleteAndPullGreen(9);
                }
                else if (row == 5) {
                    deleteAndPullGreen(9);
                }
            }
        }
    }

    bool isBlueFind{ false };
    for (int col = 4; col < 6; col++) {
        if (isBlueFind == true) {
            break;
        }
        for (int row = 0; row < 4; row++) {
            if (isBlueFind == true) {
                break;
            }

            if (Matrix[row][col] == true) {
                isBlueFind = true;
                if (col == 4) {
                    deleteAndPullBlue(9);
                    deleteAndPullBlue(9);
                }
                else if (col == 5) {
                    deleteAndPullBlue(9);
                }
            }
        }
    }
}

int countBlocks() {
    int sum{ 0 };
    for (int row = 4; row < 10 ;row++) {
        for (int col = 0; col < 4; col++) {
            if (Matrix[row][col] == true) {
                sum++;
            }
        }
    }
    for (int col = 4; col < 10; col++) {
        for (int row = 0; row < 4; row++) {
            if (Matrix[row][col] == true) {
                sum++;
            }
        }
    }

    return sum;
}

void debugMatrix() {
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            cout << Matrix[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}



