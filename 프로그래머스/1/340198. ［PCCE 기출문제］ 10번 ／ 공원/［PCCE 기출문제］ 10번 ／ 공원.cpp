#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<string>>PARK;
int m_row, m_col;

bool is_possible(int side){
    for(int r = 0; r <= m_row - side; r++){
        for(int c = 0; c <= m_col - side; c++){
            bool is_empty{true};
            for(int i = r; i < r + side; i++){
                for(int j = c; j < c + side; j++){
                    if(PARK[i][j] != "-1"){
                        is_empty = false;
                        break;
                    }
                }
            }
            
            if(is_empty == true){
                return true;
            }
            
        }
    }
    return false;
}

int solution(vector<int> mats, vector<vector<string>> park) {
    int answer = -1;
    PARK = park; m_row = park.size(); m_col = park[0].size();
    
    sort(mats.begin(),mats.end(),greater<int>());
    
    for(auto& i: mats){
        if(is_possible(i)){
            answer = i;
            break;
        };
    }
    
    return answer;
}