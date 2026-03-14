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

int N, M;

int A[101];
int B[101];

vector<int> DP[101][101];

vector<int>maxDict(pair<int, int>A, pair<int, int>B);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    cin >> M;
    
    for (int j = 1; j <= M; j++) {
        cin >> B[j];
    }





    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {

            if (A[i] == B[j]) {
                for (auto& num : DP[i - 1][j - 1]) {
                    if (A[i] <= num) {
                        DP[i][j].push_back(num);
                    }
                    else {
                        break;
                    }
                }
                DP[i][j].push_back(A[i]);
            }

            else if (A[i] != B[j]) {
                DP[i][j] = maxDict({ i - 1, j }, { i , j - 1 });
            }
        }
    }
   
    /*
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (auto& k : DP[i][j]) {
                cout << k << ',';
            }
            cout << ' ';
        }
        cout << endl;
    }
    */

    cout << DP[N][M].size() << endl;

    for (auto& k : DP[N][M]) {
        cout << k << ' ';
    }

}

vector<int>maxDict(pair<int, int>A, pair<int, int>B) {
    int size_A = DP[A.first][A.second].size(); int size_B = DP[B.first][B.second].size();
    int min_size = min(size_A, size_B);

    for (int i = 0; i < min_size; i++) {
        if (DP[A.first][A.second][i] < DP[B.first][B.second][i]) {
            return DP[B.first][B.second];
        }
        else if (DP[A.first][A.second][i] > DP[B.first][B.second][i]) {
            return DP[A.first][A.second];
        }
    }

    if (size_A >= size_B) {
        return DP[A.first][A.second];
    }
    else {
        return DP[B.first][B.second];
    }

}


