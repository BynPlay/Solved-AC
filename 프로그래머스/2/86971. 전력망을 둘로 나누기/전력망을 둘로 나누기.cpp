#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;
int min_ans = INF;

int solution(int n, vector<vector<int>> wires) {
    int answer = -1;
    
    for(int i = 0; i < wires.size(); i++){
        vector<int>TREE[101];
        for(int j = 0; j < wires.size(); j++){

            if(i == j){
                continue;
            }
            
            TREE[wires[j][0]].push_back(wires[j][1]);
            TREE[wires[j][1]].push_back(wires[j][0]);
            
        }
        
        vector<bool>visited(n+1,false); vector<int>linked_num;
        
        for(int k = 1; k <= n; k++){
            if(visited[k] == false){
                queue<int>q; q.push({k}); int cnt {0}; visited[k] = true;
                
                while(!q.empty()){
                    int now = q.front(); q.pop(); cnt++;
                    
                    for(auto&i : TREE[now]){
                        if(visited[i] == false){
                            q.push(i);
                            visited[i] = true;
                        }
                    }
                }
                
                linked_num.push_back(cnt);
            }
        }
        
        int diff = abs(linked_num[0] - linked_num[1]);
        if(diff < min_ans){
            min_ans = diff;
        }
    }

    if(min_ans != INF){
        answer = min_ans; 
    }
    
    return answer;
}