#include <string>
#include <iostream>
#include <vector>

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    vector<vector<long long>>DP(n+1,vector<long long>(m+1,0));
    
    DP[1][1] = 1;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            
            if(i == 1 && j == 1){
                continue;
            }
            
            bool is_puddle{false};
            for(auto & p:puddles){
                if(i == p[1] && j == p[0]){
                    is_puddle = true;
                }
            }
            if(is_puddle == true){
                continue;
            }
            
            DP[i][j] = (DP[i-1][j] + DP[i][j-1]) % 1000000007;
        }
    }
    
    
    
    answer = DP[n][m];
    return answer;
}