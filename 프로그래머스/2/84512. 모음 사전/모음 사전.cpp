#include <string>
#include <vector>

using namespace std;
vector<char>CHAR = {'A', 'E', 'I', 'O', 'U'};
int cnt {0};

int ans {0};

void backtracking(int length, string now, const string& word){
    
    if(now == word){
        ans = cnt;
        return;
    }
    
    if(length == 5){
        return;
    }
    
    for(int i = 0; i < 5; i++){
        
        now.push_back(CHAR[i]);
        cnt++;
        backtracking(length + 1, now, word);
        now.pop_back();
        
    }
    
}

int solution(string word) {
    int answer = 0;
    
    backtracking(0, "", word);
    
    answer = ans;
    
    return answer;
}