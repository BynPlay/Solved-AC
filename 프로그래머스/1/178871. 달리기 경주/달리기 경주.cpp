#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    map<string,int>m;
    
    for(int i = 0; i < players.size();i++){
        m[players[i]] = i;
    }
    
    for(auto& i: callings){
        int rank = m[i]; string prev = players[rank-1];
        m[i] = rank - 1; m[prev] = rank;
        swap(players[rank-1],players[rank]);
    }
    
    answer = players;
    
    return answer;
}