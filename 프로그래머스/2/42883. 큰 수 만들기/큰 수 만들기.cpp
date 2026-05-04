#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    
    stack<int>s;

    for(auto&i: number){
        int now = i - 0;
        while(!s.empty() && s.top() < now && k > 0){
            s.pop();
            k--;
        }
        s.push(now);
    }
    
    while(k > 0){
        s.pop();
        k--;
    }
    
    while(!s.empty()){
        answer.push_back(s.top()); s.pop();
    }
    
    reverse(answer.begin(), answer.end());
    
    
    return answer;
}