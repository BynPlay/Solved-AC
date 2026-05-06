#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

int solution(vector<int> array, int n) {
    int answer = 0;
    int min_diff = INF;
    sort(array.begin(),array.end());
    
    for(auto &i: array){
        int diff = abs(n - i);
        if(diff < min_diff){
            min_diff = diff;
            answer = i;
        }
    }
    
    return answer;
}