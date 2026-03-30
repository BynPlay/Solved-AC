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

    int N; cin >> N;

    priority_queue<int,vector<int>,greater<int>>pq;

    for(int i = 0; i < N; i++){
        int num; cin >> num;
        pq.push(num);
    }

    int ans{0};
    while(pq.size() > 1){
        int top = pq.top(); pq.pop();

        int merged = top + pq.top(); pq.pop();
        ans += merged;
        pq.push(merged);
    }
    cout << ans;
}