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
#include <cstring>

int N;
int A[1000];
int MAXDP[1000];
int MINDP[1000];
int BitonicDP[1000];

using namespace std; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;

    for (int i = 0; i < N ; i++) {
        cin >> A[i];
        MAXDP[i] = 1; MINDP[i] = 1;
    }

    
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j]) {
                MAXDP[i] = max(MAXDP[i], MAXDP[j]+1);
            }
        }
    }


    for (int i = N-2; i >= 0; i--) {
        for (int j = N-1; j > i; j--) {
            if (A[i] > A[j]) {
                MINDP[i] = max(MINDP[i], MINDP[j] + 1);
            }
        }
    }
    
    int max_ans{ 0 };
    for (int mid = 0; mid < N; mid++) {
        int left = MAXDP[mid]; int right = MINDP[mid];
        int length = left + right - 1;
        if (length > max_ans) {
            max_ans = length;
        }
    }

    cout << max_ans;
}

