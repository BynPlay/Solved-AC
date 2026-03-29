#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

int MAP[51][51];
int n;

struct COO {
    int row;
    int col;

    COO() : row(0), col(0) {}
    COO(const int& x, const int& y) : row(x), col(y) {}
    COO operator+(const COO& rhs) const { return { row + rhs.row, col + rhs.col }; }
    bool is_valid() const {
        if (row >= 1 && row <= n && col >= 1 && col <= n) {
            return true;
        } 
        return false; 
    }

};

const COO DIR[4] = {{1,0},{-1,0} ,{0,1} ,{0,-1}};

struct Cell {
    COO coo;
    int dist;

    bool operator<(const Cell& rhs) const { return dist > rhs.dist; }
};


int findBlackRooms() {
    vector<vector<int>>DIST(n + 1, vector<int>(n + 1, INF));
    priority_queue<Cell>pq; pq.push({ {1,1},0 }); DIST[1][1];
    while (!pq.empty()) {
        Cell now = pq.top(); pq.pop();
        if(now.dist > DIST[now.coo.row][now.coo.col]){
            continue;
        }

        for (int d = 0; d < 4; d++) {
            COO next = now.coo + DIR[d];
            if (next.is_valid() && now.dist + MAP[next.row][next.col] < DIST[next.row][next.col]) {
                DIST[next.row][next.col] = now.dist + MAP[next.row][next.col];
                pq.push({ next, DIST[next.row][next.col] });
            }
        }
    }

    return DIST[n][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> n;
    for (int row = 1; row <= n; row++) {
        string rows; cin >> rows;
        for (int col = 1; col <= n; col++) {
            if (rows[col - 1] == '1') {
                MAP[row][col] = 0;
            }
            else {
                MAP[row][col] = 1;
            }
        }
    }

    cout << findBlackRooms();
}