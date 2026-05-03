#include <string>
#include <vector>

using namespace std;

int dungeons_number{0};

int max_visited{0};

void backtracking(int depth, int now_energy, int visited, vector<bool>& v, const vector<vector<int>>& dungeons){
    
    if(depth == dungeons_number){
        if(visited > max_visited){
            max_visited = visited;
        }
        return;
    }
    
    for(int i = 0; i < dungeons_number; i++){
        
        if(v[i] == false){
            v[i] = true;
            
            bool is_visited {false};
            
            if(now_energy >= dungeons[i][0]){
                visited++; 
                now_energy -= dungeons[i][1];
                is_visited = true;
            }
            
            backtracking(depth + 1, now_energy, visited, v,dungeons);
            
            if(is_visited == true){
                visited--;
                now_energy += dungeons[i][1];
            }
            
            v[i] = false;
        }

        
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    dungeons_number = dungeons.size();
    vector<bool> v(dungeons_number,false);
    backtracking(0, k, 0, v, dungeons);
    
    answer = max_visited;
    
    return answer;
}