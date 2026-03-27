#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

const int Dr[4] = { -1,1,0,0 };
const int Dc[4] = { 0,0,-1,1 };

const int Dr2[4] = { 0,0,-1,1 };
const int Dc2[4] = { -1,1,0,0 };

const int move_dir[4][3][2] = {
    {{-1,0},{-1,-1},{-1,1}},
    {{1,0},{1,-1},{1,1}},
    {{0,-1},{-1,-1},{1,-1}},
    {{0,1},{-1,1},{1,1}}
};

int MAP[50][50];
int DISTANCE[50][50];

int WARRIROS[50][50];
int STONEDWARRIROS[50][50];
int SIGHT[50][50];

int N, M;
int sr, sc;
int er, ec;

int ans_warrior_move;
int ans_warrior_stone;
int ans_warrior_attack;

bool inbound(int nr, int nc);
void makeDistance();

void medusaMove();
void medusaSee();
void warriorMove();
void stoneReleased();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> M;
    cin >> sr >> sc >> er >> ec;

    for (int i = 0; i < M; i++) {
        int ar, ac; cin >> ar >> ac;
        WARRIROS[ar][ac] += 1;
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> MAP[row][col];
        }
    }

    makeDistance();


    if (DISTANCE[sr][sc] == INF) {
        cout << -1;
    }

    else {

        while (true) {

            ans_warrior_move = 0;
            ans_warrior_stone = 0;
            ans_warrior_attack = 0;

            medusaMove();

            /*
            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    if (row == sr && col == sc) {
                        cout << 'M' << ' ';
                    }
                    else if(row == er && col == ec){
                        cout << 'E' << ' ';
                    }
                    else {
                        cout << WARRIROS[row][col] << ' ';
                    }
                }
                cout << endl;
            }
            cout << endl;
            */

            if (sr == er && sc == ec) {
                cout << 0;
                break;
            }

            medusaSee();

            /*
            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    cout << SIGHT[row][col] << ' ';
                }
                cout << endl;
            }
            cout << endl;
            */

            warriorMove();

            stoneReleased();

            cout << ans_warrior_move << ' ' << ans_warrior_stone << ' ' << ans_warrior_attack << endl;
        }
    }
}



bool inbound(int nr, int nc) {
    if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
        return true;
    }
    return false;
}

void makeDistance() {

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            DISTANCE[row][col] = INF;
        }
    }

    queue<pair<int, int>>q;
    q.push({ er,ec }); DISTANCE[er][ec] = 0;

    while (!q.empty()) {
        int size = q.size(); bool is_finished{ false };
        for (int s = 0; s < size; s++) {
            pair<int, int> now = q.front(); q.pop();

            if (now.first == sr && now.second == sc) {
                is_finished = true;
            }

            for (int d = 0; d < 4; d++) {
                int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
                if (inbound(nr, nc) && MAP[nr][nc] == 0 && DISTANCE[nr][nc] == INF) {
                    q.push({ nr,nc });
                    DISTANCE[nr][nc] = DISTANCE[now.first][now.second] + 1;
                }
            }
        }
        if (is_finished) {
            break;
        }
    }
}

void medusaMove() {

    int next_distance = INF;
    int next_row = sr; int next_col = sc;

    for (int d = 0; d < 4; d++) {
        int nr = sr + Dr[d]; int nc = sc + Dc[d];
        if (inbound(nr, nc) && DISTANCE[nr][nc] < next_distance) {
            next_distance = DISTANCE[nr][nc];
            next_row = nr; next_col = nc;
        }
    }

    sr = next_row; sc = next_col;
    if (WARRIROS[sr][sc] > 0) {
        WARRIROS[sr][sc] = 0;
    }

}

