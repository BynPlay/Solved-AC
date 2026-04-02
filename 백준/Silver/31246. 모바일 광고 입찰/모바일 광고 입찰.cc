#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

int N, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    vector<long long>m(N);
    for(int i = 0; i < N; i++){
        long long A,B; cin >> A >> B;
        m[i] = B - A;
    }

    sort(m.begin(),m.end());
    
    int ans{0};
    for(int s = 0; s < N; s++){
        if(s == K){
            break;
        }
        if(m[s] > 0){
            ans = m[s];
        }
    }

    cout << ans;
    
}