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
#include <cstring>

using namespace std; 
const int INF{ INT_MAX };

int N;
int City[21][21];
int min_ans = { INF };

const int Dr[4] = {1,-1,0,0}; 
const int Dc[4] = {0,0,1,-1};

bool inBound(int nr, int nc) {
    if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
        return true;
    }
    return false;
}

//경계선만들기
//선거구 나누고 인구 구하기


void bruteForceDivide(vector<int>& v, int depth);

int makeLineAndCalculate(int d1, int d2, int x, int y, int visited[21][21]);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;
    for (int row = 1; row <= N ; row++) {
        for (int col = 1; col <= N ; col++) {
            cin >> City[row][col];
        }
    }

    vector<int>v;
    bruteForceDivide(v, 0);

    cout << min_ans;

}


void bruteForceDivide(vector<int>& v, int depth) {

    if (depth == 3) {
        if (v[2] + v[0] + v[1] > N) {
            return;
        }
    }

    if (depth == 4) {
        if (v[3] - v[0] < 1 || v[3] + v[1] > N) {
            return;
        }
    }

    if (depth == 4) {
        int visited[21][21] = {};
        int cal = makeLineAndCalculate(v[0], v[1], v[2], v[3], visited);
        if (cal < min_ans) {
            min_ans = cal;
            /*
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    cout << visited[i][j] << ' ';
                }
                cout << endl;
            }
            cout << endl;*/
        }
        return;
    }

    for (int i = 1; i <= 20; i++) {
        v.push_back(i);
        bruteForceDivide(v, depth + 1);
        v.pop_back();
    }
}

int makeLineAndCalculate(int d1, int d2, int x, int y, int visited[21][21]) {
    int population5{ 0 };
    for (int i = 0; i <= d1; i++) {
        if (visited[x + i][y - i] == 0) {
            population5 += City[x + i][y - i];  visited[x + i][y - i] = 5;
            //cout << x + i << ',' << y - i << ": " << City[x + i][y - i] << endl;
        }
    }
    for (int i = 0; i <= d2; i++) {
        if (visited[x + i][y + i] == 0) {
            population5 += City[x + i][y + i];  visited[x + i][y + i] = 5;
            //cout << x + i << ',' << y + i << ": " << City[x + i][y + i] << endl;
        }
    }
    for (int i = 0; i <= d2; i++) {
        if (visited[x + d1 + i][y - d1 + i] == 0) {
            population5 += City[x + d1 + i][y - d1 + i];  visited[x + d1 + i][y - d1 + i] = 5;
            //cout << x + d1 + i << ',' << y - d1 + i << ": " << City[x + d1 + i][y - d1 + i] << endl;
        }
    }
    for (int i = 0; i <= d1; i++) {
        if (visited[x + d2 + i][y + d2 - i] == 0) {
            population5 += City[x + d2 + i][y + d2 - i];  visited[x + d2 + i][y + d2 - i] = 5;
            //cout << x + d2 + i << ',' << y + d2 - i << ": " << City[x + d2 + i][y + d2 - i] << endl;
        }
    }

    int population1{ 0 }; queue<pair<int, int>>q;
    population1 += City[1][1];
    q.push({ 1,1 }); visited[1][1] = 1;

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (inBound(nr, nc) && nr < x + d1 && nc <= y && visited[nr][nc] == 0) {
                population1 += City[nr][nc];
                //cout << nr << ',' << nc << ": " << City[nr][nc] << endl;
                q.push({ nr,nc }); visited[nr][nc] = 1;
            }
        }
    }

    int population2{ 0 };
    population2 += City[1][N];
    q.push({ 1,N }); visited[1][N] = 2;

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (inBound(nr, nc) && nr <= x + d2 && nc > y && visited[nr][nc] == 0) {
                population2 += City[nr][nc];
                //cout << nr << ',' << nc << ": " << City[nr][nc] << endl;
                q.push({ nr,nc }); visited[nr][nc] = 2;
            }
        }
    }

    int population3{ 0 };
    population3 += City[N][1];
    q.push({ N,1 }); visited[N][1] = 3;

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (inBound(nr, nc) && nr >= x + d1 && nc < y - d1 + d2 && visited[nr][nc] == 0) {
                population3 += City[nr][nc];
                //cout << nr << ',' << nc << ": " << City[nr][nc] << endl;
                q.push({ nr,nc }); visited[nr][nc] = 3;
            }
        }
    }

    int population4{ 0 };
    population4 += City[N][N];
    q.push({ N,N }); visited[N][N] = 4;

    while (!q.empty()) {
        pair<int, int>now = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
            if (inBound(nr, nc) && nr > x + d2 && nc >= y - d1 + d2 && visited[nr][nc] == 0) {
                population4 += City[nr][nc];
                //cout << nr << ',' << nc << ": " << City[nr][nc] << endl;
                q.push({ nr,nc }); visited[nr][nc] = 4;
            }
        }
    }

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (visited[row][col] == 0) {
                visited[row][col] = 5;
                population5 += City[row][col];
            }
        }
    }

    vector<int>calcuator = { population1,population2 ,population3 ,population4 ,population5 };
    sort(calcuator.begin(), calcuator.end());
    int cal = calcuator[4] - calcuator[0];

    return cal;
}