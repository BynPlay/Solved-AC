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

bool binary_search(const vector<int>& NOTE_1, int f){
    int low = 0; int high = NOTE_1.size();

    while(low < high){
        int mid = low + (high - low) / 2;

        if(f == NOTE_1[mid]){
            return 1;
        }
        else if(f < NOTE_1[mid]){
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    for(int t = 0; t < T; t++){
        
        int N; cin >> N; vector<int>NOTE_1(N);
        for(int n = 0; n < N; n++){
            cin >> NOTE_1[n];
        }
        
        sort(NOTE_1.begin(),NOTE_1.end());
        
        int M; cin >> M; 
        for(int m = 0; m < M; m++){
            int f; cin >> f;
            cout << binary_search(NOTE_1,f) << '\n';
        }    
    } 
}