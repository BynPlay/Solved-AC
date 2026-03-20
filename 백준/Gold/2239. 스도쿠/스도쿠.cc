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
const int INF{ INT_MAX };

char SUDOKU[10][10];
char SUDOKUANS[10][10];

bool visitedRow[10][10];
bool visitedCol[10][10];
bool visitedBox[10][10];

bool solved{ false };

void checkMatrix();
int checkWhichBox(int row, int col);
void backTracking(int row_idx, int col_idx);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    for (int row = 1; row <= 9; row++) {
        string s; cin >> s;
        for (int col = 1; col <= 9; col++) {
            SUDOKU[row][col] = s[col - 1];
            if (SUDOKU[row][col] != '0') {
                visitedRow[row][SUDOKU[row][col] - '0'] = true;
                visitedCol[col][SUDOKU[row][col] - '0'] = true;
                visitedBox[checkWhichBox(row, col)][SUDOKU[row][col] - '0'] = true;
            }
        }
    }

    backTracking(1, 1);
    checkMatrix();

}

void backTracking(int row_idx, int col_idx) {

    if (row_idx == 10) {
        solved = true;
        return;
    }

    if (SUDOKU[row_idx][col_idx] != '0') {

        int reset_row = row_idx; int reset_col = col_idx;

        if (reset_col < 9) {
            reset_col++;
        }
        else {
            reset_col = 1;
            reset_row++;
        }

        backTracking(reset_row, reset_col);

    }
    else {

        for (int num = 1; num <= 9; num++) {

            if (solved) return;

            if (visitedRow[row_idx][num] == true) { continue; }
            if (visitedCol[col_idx][num] == true) { continue; }
            if (visitedBox[checkWhichBox(row_idx, col_idx)][num] == true) { continue; }

            SUDOKU[row_idx][col_idx] = '0' + num;
            visitedRow[row_idx][num] = true;
            visitedCol[col_idx][num] = true;
            visitedBox[checkWhichBox(row_idx, col_idx)][num] = true;

            int reset_row = row_idx; int reset_col = col_idx;

            if (reset_col < 9) {
                reset_col++;
            }
            else {
                reset_col = 1;
                reset_row++;
            }

            backTracking(reset_row, reset_col);

            if (solved) return;

            SUDOKU[row_idx][col_idx] = '0';
            visitedRow[row_idx][num] = false;
            visitedCol[col_idx][num] = false;
            visitedBox[checkWhichBox(row_idx, col_idx)][num] = false;

        }

    }

}

int checkWhichBox(int row, int col) {

    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        return 1;
    }
    else if (row >= 1 && row <= 3 && col >= 4 && col <= 6) {
        return 2;
    }
    else if (row >= 1 && row <= 3 && col >= 7 && col <= 9) {
        return 3;
    }
    else if (row >= 4 && row <= 6 && col >= 1 && col <= 3) {
        return 4;
    }
    else if (row >= 4 && row <= 6 && col >= 4 && col <= 6) {
        return 5;
    }
    else if (row >= 4 && row <= 6 && col >= 7 && col <= 9) {
        return 6;
    }
    else if (row >= 7 && row <= 9 && col >= 1 && col <= 3) {
        return 7;
    }
    else if (row >= 7 && row <= 9 && col >= 4 && col <= 6) {
        return 8;
    }
    else if (row >= 7 && row <= 9 && col >= 7 && col <= 9) {
        return 9;
    }

    return -1;
}

void checkMatrix() {
    for (int row = 1; row <= 9; row++) {
        for (int col = 1; col <= 9; col++) {
            cout << SUDOKU[row][col];
        }
        cout << '\n';
    }
    cout << '\n';
}