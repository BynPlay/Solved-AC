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

struct Node {
    int num;
    vector<int> childNode;
};

int N;
Node Tree[51];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;

    for (int i = 0; i < N; i++) {
        int node_num; cin >> node_num;
        if (node_num != -1) {
            Tree[node_num].childNode.push_back(i);
        }
    }

    int del; cin >> del; vector<int>deletedNode;

    queue<Node>q; q.push(Tree[del]); deletedNode.push_back(del);
    int ans{ 0 };

    while (!q.empty()) {
        Node now = q.front(); q.pop();
        
        for (auto& j : now.childNode) {
            q.push(Tree[j]);
            deletedNode.push_back(j);
        }
    }

    for (int i = 0; i < N; i++) {
        for (auto it = Tree[i].childNode.begin(); it != Tree[i].childNode.end();)
            if (*it == del) {
                it = Tree[i].childNode.erase(it);
            }
            else{
                it++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (Tree[i].childNode.size() == 0) {
            bool is_deleted{ false };
            for (auto& j : deletedNode) {
                if (i == j) {
                    is_deleted = true;
                }
            }
            if (is_deleted == false) {
                ans++;
            }
        }
    }

    cout << ans;
}

/*
bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}
*/



/*
const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };

struct Man {
    int row;
    int col;
    bool wallBroken{ false };
};

int N, M;
char Map[1001][1001];
int Dist[1001][1001];

bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}

void bfs() {

    queue<Man>q; q.push({ 1,1, false }); Dist[1][1] = 1;

    while (!q.empty()) {
        Man now = q.front(); q.pop();
        
        if (now.row == N && now.col == M) {
            return;
        }

        for (int d = 0; d < 4; d++) {
            int nr = now.row + Dr[d]; int nc = now.col + Dc[d];
            if (inBound(nr,nc)) {
                if (Map[nr][nc] == '0') {
                    Dist[nr][nc] = Dist[now.row][now.col] + 1;
                    q.push({nr,nc,now.wallBroken});
                }
                else {
                    if (now.wallBroken == false) {
                        Dist[nr][nc] = Dist[now.row][now.col] + 1;
                        q.push({ nr,nc,true });
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> M;
    for (int row = 1; row <= N; row++) {
        string cols; cin >> cols;
        for (int col = 1; col <= M; col++) {
            Map[row][col] = cols[col - 1];
        }
    }

    bfs(); 

    if (Dist[N][M] == 0) {
        cout << -1;
    }
    else {
        cout << Dist[N][M];
    }
}




void printMap() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= M; col++) {
            cout << Dist[row][col];
        }
        cout << endl;
    }
    cout << endl;
}
*/

/*
const int Dr[4] = { 1,-1,0,0 };
const int Dc[4] = { 0,0,1,-1 };


bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= M) {
        return true;
    }
    return false;
}*/