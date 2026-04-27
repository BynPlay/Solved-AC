#include <vector>
#include <iostream>
#include <stack>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;

    stack<int>s;
    for(auto& n: arr){
        if(s.empty()){
            s.push(n);
            answer.push_back(n);
            continue;
        }
        if(n != s.top()){
            s.push(n);
            answer.push_back(n);
        }
    }
    
    cout << "Hello Cpp" << endl;

    return answer;
}