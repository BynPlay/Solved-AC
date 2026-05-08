#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> ingredient) {
    int answer = 0;
    deque<int>dq;
    
    for(auto& i: ingredient){
        int ps = dq.size();
        if(i == 1 && ps >= 3 && dq[ps-1] == 3 && dq[ps-2] == 2 && dq[ps-3] == 1){
            for(int j = 0; j < 3; j++){
                dq.pop_back();
            }
            answer++;
        }
        else{
            dq.push_back(i);
        }
    }
    
    return answer;
}