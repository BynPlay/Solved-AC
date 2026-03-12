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

const int Dr[8] = { -1,-1,-1,0,0,1,1,1 };
const int Dc[8] = { -1,0,1,-1,1,-1,0,1 };

int N, M, K;
int GROUND[11][11];
deque<int> TREES[11][11];
deque<int> FOODS[11][11];

int A[11][11];

bool inBound(int nr, int nc);

void DebugGround();

int process();
void spring();
void summer();
void autumn();
void winter();


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M >> K;

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            GROUND[row][col] = 5;
            cin >> A[row][col];
        }
    }

    for (int tree = 0; tree < M; tree++) {
        int x, y, z;
        cin >> x >> y >> z;
        TREES[x][y].push_front(z);
    }

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            sort(TREES[row][col].begin(), TREES[row][col].end());
        }
    }

    cout << process();

}

void spring() {

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            for (int tree = 0; tree < TREES[row][col].size(); tree++) {
                    if (GROUND[row][col] - TREES[row][col][tree] >= 0) {
                        GROUND[row][col] -= TREES[row][col][tree]; TREES[row][col][tree] += 1;
                    }
                    else {
                        int size = TREES[row][col].size();
                        for (int cnt = tree; cnt < size; cnt++) {
                            FOODS[row][col].push_front(TREES[row][col].back());
                            TREES[row][col].pop_back();
                        }
                        break;
                    }
            }
        }
    }
}

void summer() {

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            while (FOODS[row][col].size() > 0) {
                GROUND[row][col] += FOODS[row][col].front() / 2;
                FOODS[row][col].pop_front();
            }
        }
    }
}

void autumn() {

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            for (int tree = 0; tree < TREES[row][col].size(); tree++)
            {
                if (TREES[row][col][tree] % 5 == 0)
                {
                    for (int d = 0; d < 8; d++)
                    {
                        int nr = row + Dr[d];
                        int nc = col + Dc[d];

                        if (inBound(nr, nc))
                        {
                            TREES[nr][nc].push_front(1);
                        }
                    }
                }
            }
        }
    }
}

void winter() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            GROUND[row][col] += A[row][col];
        }
    }
}

bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
        return true;
    }
    return false;
}


int process() {

    for (int i = 0; i < K; i++) {
        spring();
        summer();
        autumn();
        winter();
    }

    int ans{ 0 };

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            for (int tree = 0; tree < TREES[row][col].size(); tree++) {
                    ans++;
                }
            }
        }
    return ans;
}

void DebugGround() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cout << GROUND[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

/*
void DebugTree(deque<Tree>& TREES) {
    for (auto& tree : TREES) {
        cout << "Tree: " << tree.row << ' ' << tree.col << ' ' << tree.age << endl;
    }
    cout << endl;
}
*/