#include <string>
#include <vector>

using namespace std;

int N;
vector<int> TIMES;

long long binary_search(long long left, long long right){
    
    while(left < right){
        long long mid = left + (right - left) / 2;
        long long people{0};
        for(auto &i: TIMES){
            people += mid / i;
        }
        if(people >= N){
            right = mid;
        }
        else if(people < N){
            left = mid + 1;
        }
    }
    
    return left;
}

long long solution(int n, vector<int> times) {
    long long answer = 0;
    N = n; TIMES = times;
    
    long long max = 1000000000;
    
    answer = binary_search(0, max * max);
    
    return answer;
}