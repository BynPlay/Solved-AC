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

struct Univ{
int pay;
int day;

bool operator< (const Univ& rhs ) const {
        return pay < rhs.pay;
}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<Univ>univs; 

    for(int i = 0; i < n; i++){
        int p; int d; cin >> p >> d;
        Univ univ = {p,d};
        univs.push_back(univ);
    }
    sort(univs.begin(),univs.end(),[](const Univ &A, const Univ &B){return A.day > B.day;});

    priority_queue<Univ>pq; int now {10000}; int p {0};
    int ans{0};

    while(now > 0){
    while(true){
        if(p < univs.size() && now <= univs[p].day){
            pq.push(univs[p]);
            p++;
        }
        else{
            break;
        }
    }
    if(!pq.empty()){
        ans += pq.top().pay; pq.pop();
    }
    now--;
    }

    cout << ans;
}
