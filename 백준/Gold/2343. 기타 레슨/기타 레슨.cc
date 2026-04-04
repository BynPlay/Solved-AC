#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

int N, M;

long long binary_find(vector<long long>&v, int sum_min, long long max_min){

    long long left = max_min; long long right = sum_min;
    while(left < right){

    long long mid = left + (right - left) / 2;
        //cout << mid << endl;
        
    long long now_sum {0}; int need_cnt {0};
    for(int i = N - 1; i >= 0; i--){
        if(now_sum + v[i] > mid){
            need_cnt++; now_sum = 0;
        }
        now_sum += v[i];
    }
    need_cnt++;

    if(need_cnt <= M){
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

    vector<long long>v(N); long long sum_min{0}; long long max_min{0};
    for(int i = 0; i < N;i++){
        long long lecture; cin >> lecture;
        v[i] = lecture;
        sum_min += lecture;
        if(v[i] > max_min){
            max_min = v[i];
        }
    }
    
    cout << binary_find(v,sum_min,max_min);
    
}