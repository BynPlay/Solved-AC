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

void makeSegTree(const vector< long long>& v, vector< long long>& segmentTree, int node, int left, int right);
long long searchInterval(const vector< long long>& segmentTree, int node, int left, int right, int start, int end);
void insertInterval(vector< long long>& segmentTree, int node, int start, int end, int idx, long long diff);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int N, M, K; cin >> N >> M >> K;
    vector< long long>v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    vector< long long>segmentTree(v.size() * 4);
    makeSegTree(v, segmentTree, 1, 0, N - 1);

    for (int j = 0; j < M + K; j++) {
        long long a, b, c; cin >> a >> b >> c;

        if (a == 1) {
            int idx = b - 1;
            insertInterval(segmentTree, 1, 0,  N - 1, idx, c - v[idx]);
            v[idx] = c;
        }
        else if (a == 2) {
            cout << searchInterval(segmentTree, 1, 0, N - 1, b - 1, c - 1) << endl;
        }
    }
 

}

void makeSegTree(const vector< long long>& v, vector< long long>& segmentTree, int node, int left, int right) {

    if (left == right) {
        segmentTree[node] = v[left];
        return;
    }

    int mid = left + (right - left) / 2;

    makeSegTree(v, segmentTree, node * 2, left, mid);
    makeSegTree(v, segmentTree, node * 2 + 1, mid + 1, right);

    segmentTree[node] = segmentTree[node * 2] + segmentTree[node * 2 + 1];
}

long long searchInterval(const vector< long long>& segmentTree, int node, int start, int end, int left, int right) {

    if (end < left || start > right) {
        return 0;
    }

    if (start >= left && end <= right) {
        return segmentTree[node];
    }

    int mid = start + (end - start) / 2;

    return searchInterval(segmentTree, node * 2, start, mid, left, right) + searchInterval(segmentTree, node * 2 + 1, mid + 1, end, left, right);

}

void insertInterval(vector< long long>& segmentTree, int node, int start, int end, int idx, long long diff) {

    if (idx < start || idx > end) return;

    segmentTree[node] += diff;

    int mid = start + (end - start) / 2;

    if (start != end) {
        insertInterval(segmentTree, node * 2, start, mid, idx, diff);
        insertInterval(segmentTree, node * 2 + 1, mid + 1, end, idx, diff);
    }

}