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

int N, M;
char BOARD[11][11];
int const DR[4] = { 1,-1,0,0 };
int const DC[4] = { 0,0,1,-1 };

int min_ans{ INF };

bool inbound(int nr, int nc);

bool GameOver{ false };
bool GameWin{ false };

struct Ball {
    int row;
    int col;
    char color;
    bool in_hall{ false };

    bool moveBall(int dir, char COPIEDBOARD[11][11]);
};

bool Ball::moveBall(int dir, char COPIEDBOARD[11][11]) {
    if (in_hall == false) {
        
        int nr = row + DR[dir]; int nc = col + DC[dir];

        if (COPIEDBOARD[nr][nc] == 'O') {
            if (color == 'R') {
                GameWin = true;
            }
            if (color == 'B') {
                GameOver = true;
            }
            row = 0; col = 0; in_hall = true;
            return false;
        }

        else if (inbound(nr, nc) && COPIEDBOARD[nr][nc] != 'R' && COPIEDBOARD[nr][nc] != 'B') {
            row = nr; col = nc;
            return true;
        }

        else {
            return false;
        }

    }
    return false;
}

vector<Ball> balls;

bool inbound(int nr, int nc);
void DebugMatrix();


void turnBasket(int dir);
void bruteForceTry(int depth, vector<int>& selectedDir);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int row = 1; row <= N ; row++) {
        string cols; cin >> cols;
        for (int col = 1; col <= M; col++) {
            if (cols[col - 1] == 'R' || cols[col - 1] == 'B') {
                balls.push_back({ row,col,cols[col - 1] });
            }
            BOARD[row][col] = cols[col - 1];
        }
    }
    vector<int> selectedDir;

    //DebugMatrix();

    bruteForceTry(0, selectedDir);

    if (min_ans == INF) {
        cout << -1;
    }
    else {
        cout << min_ans;
    }

}

void turnBasket(int dir, char COPIEDBOARD[11][11], vector<Ball>& copied_balls) {

        if (dir == 0) {
            sort(copied_balls.begin(), copied_balls.end(), [](Ball A, Ball B) { return A.row > B.row; });
            for (auto& ball : copied_balls) {
                COPIEDBOARD[ball.row][ball.col] = '.';
                while (ball.moveBall(dir, COPIEDBOARD));
                COPIEDBOARD[ball.row][ball.col] = ball.color;
            }
        }

        else if (dir == 1) {
            sort(copied_balls.begin(), copied_balls.end(), [](Ball A, Ball B) { return A.row < B.row; });
            for (auto& ball : copied_balls) {
                COPIEDBOARD[ball.row][ball.col] = '.';
                while (ball.moveBall(dir, COPIEDBOARD));
                COPIEDBOARD[ball.row][ball.col] = ball.color;
            }
        }

        else if (dir == 2) {
            sort(copied_balls.begin(), copied_balls.end(), [](Ball A, Ball B) { return A.col > B.col; });
            for (auto& ball : copied_balls) {
                COPIEDBOARD[ball.row][ball.col] = '.';
                while (ball.moveBall(dir, COPIEDBOARD));
                COPIEDBOARD[ball.row][ball.col] = ball.color;
            }
        }

        else if (dir == 3) {
            sort(copied_balls.begin(), copied_balls.end(), [](Ball A, Ball B) { return A.col < B.col; });
            for (auto& ball : copied_balls) {
                COPIEDBOARD[ball.row][ball.col] = '.';
                while (ball.moveBall(dir, COPIEDBOARD));
                COPIEDBOARD[ball.row][ball.col] = ball.color;
            }
        }
}


void bruteForceTry(int depth, vector<int>& selectedDir) {

    if (depth == 10) {
        int cnt{ 0 };

        char COPIEDBOARD[11][11]; memcpy(COPIEDBOARD, BOARD, sizeof(BOARD));
        vector<Ball>copied_balls = balls;

        for (auto& dir : selectedDir) {
            cnt++;
            turnBasket(dir, COPIEDBOARD, copied_balls);

            if (GameOver == true) {
                GameOver = false; GameWin = false;
                return;
            }

            else if (GameWin == true) {
                GameWin = false;
                if (cnt < min_ans) {
                    min_ans = cnt;
                }
                //DebugMatrix();
                return;
            }
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        selectedDir.push_back(i);
        bruteForceTry(depth + 1, selectedDir);
        selectedDir.pop_back();
    }
}



bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M && BOARD[nr][nc] != '#') {
        return true;
    }
    return false;
}


void DebugMatrix() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            cout << BOARD[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}