#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

struct Node {
    int row;
    int col;
    int cost;
};

bool upperWeight(const Node& A, const Node& B);
bool inbound(int nr, int nc);
void debugA();

int JAIL[102][102];
vector<pair<int, int>>CRIMER;

int h, w;

vector<vector<int>> djikstraFind(int row, int col);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {

        cin >> h >> w;

        for (int row = 1; row <= h; row++) {
            string rows; cin >> rows;
            for (int col = 1; col <= w; col++) {
                if (rows[col - 1] == '.') {
                    JAIL[row][col] = 0;
                }
                else if (rows[col - 1] == '*') {
                    JAIL[row][col] = 2;
                }
                else if (rows[col - 1] == '#') {
                    JAIL[row][col] = 1;
                }
                else if (rows[col - 1] == '$') {
                    JAIL[row][col] = 0;
                    CRIMER.push_back({ row,col });
                }
            }
        }

        vector<vector<int>>sangeun = djikstraFind(0, 0);
        vector<vector<int>>A = djikstraFind(CRIMER[0].first, CRIMER[0].second);
        vector<vector<int>>B = djikstraFind(CRIMER[1].first, CRIMER[1].second);

        int ans_num{ INF };

        for (int row = 0; row <= h + 1; row++) {
            for (int col = 0; col <= w + 1; col++) {
                if (JAIL[row][col] == 1) {
                    ans_num = min(ans_num, sangeun[row][col] + A[row][col] + B[row][col] - 2);
                }
                else if(JAIL[row][col] == 0){
                    ans_num = min(ans_num, sangeun[row][col] + A[row][col] + B[row][col]);
                }
            }
        }

        cout << ans_num << '\n';

        memset(JAIL, 0, sizeof(JAIL));
        CRIMER.clear();
    }

}

vector<vector<int>> djikstraFind(int row, int col) {

    priority_queue<Node, vector<Node>, bool (*)(const Node&, const Node&)>pq(upperWeight);
    vector<vector<int>>dist(h + 2, vector<int>(w + 2, INF));
    pq.push({ row, col, 0 }); dist[row][col] = 0;

    while (!pq.empty()) {
        Node now = pq.top(); pq.pop();

        if (now.cost > dist[now.row][now.col]) {
            continue;
        }

        for (int d = 0; d < 4; d++) {
            int nr = now.row + Dr[d]; int nc = now.col + Dc[d];
            if (inbound(nr, nc) && JAIL[nr][nc] != 2 && now.cost + JAIL[nr][nc] < dist[nr][nc]) {
                pq.push({ nr,nc,now.cost + JAIL[nr][nc] }); dist[nr][nc] = now.cost + JAIL[nr][nc];
            }
        }

    }

    return dist;
}

bool upperWeight(const Node& A, const Node& B) {
    return A.cost > B.cost;
}

bool inbound(int nr, int nc) {
    if (nr >= 0 && nr <= h + 1 && nc >= 0 && nc <= w + 1) {
        return true;
    }
    return false;
}