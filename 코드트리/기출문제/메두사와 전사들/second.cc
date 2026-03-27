#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

int N; // 마을의 크기
int M; // 전사의 수

struct COO {
    int row, col;
    bool is_valid() const {
        if (row >= 0 && row < N && col >= 0 && col < N) { return true; }
        else { return false; }
    }
    COO() : row(0), col(0) {};
    COO(const int& row, const int& col) : row(row), col(col) {};

    COO operator+(const COO& rhs) const { return { row + rhs.row, col + rhs.col }; }
    bool operator!=(const COO& rhs) const {
        if (row != rhs.row || col != rhs.col) { return true; }
        else { return false; }
    }
    bool operator==(const COO& rhs) const {
        if (row == rhs.row && col == rhs.col) { return true; }
        else { return false; }
    }
    int get_distance(const COO& rhs) const { return abs(row - rhs.row) + abs(col - rhs.col); }
};

const COO Dir[2][4] = { {{-1,0},{1,0},{0,-1},{0,1}}, {{0,-1},{0,1},{-1,0},{1,0}} };
const COO DirSight[4][3] = { 
    {{-1,0},{-1,-1},{-1,1}},
    {{1,0},{1,-1},{1,1}},
    {{0,-1},{-1,-1},{1,-1}},
    {{0,1},{-1,1},{1,1}} 
};

int MAP[50][50];

struct Warrior_MAP;
struct Medusa;

void debugDistance(const vector<vector<int>>& DIST, COO dest, COO start);
void debugMap(Medusa medusa, Warrior_MAP warrior_map);
vector<vector<int>> calculateDist(COO dest, COO start, bool ignore_wall = false);

struct Warrior_MAP {
    vector<COO>warriors;
    vector<COO>warriors_stoned;
    vector<vector<unordered_set<int>>>A;

    Warrior_MAP(const int& M, const vector<COO>& init) : warriors(init) {
        A.resize(N, vector<unordered_set<int>>(N));
        for (int w = 0; w < M; w++) {
            A[warriors[w].row][warriors[w].col].insert(w);
        }
    }

    void removeWarrior(int warrior_idx);
    void remove_same_cell(const COO& cell);
    void move_warriors(const Medusa& medusa, int& ans_w_move);
    void attack_medusa(const Medusa& medusa, int& ans_w_attacked);
    void release_stoned();

};

struct Medusa {
    COO coo;
    vector<vector<bool>>CONFVISION;

    Medusa(int er, int ec) : coo({ er, ec }) {}

    void move(const vector<vector<int>>& PARKDIST, Warrior_MAP& warrior_map);
    void vision(Warrior_MAP& warrior_map, int& ans_w_stoned);
};


void Warrior_MAP:: removeWarrior(int warrior_idx) {

    COO warrior_coo = warriors[warrior_idx];
    A[warrior_coo.row][warrior_coo.col].erase(warrior_idx);

    int last_idx = warriors.size() - 1;
    if (warrior_idx != last_idx) {

        COO moved = warriors[last_idx];

        warriors[warrior_idx] = warriors.back();
        warriors.pop_back();

        A[moved.row][moved.col].erase(last_idx);
        A[moved.row][moved.col].insert(warrior_idx);
    }
    else {
        warriors.pop_back();
    }
}

void Warrior_MAP:: remove_same_cell(const COO& cell) {

    for (int i = warriors.size() - 1; i >= 0; i--) {
        if (warriors[i] == cell) {
            removeWarrior(i);
        }
    }

}

void Warrior_MAP:: move_warriors(const Medusa& medusa, int& ans_w_move) {

    for (int w = 0; w < warriors.size(); w++){

        vector<vector<int>>MEDUDOST = calculateDist(medusa.coo, warriors[w], true);
      

        COO next_coo = warriors[w]; int next_dist = MEDUDOST[warriors[w].row][warriors[w].col];

        for (int c = 0; c < 2; c++) {

            for (int d = 0; d < 4; d++) {
                COO next = warriors[w] + Dir[c][d];
                if (next.is_valid() && MEDUDOST[next.row][next.col] < next_dist && medusa.CONFVISION[next.row][next.col] == 0) {
                    next_dist = MEDUDOST[next.row][next.col];
                    next_coo = next;
                }
            }

            if (next_coo != warriors[w]) {
                ans_w_move++;
                A[warriors[w].row][warriors[w].col].erase(w);
                warriors[w] = next_coo;
                next_dist = MEDUDOST[warriors[w].row][warriors[w].col];
                A[warriors[w].row][warriors[w].col].insert(w);
            }

        }
    }

}

void Warrior_MAP:: attack_medusa(const Medusa& medusa, int& ans_w_attacked) {
    ans_w_attacked += A[medusa.coo.row][medusa.coo.col].size();
    remove_same_cell(medusa.coo);
}

void Warrior_MAP::release_stoned() {

    for (auto& w : warriors_stoned) {
        A[w.row][w.col].insert(warriors.size());
        warriors.push_back(w);
    }
    warriors_stoned.clear();

}


void Medusa:: move(const vector<vector<int>>& PARKDIST, Warrior_MAP& warrior_map) {

    COO next_coo = coo; int next_dist = INF;

    for (int d = 0; d < 4; d++) {
        COO next = coo + Dir[0][d];
        if (next.is_valid() && PARKDIST[next.row][next.col] < next_dist) {
            next_dist = PARKDIST[next.row][next.col];
            next_coo = next;
        }
    }

    coo = next_coo;

    warrior_map.remove_same_cell(coo);

}

