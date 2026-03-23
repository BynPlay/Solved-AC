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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N, L; cin >> N >> L;

    bool HOLE[1001] = {};
    for (int i = 0; i < N; i++) {
        int loc; cin >> loc;
        HOLE[loc] = true;
    }

    int cnt{ 0 };

    for (int i = 1; i <= 1000 ; i++) {
        if (HOLE[i] == true) {
            for (int j = 0; j < L ; j++) {
                HOLE[i+j] = false;
            }
            cnt++;
        }
    }
   
    cout << cnt;
}