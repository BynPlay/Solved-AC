#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

int N;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    priority_queue<int>l;
    priority_queue<int,vector<int>,greater<int>>r;

    for(int i = 0; i < N; i++){
        int n; cin >> n;
        
        if(l.size() <= r.size()){
            l.push(n);
        }
        else{
            r.push(n);
        }

        if(!l.empty() && !r.empty() && l.top() > r.top()){
    int a = l.top(); l.pop();
    int b = r.top(); r.pop();
    l.push(b);
    r.push(a);
}

        cout << l.top() << '\n'; 
    }
}