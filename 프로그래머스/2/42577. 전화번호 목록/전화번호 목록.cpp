#include <string>
#include <vector>
#include <map>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    map<string,int>m;
    
    for(auto &p: phone_book){
        m[p]++;
    }
    
    for(auto it = m.begin(); it != m.end(); it++){
        string now = it->first;
        for(int pointer = 1; pointer < now.size(); pointer++){
            if(m.count(now.substr(0, pointer))){
                answer = false;
            };  
        }
    }
    
    return answer;
}