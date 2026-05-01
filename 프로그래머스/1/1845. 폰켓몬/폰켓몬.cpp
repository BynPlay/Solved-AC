#include <vector>
#include <map>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    
    map<int,int>m;
    
    for(auto& i : nums){
        m[i]++;
    }
    
    for(auto it = m.begin(); it != m.end() ; it++){
        answer++;
    }
    
    if(answer > nums.size() / 2){
        answer = nums.size() / 2;
    }
    
    return answer;
}