#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>

using namespace std; 

int N, M;

bool visited[9];

void premutation(int depth, const vector<int>& v, vector<int>& now) {

    if (depth == M) {
        for (auto& i : now) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }

    for (int i = 0; i < N; i++) {
        if (visited[i] == false) {
            visited[i] = true;
            now.push_back(v[i]);
            premutation(depth+1, v, now);
            visited[i] = false;
            now.pop_back();
        }
    }
}

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

    vector<int> now;
    premutation(0, v, now);

    return 0;
}


