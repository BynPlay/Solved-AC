#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

int N;

bool binsearch_find(const vector<long long>& SUMS, long long n){
    int left = 0; int right = SUMS.size();

    while(left < right){
        int mid = left + (right - left) / 2;

        if(n == SUMS[mid]){
            return true;
        }

        else if(n < SUMS[mid]){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;

    vector<long long>v(N);
    for(int i = 0; i < N; i++){
        long long A; cin >> A;
        v[i] = A;
    }

    sort(v.begin(),v.end());
    
    int ans {0};
    
    for(int i = 0; i < N; i++){
        int left = 0; int right = N - 1;

        while(left < right){
            //out << v[i] << ' ' << left << ' ' << right << endl;

            if(left == i){
                left++;
                continue;
            }
            else if(right == i){
                right--;
                continue;
            }

            if(v[i] == v[left] + v[right]){
                ans++;
                break;
            }
            else if(v[i] > v[left] + v[right]){
                left++;
            }
            else{
                right--;
            }
        }
    }

    cout << ans;
}