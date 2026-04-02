#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;
vector<int>v [32001];

int N,M;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    vector<int>indeed(N + 1, 0);
    
    for(int i = 0; i < M; i++){
        int A, B; cin >> A >> B;
        v[A].push_back(B);
        indeed[B]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq; vector<int>ans;
    
    for(int i = 1; i <= N; i++){
        if(indeed[i] == 0){
            pq.push(i);
        }
    }

    while(!pq.empty()){
        int now = pq.top(); pq.pop();

        ans.push_back(now);

        for(auto &i: v[now]){
            indeed[i]--;
            if(indeed[i] == 0){
                pq.push(i);
            }
        }
    }

    for(auto &k: ans){
        cout << k << ' ';
    }
}