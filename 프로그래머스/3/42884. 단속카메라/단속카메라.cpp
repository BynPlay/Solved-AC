#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Route{
    int start;
    int finish;
    
    bool operator<(Route & rhs) const {return finish < rhs.finish; }
};

int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    vector<Route>ROUTES;
    for(auto&r: routes){
        ROUTES.push_back({r[0],r[1]});
    }
    sort(ROUTES.begin(),ROUTES.end());
    
    vector<bool>visit(routes.size(),false);
    
    for(int i = 0; i < ROUTES.size(); i++){
        if(visit[i] == false){
            visit[i] = true;
            answer++;
            for(int j = i + 1; j < ROUTES.size(); j++){
                if(ROUTES[j].start <= ROUTES[i].finish){
                    visit[j] = true;
                }
            }
        }
    }
    
    return answer;
}