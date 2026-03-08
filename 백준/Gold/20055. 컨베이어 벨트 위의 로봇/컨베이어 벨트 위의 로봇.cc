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

using namespace std; 

int N, K;


struct Belt {
    int A;
    bool Onrobot{ false };
};

Belt belt[201];

struct Robot {
    int loc;

    void rotateWithBelt() {
        if (loc < 2 * N) {
            loc = loc + 1;
        }
        else if (loc == 2 * N) {
            loc = 1;
        }
    }

    void move() {
        int next_loc;
        if (loc < 2 * N) {
            next_loc = loc + 1;
        }
        else if (loc == 2 * N) {
            next_loc = 1;
        }
        
        if (belt[next_loc].A >= 1 && belt[next_loc].Onrobot == false) {
            belt[loc].Onrobot = false;
            loc = next_loc;
            belt[loc].Onrobot = true;
            belt[loc].A--;
        }
    }
};

vector<Robot> robots;

void rotateBelt() {
    Belt last_space = belt[2 * N];
    for (int i = 2 * N; i > N; i--) {
        belt[i] = belt[i - 1];
    }
    for (int i = N; i > 1 ; i--) {
        belt[i] = belt[i-1];
    }
    belt[1] = last_space;

    for (auto it = robots.begin(); it != robots.end();) {
        it->rotateWithBelt();
        if (it->loc == N) {
            it = robots.erase(it);
            belt[N].Onrobot = false;
        }
        else {
            ++it;
        }
    }
}

void moveRobots() {
    for (auto it = robots.begin(); it != robots.end();) {
        it->move();
        if (it->loc == N) {
            it = robots.erase(it);
            belt[N].Onrobot = false;
        }
        else {
            ++it;
        }
    }
}

void raiseRobot() {
    if (belt[1].A != 0 && belt[1].Onrobot == false) {
        belt[1].A--;
        belt[1].Onrobot = true;
        robots.push_back({1});
    }
}

bool isFinished() {
    int blanked_cnt{ 0 };
    for (int i = 1; i <= 2 * N ; i++) {
        if (belt[i].A == 0) {
            blanked_cnt++;
        }
    }
    if (blanked_cnt >= K) {
        return true;
    }
    return false;
}

void checkBelt() {
    for (int i = 1; i <= 2 * N; i++) {
        cout << i << ": " << belt[i].A << '(' << belt[i].Onrobot << ')' << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> K;
    for (int i = 1; i <= 2 * N ; i++) {
        cin >> belt[i].A;
    }

    int level{ 0 };

    while (!isFinished()) {
    rotateBelt();
    moveRobots();
    raiseRobot();
        level++;
    }

    cout << level;
}

/*
int N, M, K;
int Map[21][21];



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   //freopen("input.txt", "r", stdin);
    cin >> N >> M >> K;
    for (int row = 1; row <= N ; row++) {
        for (int col = 1; col <= M ; col++) {
            cin >> Map[row][col];
        }
    }

    return 0;
}
*/



