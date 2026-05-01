#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(auto &i: commands){
        vector<int>v;
        for(int j = i[0] - 1; j < i[1]; j++){
            v.push_back(array[j]);
        }
        sort(v.begin(),v.end());
        answer.push_back(v[i[2] - 1]);
    }
    
    return answer;
}