#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>

using namespace std; 
const int INF{ INT_MAX };
const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

struct Virus {
    int row;
    int col;
};

int N, M;
int Matrix[51][51];
Virus Viruses[10];
int min_ans{ INF };
int empty_cnt{ 0 };

void bruteForceSelectViruses(int idx, int cnt, bool Activated_viruses[10], int virus_cnt);
void virusSpread(bool Activated_viruses[10], int virus_cnt);
bool allInfected(int copied_matrix[51][51]);

int findMax(int copied_matrix[51][51]);
void checkMatrix();
void checkMatrix(int copied_matrix[51][51]);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M;
    int virus_cnt{ 0 };
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cin >> Matrix[row][col];
            if (Matrix[row][col] == 2) {
                Viruses[virus_cnt].row = row; Viruses[virus_cnt].col = col;
                virus_cnt++;
            }
            else if (Matrix[row][col] == 0) {
                empty_cnt++;
            }
        }
    }
    bool Activated_viruses[10] = {};
    bruteForceSelectViruses(0, 0, Activated_viruses, virus_cnt);
    if (min_ans == INF) {
        cout << -1;
    }
    else {
        cout << min_ans;
    }

    return 0;
}


void bruteForceSelectViruses(int idx, int cnt, bool Activated_viruses[10], int virus_cnt) {

    if (cnt == M) {
        virusSpread(Activated_viruses, virus_cnt);
        return;
    }

    for (int i = idx; i < virus_cnt; i++) {
        Activated_viruses[i] = true;
        bruteForceSelectViruses(i + 1, cnt + 1, Activated_viruses, virus_cnt);
        Activated_viruses[i] = false;
    }
}

void virusSpread(bool Activated_viruses[10], int virus_cnt) {
    int copied_matrix[51][51] = {}; int emp = empty_cnt;
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (Matrix[row][col] == 1) {
                copied_matrix[row][col] = -3;
            }
            else if (Matrix[row][col] == 2) {
                for (int virus = 0; virus < virus_cnt; virus++) {
                    if (Activated_viruses[virus] == true) {
                        copied_matrix[Viruses[virus].row][Viruses[virus].col] = 0;
                    }
                    else {
                        copied_matrix[Viruses[virus].row][Viruses[virus].col] = -1;
                    }
                }
            }
            else {
                copied_matrix[row][col] = -2;
            }
        }
    }


    queue<pair<int, int>>q;

    for (int i = 0; i < 10; i++) {
        if (Activated_viruses[i] == true) {
            q.push({ Viruses[i].row,Viruses[i].col });
        }
    }

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop();

        if (emp == 0) {
            int time = findMax(copied_matrix);
            if (time < min_ans) {
                min_ans = time;
                //checkMatrix(copied_matrix);
            }
            return;
        }

        for (int d = 0; d < 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
                if (copied_matrix[nr][nc] == -2) {
                    q.push({ nr,nc });
                    copied_matrix[nr][nc] = copied_matrix[now.first][now.second] + 1;
                    emp--;
                }
                else if (copied_matrix[nr][nc] == -1) {
                    q.push({ nr,nc });
                    copied_matrix[nr][nc] = copied_matrix[now.first][now.second] + 1;
                }

            }
        }
    }

};

bool allInfected(int copied_matrix[51][51]) {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (copied_matrix[row][col] == -2) {
                return false;
            }
        }
    }
    return true;
}

int findMax(int copied_matrix[51][51]) {
    int max{ 0 };
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (copied_matrix[row][col] != -1 && copied_matrix[row][col] != -3) {
                if (max < copied_matrix[row][col]) {
                    max = copied_matrix[row][col];
                }
            }
        }
    }
    return max;
}


void checkMatrix() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cout << Matrix[row][col] << ' ';
        }
        cout << endl;
    }
}

void checkMatrix(int copied_matrix[51][51]) {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cout << copied_matrix[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}