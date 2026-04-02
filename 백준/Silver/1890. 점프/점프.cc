#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

int N;

bool inbound(int nr, int nc);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    vector<vector<long long>>BOARD(N,vector<long long>(N));
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            cin >> BOARD[row][col];
        }
    }

    vector<vector<long long>>DP(N,vector<long long>(N,0));
    DP[0][0] = 1;
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            if(BOARD[row][col] == 0){
                continue;
            }
            for(int d = 0; d < 2; d++){
                if(d == 0){
                    int nr = row + BOARD[row][col]; int nc = col;
                    if(inbound(nr,nc)){
                        DP[nr][nc] += DP[row][col];
                    }
                }
                else{
                    int nr = row; int nc = col + BOARD[row][col];
                    if(inbound(nr,nc)){
                        DP[nr][nc] += DP[row][col];
                    }
                }
            }
        }
    }

    cout << DP[N-1][N-1];
}

bool inbound(int nr, int nc){
    if(nr >= 0 && nr < N && nc >= 0 && nc < N){
        return true;
    }
    return false;
}