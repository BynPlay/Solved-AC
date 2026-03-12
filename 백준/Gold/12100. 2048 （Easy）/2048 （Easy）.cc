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

using namespace std;
const int INF = { INT_MAX };

const int Dr[4] = { -1,1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

int N;

int BOARD[21][21];
bool FUSIONED[21][21];

int max_ans{ 0 };

int boardSimulation(const vector<int> arr) {
    int COPIEDBOARD[21][21]; memcpy(COPIEDBOARD, BOARD, sizeof(BOARD));

    for (auto& a : arr) {
        if (a == 1) {
            for (int row = 1; row <= N; row++) {
                for (int col = 1; col <= N; col++) {
                    int cur = row;
                    while (cur > 1) {
                        if (COPIEDBOARD[cur - 1][col] != 0) {
                            if (COPIEDBOARD[cur - 1][col] == COPIEDBOARD[cur][col] && FUSIONED[cur - 1][col] == false) {
                                COPIEDBOARD[cur - 1][col] *= 2;
                                COPIEDBOARD[cur][col] = 0;
                                FUSIONED[cur - 1][col] = true;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        COPIEDBOARD[cur - 1][col] = COPIEDBOARD[cur][col];
                        COPIEDBOARD[cur][col] = 0; cur--;
                    }
                }
            }
        }

        else if (a == 2) {
            for (int row = N; row >= 1; row--) {
                for (int col = 1; col <= N; col++) {
                    int cur = row;
                    while (cur < N) {
                        if (COPIEDBOARD[cur + 1][col] != 0) {
                            if (COPIEDBOARD[cur + 1][col] == COPIEDBOARD[cur][col] && FUSIONED[cur + 1][col] == false) {
                                COPIEDBOARD[cur + 1][col] *= 2;
                                COPIEDBOARD[cur][col] = 0;
                                FUSIONED[cur + 1][col] = true;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        COPIEDBOARD[cur + 1][col] = COPIEDBOARD[cur][col];
                        COPIEDBOARD[cur][col] = 0; cur++;
                    }
                }
            }
        }

        else if (a == 3) {
            for (int col = 1; col <= N; col++) {
                for (int row = 1; row <= N; row++) {
                    int cur = col;
                    while (cur > 1) {
                        if (COPIEDBOARD[row][cur - 1] != 0) {
                            if (COPIEDBOARD[row][cur - 1] == COPIEDBOARD[row][cur] && FUSIONED[row][cur - 1] == false) {
                                COPIEDBOARD[row][cur - 1] *= 2;
                                COPIEDBOARD[row][cur] = 0;
                                FUSIONED[row][cur - 1] = true;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        COPIEDBOARD[row][cur - 1] = COPIEDBOARD[row][cur];
                        COPIEDBOARD[row][cur] = 0; cur--;
                    }
                }
            }
        }

        else if (a == 4) {
            for (int col = N; col >= 1; col--) {
                for (int row = 1; row <= N; row++) {
                    int cur = col;
                    while (cur < N) {
                        if (COPIEDBOARD[row][cur+1] != 0) {
                            if (COPIEDBOARD[row][cur+1] == COPIEDBOARD[row][cur] && FUSIONED[row][cur+1] == false) {
                                COPIEDBOARD[row][cur + 1] *= 2;
                                COPIEDBOARD[row][cur] = 0;
                                FUSIONED[row][cur+1] = true;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        COPIEDBOARD[row][cur+1] = COPIEDBOARD[row][cur];
                        COPIEDBOARD[row][cur] = 0; cur++;
                    }
                }
            }
        }
        memset(FUSIONED, false, sizeof(FUSIONED));
    }
    int max_blocks{ 0 };

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (COPIEDBOARD[row][col] > max_blocks) {
                max_blocks = COPIEDBOARD[row][col];
            }
        }
    }

    return max_blocks;
}

void bruteForceCnt(int depth, vector<int>& arr) {

    if (depth == 5) {
        int max_blocks = boardSimulation(arr);
        if (max_blocks > max_ans) {
            max_ans = max_blocks;
        }
        return;
    }

    for (int i = 1; i <= 4; i++) {
        arr.push_back(i);
        bruteForceCnt(depth + 1, arr);
        arr.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cin >> BOARD[row][col];
        }
    }

    vector<int> arr;
    bruteForceCnt(0, arr);

    cout << max_ans;
}