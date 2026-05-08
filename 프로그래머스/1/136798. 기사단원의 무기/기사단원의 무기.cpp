#include <string>
#include <vector>

using namespace std;

int PRIME[100001];

int make_prime_number(int num){
    int count {0};
    for(int i = 1; i <= num;i++){
        if(num % i == 0){
            count++;
        }
    }
    return count;
}

int solution(int number, int limit, int power) {
    int answer = 0;

    for(int i = 1; i <= 100000;i++){
        PRIME[i] = make_prime_number(i);
    }
    
    for(int i = 1; i <= number; i++){
        int p = PRIME[i];
        if(p > limit){
            p = power;
        }
        answer += p;
    }
    
    return answer;
}