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
const long long INF{ INT_MAX };

const int length[2][2] = { {1,0},{-1,0} };
const int width[2][2] = { {0,1},{0,-1} };
const int diagonal1[2][2] = { {-1,1},{1,-1} };
const int diagonal2[2][2] = { {-1,-1},{1,1} };
const int CASES[4][2][2] = { { {1,0},{-1,0} } ,{ {0,1},{0,-1} } ,{ {-1,1},{1,-1} } ,{ {-1,-1},{1,1} } };

int BOARD[20][20];

bool inbound(int nr, int nc);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N, K, Q, M;
    cin >> N >> K >> Q >> M;

    int maxNum = N + 2;

    vector<bool> sleeping(maxNum + 1, false);
    vector<bool> attended(maxNum + 1, false);

    for (int i = 0; i < K; i++) {
        int x; cin >> x;
        sleeping[x] = true;
    }

    for (int i = 0; i < Q; i++) {
        int x; cin >> x;
        if (sleeping[x]) continue;
        for (int mul = x; mul <= maxNum; mul += x) {
            if (!sleeping[mul]) {
                attended[mul] = true;
            }
        }
    }

    vector<int> psum(maxNum + 1, 0);
    for (int i = 3; i <= maxNum; i++) {
        psum[i] = psum[i - 1] + (attended[i] ? 1 : 0);
    }

    for (int i = 0; i < M; i++) {
        int S, E;
        cin >> S >> E;
        int total = E - S + 1;
        int attendedCount = psum[E] - psum[S - 1];
        cout << total - attendedCount << "\n";
    }

    return 0;
}



bool inbound(int nr, int nc) {
    if (nr >= 1 && nr <= 19 && nc >= 1 && nc <= 19) {
        return true;
    }
    return false;
}