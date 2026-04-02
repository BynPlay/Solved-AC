#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

struct Lecture{
    int s;
    int t;

    bool operator< (const Lecture& rhs) const {return t > rhs.t;}
};

int N;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;

    vector<Lecture>v;
    for(int i = 0; i < N; i++){
        int si, ti; cin >> si >> ti;
        v.push_back({si,ti});
    }

    sort(v.begin(),v.end(),[](const Lecture &A, const Lecture &B){ return A.s < B.s;});
    

    priority_queue<Lecture>pq; 

    for(auto&l : v){
        if(!pq.empty() && l.s >= pq.top().t){
            Lecture merged = {pq.top().s,l.t};
            pq.pop();
            pq.push(merged);
        }
        else{
            pq.push(l);
        }
    }

    cout << pq.size();
    
}