void Medusa:: vision(Warrior_MAP& warrior_map, int& ans_w_stoned) {

    int max_stoned{ -1 };

    for (int d = 0; d < 4; d++) {

        vector<vector<bool>> MEDUSAVIS(N, vector<bool>(N, false));
        queue<COO>q; q.push(coo); queue<pair<COO, int>>q_stoned;

        while (!q.empty()) {
            COO now = q.front(); q.pop();
            for (int i = 0; i < 3; i++) {
                COO next_coo = now + DirSight[d][i];
                if (next_coo.is_valid() && MEDUSAVIS[next_coo.row][next_coo.col] == false) {
                    if (warrior_map.A[next_coo.row][next_coo.col].size() > 0) {
                        q_stoned.push({ next_coo, i });
                    }
                    q.push(next_coo);
                    MEDUSAVIS[next_coo.row][next_coo.col] = true;
                }
            }

        }

        while (!q_stoned.empty()) {
            COO now = q_stoned.front().first;
            int dir = q_stoned.front().second;
            q_stoned.pop();

            COO next_coo = now + DirSight[d][dir];
            if (next_coo.is_valid() && MEDUSAVIS[next_coo.row][next_coo.col] == true) {
                q_stoned.push({ next_coo,dir });
                MEDUSAVIS[next_coo.row][next_coo.col] = false;
            }

            if (dir == 1 || dir == 2) {
                next_coo = now + DirSight[d][0];
                if (next_coo.is_valid() && MEDUSAVIS[next_coo.row][next_coo.col] == true) {
                    q_stoned.push({ next_coo,0 });
                    MEDUSAVIS[next_coo.row][next_coo.col] = false;
                }
            }
        }

        int stoned_warriors{ 0 };

        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (MEDUSAVIS[row][col] == true && warrior_map.A[row][col].size() > 0) {
                    stoned_warriors += warrior_map.A[row][col].size();
                }
            }
        }

        if (stoned_warriors > max_stoned) {
            max_stoned = stoned_warriors;
            CONFVISION = MEDUSAVIS;
        }

        /*
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                cout << MEDUSAVIS[row][col] << ' ';
            }
            cout << endl;
        }
        cout << endl;
        */

    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (CONFVISION[row][col] == true && warrior_map.A[row][col].size() > 0) {
                for (auto& warrior : warrior_map.A[row][col]) {
                    warrior_map.warriors_stoned.push_back(warrior_map.warriors[warrior]);
                    ans_w_stoned++;
                }
                warrior_map.remove_same_cell({ row,col });
            }
        }
    }

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    int sr, sc; int er, ec; 
    cin >> sr >> sc >> er >> ec;

    Medusa medusa(sr, sc);
    COO park_coo(er, ec);

    vector<COO>init(M);
    for (int i = 0; i < M; i++) {
        int ar, ac; cin >> ar >> ac;
        init[i] = { ar,ac };
    }
    Warrior_MAP warror_map(M, init);

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> MAP[row][col];
        }
    }
    vector<vector<int>>PARKDIST = calculateDist(park_coo, medusa.coo);

    if (PARKDIST[medusa.coo.row][medusa.coo.col] == INF) {
        cout << -1;
    }
    else {
        while (true) {

            int ans_w_move{ 0 }; int ans_w_stoned{ 0 }; int ans_w_attacked{ 0 };


            medusa.move(PARKDIST, warror_map);

            if (medusa.coo == park_coo) {
                cout << 0;
                break;
            }

            medusa.vision(warror_map, ans_w_stoned);

            warror_map.move_warriors(medusa, ans_w_move);
            warror_map.attack_medusa(medusa, ans_w_attacked);
            warror_map.release_stoned();

            cout << ans_w_move << ' ' << ans_w_stoned << ' ' << ans_w_attacked << endl;

        }
    }

}


vector<vector<int>> calculateDist(COO dest, COO start, bool ignore_wall) {

    vector<vector<int>>DIST(N, vector<int>(N, INF));

    queue<COO>q; q.push(dest); DIST[dest.row][dest.col] = 0;

    bool is_Finished{ false };
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            COO now = q.front(); q.pop();

            if (now == start) {
                is_Finished = true;
            }

            for (int d = 0; d < 4; d++) {
                COO next(now + Dir[0][d] );
                if (next.is_valid() && DIST[next.row][next.col] == INF) {
                    if (ignore_wall == true || MAP[next.row][next.col] != 1) {
                        q.push(next); DIST[next.row][next.col] = DIST[now.row][now.col] + 1;
                    }
                }
            }
        }
        if (is_Finished == true) {
            break;
        }
    }

    return DIST;

}


void debugDistance(const vector<vector<int>>& DIST, COO dest, COO start) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (row == dest.row && col == dest.col) {
                cout << 'D' << ' ';
            }
            else if (row == start.row && col == start.col) {
                cout << 'S' << ' ';
            }
            else if (DIST[row][col] == INF) {
                cout << 'X' << ' ';
            }
            else {
                cout << DIST[row][col] << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void debugMap(Medusa medusa, Warrior_MAP warrior_map) {

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (row == medusa.coo.row && col == medusa.coo.col) {
                cout << 'M' << ' ';
            }
            else {
                cout << warrior_map.A[row][col].size() << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}