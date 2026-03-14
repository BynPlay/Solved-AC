#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
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
#include <deque>

using namespace std;
const int INF { INT_MAX };

int r, c, k;
int A[101][101];
int max_R{ 3 }; int max_C{ 3 };



void DebugMatrix();


void calculateR();
void calculateC();


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> r >> c >> k;

    for (int row = 1; row <= 3; row++) {
        for (int col = 1; col <= 3; col++) {
            cin >> A[row][col];
        }
    }

    //DebugMatrix();

    int day{ 0 };
    while (day <= 100) {

        if (A[r][c] == k) {
            break;
        }

        if (max_R >= max_C) {
            calculateR();
        }
        else if (max_C > max_R) {
            calculateC();
        }
        //DebugMatrix();
    
        day++;
    }

    if (day == 101) {
        cout << -1;
    }
    else {
        cout << day;
    }

}


void calculateC() {
    int cnt[101] = {}; int MAX = max_R; int TMP[101][101] = {};
    for (int col = 1; col <= max_C; col++) {
        map<int, int>cnt; int now_max_R{ 0 };
        for (int row = 1; row <= MAX; row++) {
            if (A[row][col] != 0) {
                cnt[A[row][col]]++;
            }
        }
        vector<pair<int, int>> new_cnt(cnt.begin(), cnt.end());
        sort(new_cnt.begin(), new_cnt.end(), [](pair<int, int> A, pair<int, int> B) {if (A.second == B.second) { return A.first < B.first; } return A.second < B.second; });
        now_max_R = new_cnt.size() * 2;
        for (int row = 1; row <= now_max_R; row++) {
            if (row % 2 == 0) {
                TMP[row][col] = new_cnt[((row + 1) / 2) - 1].second;
            }
            else {
                TMP[row][col] = new_cnt[((row + 1) / 2) - 1].first;
            }
        }
        if (now_max_R > max_R) {
            max_R = now_max_R;
        }
    }
    for (int row = 1; row <= max_R; row++) {
        for (int col = 1; col <= max_C; col++) {
            if (TMP[row][col] == 0) {
                TMP[row][col] = 0;
            }
        }
    }
    memcpy(A, TMP, sizeof(TMP));
}

void calculateR() {
    int cnt[101] = {}; int MAX = max_C; int TMP[101][101] = {};
    for (int row = 1; row <= max_R; row++) {
        map<int, int>cnt; int now_max_C{ 0 };
        for (int col = 1; col <= MAX; col++) {
            if (A[row][col] != 0) {
                cnt[A[row][col]]++;
            }
        }
        vector<pair<int, int>> new_cnt(cnt.begin(), cnt.end());
        sort(new_cnt.begin(), new_cnt.end(), [](pair<int, int> A, pair<int, int> B) {if (A.second == B.second) { return A.first < B.first; } return A.second < B.second; });
        now_max_C = new_cnt.size() * 2;
        for (int col = 1; col <= now_max_C; col++) {
            if (col % 2 == 0) {
                TMP[row][col] = new_cnt[((col + 1) / 2) - 1].second;
            }
            else {
                TMP[row][col] = new_cnt[((col + 1) / 2) - 1].first;
            }
        }
        if (now_max_C > max_C) {
            max_C = now_max_C;
        }
    }
    for (int row = 1; row <= max_R; row++) {
        for (int col = 1; col <= max_C; col++) {
            if (TMP[row][col] == 0) {
                TMP[row][col] = 0;
            }
        }
    }
    memcpy(A, TMP, sizeof(TMP));
}

void DebugMatrix() {
    for (int row = 1; row <= max_R; row++) {
        for (int col = 1; col <= max_C; col++) {
            cout << A[row][col] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}