#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<int>A = {1, 2, 3, 4, 5};
    vector<int>B = {2, 1, 2, 3, 2, 4, 2, 5};
    vector<int>C = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    
    int a {0}; int b {0}; int c {0};
    
    for(int i = 0; i < answers.size(); i++){
        int a_index = i % 5; int b_index = i % 8; int c_index = i % 10;
        
        if(answers[i] == A[a_index]){
            a++;
        }
        if(answers[i] == B[b_index]){
            b++;
        }
        if(answers[i] == C[c_index]){
            c++;
        }
        
    }
    
    int ans = max({a,b,c});
    
    if(ans == a){
        answer.push_back(1);
    }
    if(ans == b){
        answer.push_back(2);
    }
    if(ans == c){
        answer.push_back(3);
    }
    
    return answer;
}