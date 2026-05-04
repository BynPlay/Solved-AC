#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    vector<vector<int>>T(n+1,vector<int>(n+1,false));
        
    for(auto& i: results){
        T[i[0]][i[1]] = true; 
    }
    
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(T[i][k] && T[k][j]){
                    T[i][j] = true;
                }
            }
        }
    }
    
    for(int i = 1; i <= n; i++){
        int count{0};
            for(int j = 1; j <= n; j++){
                if(T[i][j] || T[j][i]){
                    count++;
                }
            }
        if(count == n - 1){
            answer++;
        }
        }
    
    return answer;
}