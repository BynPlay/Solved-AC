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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int n; cin >> n;
    vector<int>A(n); vector<int>B(n); vector<int>C(n); vector<int>D(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }
    
    vector<int>AB(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AB[(i * n) + j] = A[i] + B[j];
        }
    }

    vector<int>CD(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            CD[(i * n) + j] = C[i] + D[j];
        }
    }

    sort(AB.begin(), AB.end());
    sort(CD.begin(), CD.end());

    int left = 0; int right = (n * n) - 1;
    long long ans{ 0 };

    while (right >= 0 && left < n * n) {

        if (AB[left] + CD[right] >= 0) {
            if (AB[left] + CD[right] == 0) {
                long long leftcnt{ 1 }; long long rightcnt{ 1 };
                while (left + leftcnt < n * n && AB[left + leftcnt] + CD[right] == 0) {
                    leftcnt++;
                }
                while (right - rightcnt >= 0 && AB[left] + CD[right - rightcnt] == 0) {
                    rightcnt++;
                }
                ans += leftcnt * rightcnt;
                left = left + leftcnt; right = right - rightcnt;
            }
            else {
                right--;
            }
        }
        else{
            left++;
       }

    }

    cout << ans;

}
