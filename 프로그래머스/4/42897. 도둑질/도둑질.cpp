#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>

const int INF = INT_MAX;

using namespace std;

int solution(vector<int> money) {
    int answer = 0;
    
    //첫번쨰거 안훔쳤을떄
    vector<int> DP(money.size(),0);
    DP[0] = -INF; DP[1] = money[1]; DP[2] = max(money[1],money[2]);
    for(int i = 3; i < money.size();i++){
        DP[i] = max(DP[i-2] + money[i],DP[i-1]);
    }
    
    //첫번쨰거 훔쳤을떄
    vector<int> DP2(money.size(),0);
    DP2[0] = money[0]; DP2[1] = DP2[0];
    for(int i = 2; i < money.size() - 1;i++){
        DP2[i] = max(DP2[i-2] + money[i],DP2[i-1]);
    }
    DP2[money.size() - 1] = DP2[money.size() - 2];
    
    answer = max(DP[money.size() - 1],DP2[money.size() - 1]);
    
    return answer;
}