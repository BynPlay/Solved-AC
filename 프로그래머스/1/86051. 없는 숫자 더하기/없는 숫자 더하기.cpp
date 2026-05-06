#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> numbers) {
    int answer = -1;
    
    sort(numbers.begin(),numbers.end());
    int count {0}; int sum_no{0};
    
    for(int i = 0; i <= 9;i++){
        if(numbers[i - count] != i){
            count++;
            sum_no += i;
        }
    }
    
    if(sum_no != 0){
        answer = sum_no;
    }
    
    return answer;
}