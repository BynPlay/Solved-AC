#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L,C; cin >> L >> C;
    vector<char>alp(C);
    for(int i = 0; i < C; i++){
        cin >> alp[i];
    }
    sort(alp.begin(),alp.end());

    vector<string>ans;
    for(int mask = 0; mask < (1 << C) ; mask++){

        int cnt{0}; string password;
        for(int bit = 0; bit < C; bit++){
            if(mask & (1 << bit)){
                password.push_back(alp[bit]);
                cnt++;
            }
        }
        
        if(cnt != L){
            continue;
        }

        int con{0}; int bow{0};
        for(auto &c: password){
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ){
                con++;
            }
            else{
                bow++;
            }
        }
        if(con >= 1 && bow >= 2){
            ans.push_back(password);
        }
    }
    sort(ans.begin(),ans.end());
    for(auto &s : ans){
        cout << s << '\n';
    }
}
