#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int DIR[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int H,W;

bool inbound(int nr, int nc){
    if(nr >= 0 && nr < H && nc >= 0 && nc < W){
        return true;
    }
    return false;
}

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;
    H = park.size(); W = park[0].size();
    int now_r = 0; int now_c = 0;

    for(int i = 0; i < park.size(); i++){
        for(int j = 0; j < park[i].size(); j++){
            if(park[i][j] == 'S'){
                now_r = i; now_c = j;
                cout << now_r << ' ' << now_c << endl;
            }
        }
    }
    
    for(auto& r: routes){
        int dir {0};
            if(r[0] == 'E'){
                dir = 0;
            }
            else if(r[0] == 'W'){
                dir = 1;
            }
            else if(r[0] == 'N'){
                dir = 2;
            }
            else if(r[0] == 'S'){
                dir = 3;
            }
        
        bool move {true};
        int nr = now_r; int nc = now_c;
        
        for(int i = 0; i < r[2] - '0' ;i++){
            nr += DIR[dir][0]; nc += DIR[dir][1];
            if(!inbound(nr,nc) || park[nr][nc] == 'X'){
                move = false;
                break;
            }         
        }
        
        if(move == true){
            now_r = nr; now_c = nc;
            cout << now_r << ' ' << now_c << endl;
        }
    }
    answer.push_back(now_r); answer.push_back(now_c);
    
    return answer;
}