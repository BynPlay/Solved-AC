#include <string>
#include <vector>

using namespace std;

int count {0};

void backtracking (const string& numbers, vector<bool>& is_prime, string &comp, vector<bool>& visited){
    
    if(!comp.empty() && is_prime[stoi(comp)] == true){
        is_prime[stoi(comp)] = false;
        count++;
    }
    
    if(comp.size() == numbers.size()){
        return;
    }
    
    for(int i = 0; i < numbers.size();i++){
        if(visited[i] == false){
            comp.push_back(numbers[i]);
            visited[i] = true;
            backtracking(numbers, is_prime, comp, visited);
            visited[i] = false;
            comp.pop_back();
        }
    }
}

int solution(string numbers) {
    int answer = 0;
    
    vector<bool> is_prime(10000000, true);
    
    is_prime[0] = false;
    is_prime[1] = false;
    
    for(int i = 2; i * i < 10000000; i++){
        if(is_prime[i]){
            for(int j = i * i; j < 10000000; j += i){
                is_prime[j] = false;
            }
        }
    }
    
    vector<bool>visited(numbers.size(),false);
    string tmp = "";
    
    backtracking(numbers, is_prime, tmp, visited);
    answer = count;
    
    return answer;
}