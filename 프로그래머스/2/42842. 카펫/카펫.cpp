#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int w = 3; int h = 3;
    
    while((w * 2) + (h * 2) - 4 <= 5000){
        
        bool is_find {false};
        while(h <= w){
            int now_brown = (w * 2) + (h * 2) - 4;
            int now_yellow = (w * h) -  now_brown;
            if(now_brown == brown && now_yellow == yellow){
                is_find = true;
                answer.push_back(w);
                answer.push_back(h);
                break;
            }
            h++;
        }
        if(is_find == true){
            break;
        }
        w++; h = 3;
    }
    
    return answer;
}