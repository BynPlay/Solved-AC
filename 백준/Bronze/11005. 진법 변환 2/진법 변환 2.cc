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
const long long INF{ INT_MAX };


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    long long N; int B; cin >> N >> B;

    vector<long long>v; long long now = 1; v.push_back(now);

    while (true) {
        now *= B;
        if (now > N) {
            break;
        }
        v.push_back(now);
    }

    vector<char>ans(v.size(),'0'); long long now_num = N;
    for (int i = v.size() - 1; i >= 0; i--) {
        if (now_num / v[i] > 0) {
            char a;
            if ((now_num / v[i]) >= 10) {
                a = 'A' + ((now_num / v[i]) - 10);
            }
            else {
                a = (now_num / v[i]) + '0';
            }
            ans[i] = a;
            now_num -= v[i] * (now_num / v[i]);
        }
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }

}

