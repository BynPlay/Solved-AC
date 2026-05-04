#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    answer = people.size();
    sort(people.begin(),people.end());
    
    int left = 0; int right = people.size() - 1; int coupled{0};
    
    while(left < right){
        if(people[left] + people[right] <= limit){
            left++; right--;
            coupled++;
        }
        else if(people[left] + people[right] > limit){
            right--;
        }
    }
    
    answer -= coupled;
    
    return answer;
}