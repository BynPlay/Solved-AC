#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int answer = 0;
    
    int width_max {0}; int height_max {0}; int size_max{0};
    
    for(auto &i: sizes){
        
        int upright = max(width_max,i[0]) * max(height_max,i[1]);
        int inverted = max(width_max,i[1]) * max(height_max,i[0]);
        
        if(upright < inverted){
            width_max =  max(width_max,i[0]);
            height_max = max(height_max,i[1]);
            size_max = upright;
        }
        else{
            width_max =  max(width_max,i[1]);
            height_max = max(height_max,i[0]);
            size_max = inverted;
        }
    }
    
    answer = size_max;
    
    return answer;
}