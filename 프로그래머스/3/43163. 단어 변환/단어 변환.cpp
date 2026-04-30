#include <string>
#include <queue>
#include <vector>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    
    vector<bool>DIST(words.size(),false);
    
    queue<pair<string,int>>q; q.push({begin,0});
    
    while(!q.empty()){
        pair<string,int> now = q.front(); q.pop();
        
        if(now.first == target){
            answer = now.second;
            break;
        }
        
        for(int word = 0; word < words.size(); word++){
            int diff {0};
            for(int ch = 0; ch < words[word].size(); ch++){
                if(words[word][ch] != now.first[ch]){
                    diff++;
                }
            }
            if(diff == 1 && DIST[word] == false){
                q.push({words[word], now.second + 1});
                DIST[word] = true;
            }
        }
    }
    
    return answer;
}