#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    
    int st = triangle.size();
    
    vector<vector<int>>DP(st,vector<int>(st,-1));
    DP[0][0] = triangle[0][0];
    
    for(int i = 1; i < st; i++){
        for(int j = 0; j <= i; j++){
            DP[i][j] = max(DP[i-1][j-1],DP[i-1][j]) + triangle[i][j];
        }
    }
    
    for(int i = 0; i < st ;i++){
        if(answer < DP[st-1][i]){
            answer = DP[st-1][i];
        }
    }
    
    return answer;
}