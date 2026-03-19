#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const int INF{ INT_MAX };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    long long N, S;
    cin >> N >> S;
    vector<int>sequence(N); int ans_length{ INF };

    for (int i = 0; i < N ; i++) {
        cin >> sequence[i];
        if (sequence[i] >= S) {
            ans_length = 1;
        }
    }

    int left = 0; int right = 1; long long now_sum = sequence[left];

    while (right < N) {

        now_sum += sequence[right];

        if (now_sum >= S) {

            //cout << left << ',' << right << ": " << now_sum << endl;

            if (right - left + 1 < ans_length) {
                ans_length = right - left + 1;
            }

            now_sum -= sequence[left];
            left++;
           
            if (left == right) {
                right++;
            }
            else {
                now_sum -= sequence[right];
            }

        }
        else {
            right++;
        }
    }
    
    if (ans_length == INF) {
        cout << 0;
    }
    else {
        cout << ans_length;
    }
}