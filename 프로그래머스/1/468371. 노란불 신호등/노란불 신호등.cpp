#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> signals) {
    int answer = 0;
    
    vector<vector<char>> signal_vector(signals.size());
        
    for(int i = 0; i < signals.size(); i++){
        for(int j = 0; j < signals[i].size(); j++){
            if(j == 0){
                for(int k = 0; k < signals[i][j]; k++){
                    signal_vector[i].push_back('G');
                }
            }
            else if(j == 1){
                for(int k = 0; k < signals[i][j]; k++){
                    signal_vector[i].push_back('Y');
                }
            }
            else if(j == 2){
                for(int k = 0; k < signals[i][j]; k++){
                    signal_vector[i].push_back('R');
                }
            }
        }
    }
    
    int max_count{1};
    for(auto& i: signal_vector){
        max_count *= i.size();
    }
    
    int now = 0; 
    while(true){
        bool is_stop{true};
        for(auto& i: signal_vector){
            if(i[now % i.size()] != 'Y'){
                is_stop = false;
                break;
            }
        }
        now++;
        if(is_stop == true){
            break;
        }
        if(now == max_count){
            now = -1;
            break;
        }
    }
    
    answer = now;
    /*
    for(auto& i : signal_vector){
        for(auto& j : i){
            cout << j;
        }
        cout << endl;
    }
    */
    
    return answer;
}