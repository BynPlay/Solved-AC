#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int pointer = 0;
    
    while(pointer < progresses.size()){
        for(int i = pointer; i < progresses.size(); i++){
            progresses[i] += speeds[i]; 
        }
        if(progresses[pointer] >= 100){
            int num = 1;
            for(int i = pointer + 1; i < progresses.size(); i++){
                if(progresses[i] >= 100){
                    num++;
                }
                else{
                    break;
                }
            }
            answer.push_back(num);
            pointer += num;
        }
    }
    
    return answer;
}