#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = n - lost.size();
    
    sort(lost.begin(),lost.end());
    sort(reserve.begin(),reserve.end());
    
    vector<bool> is_reserved(reserve.size(),false);
    vector<bool> is_mine(lost.size(),false);
    
    
    for(int l = 0; l < lost.size(); l++){
        
        for(int i = 0; i < reserve.size(); i++){
            if(lost[l] == reserve[i]){
                is_reserved[i] = true;
                answer++;
                is_mine[l] = true;
                break;
            }
        }
        
    }
    
    for(int l = 0; l < lost.size(); l++){
        
        if(is_mine[l] == true){
            continue;
        }
        
        for(int i = 0; i < reserve.size(); i++){
            
            if(lost[l] - 1 == reserve[i] && is_reserved[i] == false){
                is_reserved[i] = true;
                answer++;
                break;
            }
            if(lost[l] + 1 == reserve[i] && is_reserved[i] == false){
                is_reserved[i] = true;
                answer++;
                break;
            }
        }
    }
    
    return answer;
}