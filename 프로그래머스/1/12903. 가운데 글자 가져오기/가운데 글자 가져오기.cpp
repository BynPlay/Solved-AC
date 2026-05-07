#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    string answer = "";
    int center = s.size() / 2;
    if(s.size() % 2 == 1){
        answer.push_back(s[center]);
    }
    else{
        answer.push_back(s[center-1]);
        answer.push_back(s[center]);
    }
    
    return answer;
}