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

const int DR[4] = { 1, -1, 0, 0 };
const int DC[4] = { 0, 0, 1, -1 };

int N, M;
char MAP[1001][1001];

int MAPID[1001][1001];
map<int, int>IDCNT;

struct Blank {
    int row;
    int col;
};

bool inbound(int nr, int nc);

void findMove(int row, int col, vector<vector<bool>>& VISITED, const int& id);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M;

    for (int row = 1; row <= N ; row++) {
        string rows; cin >> rows;
        for (int col = 1; col <= M; col++) {
            MAP[row][col] = rows[col - 1];
        }
    }

    vector<vector<bool>> VISITED(N + 1, vector<bool>(M + 1, false)); int id{ 1 };

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            if (MAP[row][col] == '0' && VISITED[row][col] == false) {
                findMove(row, col, VISITED, id); id++;
            }
        }
    }

    vector<vector<int>> ANS(N + 1, vector<int>(M + 1, 0));
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            if (MAP[row][col] == '1') {
                set<int>s; ANS[row][col] += 1;
                for (int d = 0; d < 4; d++) {
                    int nr = row + DR[d]; int nc = col + DC[d];
                    if (inbound(nr,nc) && MAP[nr][nc] == '0') {
                        s.insert(MAPID[nr][nc]);
                    }
                }
                for (auto& i : s) {
                    ANS[row][col] += IDCNT[i];
                }
            }
        }
    }

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            cout << ANS[row][col] % 10;
        }
        cout << endl;
    }

}

void findMove(int row, int col, vector<vector<bool>>& VISITED, const int& id) {
    queue<Blank>q; q.push({ row,col }); VISITED[row][col] = true; int cnt{ 1 };

    while (!q.empty()) {
        Blank now = q.front(); q.pop();
        MAPID[now.row][now.col] = id;

        for (int d = 0; d < 4; d++) {
            int nr = now.row + DR[d]; int nc = now.col + DC[d];
            if (inbound(nr, nc) && MAP[nr][nc] == '0' && VISITED[nr][nc] == false) {
                q.push({ nr,nc }); VISITED[nr][nc] = true; cnt++;
            }
        }
    }

    IDCNT[id] = cnt;
}

bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}
