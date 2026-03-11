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
#include <stack>
#include <cstring>

using namespace std;
const int INF = { INT_MAX };

string A; string B;
int DP[1001][1001];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> A >> B;

    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            if (A[i-1] == B[j-1]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            else {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
    }

    int a = A.size(); int b = B.size(); 
    cout << DP[a][b] << '\n';
    
    /*
    stack<char>s;
    while (a > 0 && b > 0) {
        if (DP[a][b] == DP[a - 1][b]) {
            a -= 1;
            continue;
        }
        else if (DP[a][b] == DP[a][b-1]) {
            b -= 1;
            continue;
        }
        else {
            s.push(A[a-1]);
            a -= 1; b -= 1;
            continue;
        }
    }
    while (!s.empty()) {
        cout << s.top();
        s.pop();
    }
    */
}