#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;  // → ↑ ← ↓ y x
const int Dir[4][2] = {{0,1},{-1,0},{0,-1},{1,0}}; 
bool Matrix[101][101];
int N;

struct DragonCurve {
    int x;
    int y;
    int d;
    int g;
    int prevDir[1024];

    void makeImprint() {
        Matrix[y][x] = true; int size{ 0 };
        y += Dir[d][0]; x += Dir[d][1]; prevDir[0] = d; size++;
        Matrix[y][x] = true;
        
        for (int i = 0; i < g; i++) {
            int cnt = size;
            for (int j = cnt-1; j >= 0; j--) {
                int nd = (prevDir[j] + 1) % 4; 
                y += Dir[nd][0]; x += Dir[nd][1]; prevDir[size] = nd; size++;
                Matrix[y][x] = true;
            }
        } 
    }
};

struct Rectangle {
    pair<int, int>LU = { 0,0 }; 
    pair<int, int>RU = { 0,1 };
    pair<int, int>LD = { 1,0 }; 
    pair<int, int>RD = { 1,1 };
    int ans{ 0 };
};

int findDragonCurve() {
    Rectangle rectangle;
    for (int r = 0; r < 100; r++) {
        int ar = rectangle.LU.first + r;
        int br = rectangle.RU.first + r;
        int cr = rectangle.LD.first + r;
        int dr = rectangle.RD.first + r;
        for (int c = 0; c < 100; c++) {
            int ac = rectangle.LU.second + c;
            int bc = rectangle.RU.second + c;
            int cc = rectangle.LD.second + c;
            int dc = rectangle.RD.second + c;
            if (Matrix[ar][ac] == true && Matrix[br][bc] == true && Matrix[cr][cc] == true && Matrix[dr][dc] == true) {
                rectangle.ans++;
            }
        }
    }
    return rectangle.ans;
}

void checkMatrix();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N ; i++) {
        DragonCurve dragoncurve;
        cin >> dragoncurve.x >> dragoncurve.y >> dragoncurve.d >> dragoncurve.g;
        dragoncurve.makeImprint();
    }
    cout << findDragonCurve();

    return 0;
}

void checkMatrix() {
    for (int row = 0; row <= 10; row++) {
        for (int col = 0; col <= 10; col++) {
            cout << Matrix[row][col] << ' ';
        }
        cout << endl;
    }
}