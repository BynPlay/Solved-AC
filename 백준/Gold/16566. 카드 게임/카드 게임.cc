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
const int INF{ INT_MAX };

int find(int x, vector<int>& parent ) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x], parent);
}


int upper_bound_UF(const vector<int>& SEL, vector<int>& parent, int chul) {
    int left = 0; int right = SEL.size(); int idx;

    while (left < right) {

        int mid = left + (right - left) / 2;

        if (chul < SEL[mid]) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    idx = find(left, parent);
    parent[idx] = find(idx + 1, parent);

    return idx;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N, M, K; cin >> N >> M >> K;
   
    vector<int>SEL(M);
    for (int i = 0; i < M; i++) {
        cin >> SEL[i];
    }

    sort(SEL.begin(), SEL.end());

    vector<int>parent(M + 1);
    for (int idx = 0; idx <= M; idx++) {
        parent[idx] = idx;
    }

    for (int i = 1; i <= K; i++) {
        int chul; cin >> chul;
        cout << SEL[upper_bound_UF(SEL, parent, chul)] << endl;
    }
}
