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

const int DR[4] = { 1,-1,0,0 };
const int DC[4] = { 0,0,1,-1 };

int h, w;

bool inbound(int nr, int nc, char MAP[102][102]);

int roomSearch(char MAP[102][102], bool visited[102][102], bool key[26]) {
    
    int ans{ 0 };

    queue<pair<int, int>>q; vector<pair<int, int>> locked_door[26]; 
    q.push({ 0, 0 }); visited[0][0] = true;

    while (!q.empty()) {
        pair<int, int> now = q.front(); q.pop();

        if (MAP[now.first][now.second] == '$') {
            ans++;
            MAP[now.first][now.second] = '.';
        }

        else if (MAP[now.first][now.second] >= 'a' && MAP[now.first][now.second] <= 'z') {
            key[MAP[now.first][now.second] - 'a'] = true;

            for(auto & next: locked_door[MAP[now.first][now.second] - 'a']) {
                q.push({ next.first,next.second });
            }
            locked_door[MAP[now.first][now.second] - 'a'].clear();
        }
         
        for (int d = 0; d < 4; d++) {
            int nr = now.first + DR[d]; int nc = now.second + DC[d];
            if (inbound(nr,nc,MAP) && visited[nr][nc] == false) {

                if (MAP[nr][nc] >= 'A' && MAP[nr][nc] <= 'Z') {
                    if (key[MAP[nr][nc] - 'A'] == false) {
                        locked_door[MAP[nr][nc] - 'A'].push_back({nr,nc});
                        visited[nr][nc] = true;
                    }
                    else {
                        q.push({ nr,nc });
                        visited[nr][nc] = true;
                    }
                }
                else {
                    q.push({ nr,nc });
                    visited[nr][nc] = true;
                }
            }
        }
    }

    return ans;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int T; cin >> T;

    for (int t = 0; t < T; t++) {

        cin >> h >> w;
        char MAP[102][102] = {};
        for (int i = 0; i <= h + 1; i++) {
            for (int j = 0; j <= w + 1; j++) {
                MAP[i][j] = '.';
            }
        }
        bool key[26] = {}; int max_ans{ 0 };

        for (int row = 1; row <= h; row++) {
            string rows; cin >> rows;
            for (int col = 1; col <= w; col++) {
                MAP[row][col] = rows[col - 1];
            }
        }

        string keys; cin >> keys;
        if (keys != "0") {
            for (int i = 0; i < keys.size(); i++) {
                key[keys[i] - 'a'] = true;
            }
        }

        bool visited[102][102] = {};
        int docs_cnt = roomSearch(MAP, visited, key);
        if (max_ans < docs_cnt) {
            max_ans = docs_cnt;
        }

        cout << max_ans << endl;
    }
}

bool inbound(int nr, int nc, char MAP[102][102]) {
    if (nr >= 0 && nr <= h + 1 && nc >= 0 && nc <= w + 1 && MAP[nr][nc] != '*') {
        return true;
    }
    return false;
}