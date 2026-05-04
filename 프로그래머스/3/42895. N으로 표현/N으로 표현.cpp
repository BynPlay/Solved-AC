#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>

using namespace std;

int solution(int N, int number) {
    int answer = -1;
    
    unordered_set<int>DP[9];
    DP[1].insert(N);
    
    for(int i = 2; i < 9; i++){
        
        for(int j = 1; j <= i / 2;j++){
            
            for(auto& a: DP[j]){
                 for(auto& b:  DP[i - j]){
                     DP[i].insert(a + b); DP[i].insert(b + a);
                     DP[i].insert(a - b); DP[i].insert(b - a);
                     DP[i].insert(a * b); 
                     if(a != 0){DP[i].insert(b / a);}
                     if(b != 0){DP[i].insert(a / b);}
                 }
            } 
        }
        
        int num{0};
        for(int o = 0; o < i; o++){
            num += N * pow(10,o);
        }
        DP[i].insert(num);
        
    }
    
    for(int i = 1; i < 9; i++){
        bool is_find{false};
        for(auto& n: DP[i]){
            if(n == number){
                answer = i;
                is_find = true;
                break;
            }
        }
        if(is_find == true){
            break;
        }
    }
    
    return answer;
}