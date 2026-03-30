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

    int N,S; cin >> N >> S;
    vector<int>v(N);
    
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }

    int cnt{0};
    
    for(int mask = 1; mask < (1 << N); mask++){
        int sum{0};

        for(int bit = 0; bit < N; bit++){
            if(mask & (1 << bit)){
                sum += v[bit];
            }
        }
        
        if(sum == S){
            cnt++;
        }
    }
    cout << cnt;
    }