void medusaSee() {

    int max_stoned_num{ -1 };
    int COPIEDWARRIROS[50][50]; memcpy(COPIEDWARRIROS, WARRIROS, sizeof(WARRIROS));

    for (int dir = 0; dir < 4; dir++) {

        int warriors[50][50]; memcpy(warriors, COPIEDWARRIROS, sizeof(warriors));
        int stoned_warriors[50][50] = {}; int sight[50][50] = {};

        queue<pair<int, int>> q;
        q.push({ sr,sc });

        while (!q.empty()) {
            pair<int, int> now = q.front(); q.pop();

            for (int d = 0; d < 3; d++) {
                int nr = now.first + move_dir[dir][d][0]; int nc = now.second + move_dir[dir][d][1];
                if (inbound(nr, nc) && sight[nr][nc] == 0) {
                    //cout << nr << ' ' << nc << ' ' << warriors[nr][nc] << endl;
                    if (warriors[nr][nc] >= 1) {
                        //cout << nr << ' ' << nc << endl;

                        stoned_warriors[nr][nc] = warriors[nr][nc];
                        warriors[nr][nc] = -1; int k{ 0 };

                        if (dir == 0 || dir == 1) {
                            if (nc < sc) {
                                k = 1;
                            }
                            else if (nc > sc) {
                                k = 2;
                            }
                        }
                        else if (dir == 2 || dir == 3) {
                            if (nr < sr) {
                                k = 1;
                            }
                            else if (nr > sr) {
                                k = 2;
                            }
                        }

                        queue<pair<int, int>> q2;
                        q2.push({ nr,nc }); sight[nr][nc] = 2;

                        while (!q2.empty()) {
                            pair<int, int> now = q2.front(); q2.pop();
                            int nr2 = now.first + move_dir[dir][0][0]; int nc2 = now.second + move_dir[dir][0][1];
                            if (inbound(nr2, nc2) && sight[nr2][nc2] != 2) {
                                q2.push({ nr2,nc2 });
                                sight[nr2][nc2] = 2;
                            }

                            nr2 = now.first + move_dir[dir][k][0]; nc2 = now.second + move_dir[dir][k][1];
                            if (inbound(nr2, nc2) && sight[nr2][nc2] != 2) {
                                q2.push({ nr2,nc2 });
                                sight[nr2][nc2] = 2;
                            }
                        }
                    }

                    else {
                        q.push({ nr,nc });
                        sight[nr][nc] = 1;
                    }
                }
            }
        }

        int stoned_num{ 0 };

        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (warriors[row][col] == -1) {
                    stoned_num += COPIEDWARRIROS[row][col];
                }
            }
        }

        if (stoned_num > max_stoned_num) {
            max_stoned_num = stoned_num;
            memcpy(SIGHT, sight, sizeof(sight));
            memcpy(STONEDWARRIROS, stoned_warriors, sizeof(stoned_warriors));
            memcpy(WARRIROS, warriors, sizeof(warriors));
        }
    }

    /*
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << WARRIROS[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    */

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (WARRIROS[row][col] == -1) {
                ans_warrior_stone += COPIEDWARRIROS[row][col];
            }
        }
    }


}

void warriorMove() {

    int COPIEDWARRIORS[50][50]; memcpy(COPIEDWARRIORS, WARRIROS, sizeof(WARRIROS));

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (WARRIROS[row][col] > 0) {

                int dist[50][50] = {};

                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        dist[row][col] = INF;
                    }
                }

                queue<pair<int, int>>q;
                q.push({ sr,sc }); dist[sr][sc] = 0;

                while (!q.empty()) {
                    int size = q.size(); bool is_finished{ false };
                    for (int s = 0; s < size; s++) {
                        pair<int, int> now = q.front(); q.pop();

                        for (int d = 0; d < 4; d++) {
                            int nr = now.first + Dr[d]; int nc = now.second + Dc[d];
                            if (inbound(nr, nc) && dist[nr][nc] == INF) {
                                q.push({ nr,nc });
                                dist[nr][nc] = dist[now.first][now.second] + 1;
                            }
                        }
                    }

                }

                /*
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        if (dist[row][col] == INF) {
                            cout << 'F' << ' ';
                        }
                        else {
                            cout << dist[row][col] << ' ';
                        }
                    }
                    cout << endl;
                }
                cout << endl;

                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        cout << COPIEDWARRIORS[row][col] << ' ';
                    }
                    cout << endl;
                }
                cout << endl;
                */

                int new_distance{ dist[row][col] }; int new_row{ row }; int new_col{ col }; int now_people{ WARRIROS[row][col] };


                for (int d = 0; d < 4; d++) {
                    int nr = row + Dr[d]; int nc = col + Dc[d];
                    if (inbound(nr, nc) && dist[nr][nc] < new_distance && SIGHT[nr][nc] != 1 && WARRIROS[nr][nc] != -1) {
                        new_distance = dist[nr][nc];
                        new_row = nr; new_col = nc;
                    }
                }

                if (new_distance != dist[row][col]) {
                    //cout << "moved first" << endl;
                    ans_warrior_move += now_people;
                    COPIEDWARRIORS[new_row][new_col] += now_people;
                    COPIEDWARRIORS[row][col] -= now_people;
                }

                /*
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        cout << COPIEDWARRIORS[row][col] << ' ';
                    }
                    cout << endl;
                }
                cout << endl;
                */

                int new_distance2{ new_distance }; int new_row2{ new_row }; int new_col2{ new_col };

                for (int d = 0; d < 4; d++) {
                    int nr = new_row + Dr2[d]; int nc = new_col + Dc2[d];
                    if (inbound(nr, nc) && dist[nr][nc] < new_distance2 && SIGHT[nr][nc] != 1 && WARRIROS[nr][nc] != -1) {
                        new_distance2 = dist[nr][nc];
                        new_row2 = nr; new_col2 = nc;

                    }
                }

                if (new_distance != new_distance2) {
                    ans_warrior_move += now_people;
                    COPIEDWARRIORS[new_row2][new_col2] += now_people;
                    COPIEDWARRIORS[new_row][new_col] -= now_people;
                }

                /*
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        cout << COPIEDWARRIORS[row][col] << ' ';
                    }
                    cout << endl;
                }
                cout << endl;
                */
            }

        }
    }

    memcpy(WARRIROS, COPIEDWARRIORS, sizeof(COPIEDWARRIORS));
    ans_warrior_attack += WARRIROS[sr][sc];
    WARRIROS[sr][sc] = 0;

}

void stoneReleased() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (WARRIROS[row][col] == -1) {
                WARRIROS[row][col] = STONEDWARRIROS[row][col];
                STONEDWARRIROS[row][col] = 0;
            }
        }
    }

}
