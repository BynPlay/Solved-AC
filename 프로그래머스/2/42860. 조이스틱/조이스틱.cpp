#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

struct Pointer{
    int idx;
    int moved;
    int cnt;
    vector<bool>visited;
};

int solution(string name) {
    int answer = 0; 
    
    vector<int>DIST(name.size()); 
    vector<bool>visited(name.size(),false);
    
    int number {0};
    for(int i = 0; i < name.size(); i++){
        DIST[i] = min(name[i] - 'A', 26 - (name[i] - 'A'));
        if(DIST[i] != 0){
            answer += DIST[i];
            number++;
        }
    }

   queue<Pointer>q; q.push({0,0,0,visited});
    
    while(!q.empty()){
        Pointer now = q.front(); q.pop();
        
        if(now.visited[now.idx] == false && DIST[now.idx] != 0){
            now.visited[now.idx] = true;
            now.cnt++;
        }
        
        if(now.cnt == number){
            answer += now.moved;
            break;
        }
        
        int left = now.idx - 1;
        if(left < 0){
            left = name.size() - 1;
        }
        int right = now.idx + 1;
        if(right > name.size() - 1){
            right = 0;
        }
        
        q.push({left,now.moved + 1,now.cnt,now.visited});
        q.push({right,now.moved + 1,now.cnt,now.visited});
        
    }
    
    
    return answer;
}