#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

int N, M;
set<vector<int>>sNum;

void bruteForceBacktracking(const vector<int>v, vector<int>& list, int depth, int idx);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M;
    vector<int>v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
    vector<int> list;
    bruteForceBacktracking(v, list, 0, 0);

    for (auto& i : sNum) {
        for (auto& j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}


void bruteForceBacktracking(const vector<int>v, vector<int>& list, int depth, int idx) {

    if (depth == M) {
        sNum.insert(list);
        return;
    }

    for (int i = idx; i < N; i++) {
        list.push_back(v[i]);
        bruteForceBacktracking(v, list, depth + 1,i);
        list.pop_back();
    }
}