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

void makeMultiplyTree(const vector<long long>& SEQUENCES, vector<long long>& MAXSEG, int node, int start, int end);
long long searchMul(const vector<long long>& MAXSEG, int node, int start, int end, int left, int right);
void insertMul(vector<long long>& MULSEG, const vector<long long>& SEQUENCES, int node, int start, int end, int idx);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int N, M, K; cin >> N >> M >> K;
    vector<long long>SEQUENCES(N + 1);
    for (int i = 1; i <= N ; i++) {
        cin >> SEQUENCES[i];
    }

    
    vector<long long> MULSEG(4 * N + 10);
    makeMultiplyTree(SEQUENCES, MULSEG, 1, 1, N);

    for (int i = 0; i < M + K; i++) {
        int a, b; cin >> a >> b; long long c; cin >> c;
        if (a == 1) {
            SEQUENCES[b] = c;  // 원본 배열 갱신
            insertMul(MULSEG, SEQUENCES, 1, 1, N, b);
        }
        else {
            cout << searchMul(MULSEG, 1, 1, N, b, c) << '\n';
        }
    }

}

void insertMul(vector<long long>& MULSEG, const vector<long long>& SEQUENCES,
    int node, int start, int end, int idx) {

    if (idx < start || idx > end) return;  

    if (start == end) {
        MULSEG[node] = SEQUENCES[start];  
        return;
    }

    int mid = start + (end - start) / 2;

    if (idx <= mid)
        insertMul(MULSEG, SEQUENCES, node * 2, start, mid, idx);
    else
        insertMul(MULSEG, SEQUENCES, node * 2 + 1, mid + 1, end, idx);

    MULSEG[node] = (MULSEG[node * 2] * MULSEG[node * 2 + 1]) % 1000000007;
}

long long searchMul(const vector<long long>& MulSEG, int node, int start, int end, int left, int right) {

    if (start > right || end < left) {
        return 1;
    }

    if (start >= left && end <= right) {
        return MulSEG[node];

    }

    int mid = start + (end - start) / 2;

    return (searchMul(MulSEG, node * 2, start, mid, left, right) * searchMul(MulSEG, node * 2 + 1, mid + 1, end, left, right)) % 1000000007;

}


void makeMultiplyTree(const vector<long long>& SEQUENCES, vector<long long>& MAXSEG, int node, int start, int end) {

    if (start == end) {
        MAXSEG[node] = SEQUENCES[start];
        return;
    }

    int mid = start + (end - start) / 2;
    makeMultiplyTree(SEQUENCES, MAXSEG, node * 2, start, mid);
    makeMultiplyTree(SEQUENCES, MAXSEG, node * 2 + 1, mid + 1, end);

    MAXSEG[node] = (MAXSEG[node * 2] * MAXSEG[node * 2 + 1]) % 1000000007;

}