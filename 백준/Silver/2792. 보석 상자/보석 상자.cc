#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

int N,M;

int binaryFind(vector<int>& v, int right){
    int left = 1; int ans{-1};

    while(left < right){
        double mid = left + (right - left) / 2;

        int need{0};
        for(auto & n: v){
            need += ceil(n / mid);
        }

        if(need <= N){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    vector<int>v(M); int right{0};
    for(int i = 0; i < M ;i++){
        cin >> v[i];
        if(v[i] > right){
            right = v[i];
        }
    }

    cout << binaryFind(v, right);
    
    return 0;
}