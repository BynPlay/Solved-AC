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

const int Dr[4] = {-1,0,0,1}; // 위 왼쪽 오른쪽 아래
const int Dc[4] = {0,-1,1,0};

struct Passenger {
    int passnum;
    int dest_row;
    int dest_col;
};

int N, M;
int Oil; bool Stop{ false };
int MatrixMap[21][21];
Passenger MatrixPos[21][21];

bool inbound(int nr, int nc);

struct Taxi {
    int row;
    int col;
    int useoil{ 0 };
    Passenger passenger;
};

Taxi searchPassenger(Taxi taxi);
Taxi searchDestination(Taxi taxi);

void DebugMatrixMap();
void DebugMatrixPos(Taxi taxi);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M >> Oil;

    for (int row = 1; row <= N ; row++) {
        for (int col = 1; col <= N ; col++) {
            cin >> MatrixMap[row][col];
            if (MatrixMap[row][col] == 1) {
                MatrixMap[row][col] = -1;
            }
        }
    }

    Taxi taxi;
    cin >> taxi.row >> taxi.col;

    for (int i = 1; i <= M; i++) {
        Passenger passenger; passenger.passnum = i;
        int r, c;
        cin >> r >> c >> passenger.dest_row >> passenger.dest_col;
        MatrixPos[r][c] = passenger;
    }

    int cnt = 0;
    while (cnt < M) {
        taxi = searchPassenger(taxi);
        if (Stop == true) {
            break;
        }
        taxi = searchDestination(taxi);
        if (Stop == true) {
            break;
        }
        cnt++;
    }

    if (Stop == true) {
        cout << -1;
    }
    else {
        cout << Oil;
    }
    
}

bool inbound(int nr, int nc) {
    if (nr <= N && nr >= 1 && nc <= N && nc >= 1) {
        return true;
    }
    return false;
}

Taxi searchPassenger(Taxi taxi) {
    int TestMap[21][21] = {};
    memcpy(TestMap, MatrixMap, sizeof(MatrixMap));

    queue<Taxi> q;
    q.push(taxi);
    TestMap[taxi.row][taxi.col] = 1;

    while (!q.empty()) {
        int sz = q.size();
        vector<Taxi> candidates; // 같은 거리에서 발견된 승객 후보

        for (int i = 0; i < sz; i++) {
            Taxi now_taxi = q.front(); q.pop();

            if (MatrixPos[now_taxi.row][now_taxi.col].passnum > 0) {
                candidates.push_back(now_taxi);
            }

            for (int d = 0; d < 4; d++) {
                int nr = now_taxi.row + Dr[d];
                int nc = now_taxi.col + Dc[d];
                if (inbound(nr, nc) && TestMap[nr][nc] == 0) {
                    q.push({ nr, nc, now_taxi.useoil + 1, now_taxi.passenger });
                    TestMap[nr][nc] = 1;
                }
            }
        }

        if (!candidates.empty()) {
            // 행 우선, 열 우선으로 정렬
            sort(candidates.begin(), candidates.end(), [](const Taxi& a, const Taxi& b) {
                if (a.row != b.row) return a.row < b.row;
                return a.col < b.col;
                });

            Taxi now_taxi = candidates[0];

            if (Oil - now_taxi.useoil < 0) {
                Stop = true;
                return taxi;
            }
            else {
                now_taxi.passenger = MatrixPos[now_taxi.row][now_taxi.col];
                MatrixPos[now_taxi.row][now_taxi.col].passnum = 0;
                Oil -= now_taxi.useoil;
                now_taxi.useoil = 0;
                return now_taxi;
            }
        }
    }

    Stop = true;
    return taxi;
}

Taxi searchDestination(Taxi taxi) {
    int TestMap[21][21] = {};
    memcpy(TestMap, MatrixMap, sizeof(MatrixMap));

    queue<Taxi>q;
    q.push(taxi);
    TestMap[taxi.row][taxi.col] = 1;

    while (!q.empty()) {
        Taxi now_taxi = q.front(); q.pop();

    if (now_taxi.passenger.dest_row == now_taxi.row && now_taxi.passenger.dest_col == now_taxi.col) {
        if (Oil - now_taxi.useoil < 0) {
            Stop = true;
            return taxi;
        }
        else {
            now_taxi.passenger.passnum = 0;
            Oil -= now_taxi.useoil;
            Oil += now_taxi.useoil * 2;
            now_taxi.useoil = 0;

            return now_taxi;
        }
        //cout << now_taxi.passenger.passnum << ' ' << now_taxi.passenger.dest_row << ' ' << now_taxi.passenger.dest_col << ' ' << endl;
    }
 

        for (int d = 0; d < 4; d++) {
            int nr = now_taxi.row + Dr[d]; int nc = now_taxi.col + Dc[d];
            if (inbound(nr, nc) && TestMap[nr][nc] == 0) {
                q.push({ nr, nc, now_taxi.useoil + 1 ,now_taxi.passenger});
                TestMap[nr][nc] = 1;
            }
        }
    }

    Stop = true;
    return taxi;
}

void DebugMatrixMap() {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            cout << MatrixMap[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void DebugMatrixPos(Taxi taxi) {
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            if (taxi.row == row && taxi.col == col) {
                cout << taxi.useoil << ' ';
            }
            else {
                cout << MatrixPos[row][col].passnum << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

