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


void makeMaxTree(const vector<long long>& SEQUENCES, vector<long long>& MAXSEG, int node, int start, int end);
void makeMinTree(const vector<long long>& SEQUENCES, vector<long long>& MINSEG, int node, int start, int end);

long long searchMax(const vector<long long>& MAXSEG, int node, int start, int end, int left, int right);
long long searchMin(const vector<long long>& MINSEG, int node, int start, int end, int left, int right);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int N, M; cin >> N >> M;
    vector<long long>SEQUENCES(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> SEQUENCES[i];
    }

    vector<long long>MAXTREE(4 * N + 1);
    makeMaxTree(SEQUENCES, MAXTREE, 1, 1, N);

    vector<long long>MINTREE(4 * N + 1, INF);
    makeMinTree(SEQUENCES, MINTREE, 1, 1, N);

    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b; 
        cout << searchMin(MINTREE, 1, 1, N, a, b) << '\n';
    }
    

}


long long searchMax(const vector<long long>& MAXSEG, int node, int start, int end, int left, int right) {

    if (start > right || end < left) {
        return 0;
    }

    if (start >= left && end <= right) {
        return MAXSEG[node];

    }

    int mid = start + (end - start) / 2;

    return max(searchMax(MAXSEG, node * 2, start, mid, left, right), searchMax(MAXSEG, node * 2 + 1, mid + 1, end, left, right));

}

long long searchMin(const vector<long long>& MINSEG, int node, int start, int end, int left, int right) {

    if (start > right || end < left) {
        return INF;
    }

    if (start >= left && end <= right) {
        return MINSEG[node];

    }

    int mid = start + (end - start) / 2;
    
    return min(searchMin(MINSEG, node * 2, start, mid, left, right), searchMin(MINSEG, node * 2 + 1, mid + 1, end, left, right));

}

void makeMaxTree(const vector<long long>& SEQUENCES, vector<long long>& MAXSEG, int node, int start, int end) {

    if (start == end) {
        MAXSEG[node] = SEQUENCES[start];
        return;
    }

    int mid = start + (end - start) / 2;
    makeMaxTree(SEQUENCES, MAXSEG, node * 2, start, mid);
    makeMaxTree(SEQUENCES, MAXSEG, node * 2 + 1, mid + 1, end);

    MAXSEG[node] = max(MAXSEG[node * 2], MAXSEG[node * 2 + 1]);

}

void makeMinTree(const vector<long long>& SEQUENCES, vector<long long>& MINSEG, int node, int start, int end) {

    if (start == end) {
        MINSEG[node] = SEQUENCES[start];
        return;
    }

    int mid = start + (end - start) / 2;
    makeMinTree(SEQUENCES, MINSEG, node * 2, start, mid);
    makeMinTree(SEQUENCES, MINSEG, node * 2 + 1, mid + 1, end);

    MINSEG[node] = min(MINSEG[node * 2], MINSEG[node * 2 + 1]);

}