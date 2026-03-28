#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

struct RobotCat {
    int pos;
    string turn;
};

bool inbound(int n, int A);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    
    long long k; cin >> k; long long now = k;

    long long cnt{ 0 }; vector<long long>v; long long num = 2;

while ((long long)num * num <= now) {  // k → now
    if (now % num == 0) {
        now /= num;
        v.push_back(num);
        cnt++;
        continue;
    }
    num++;
}

if (now > 1) {
    cnt++;
    v.push_back(now);
}

    cout << cnt << endl;
    for (auto& i : v) {
        cout << i << ' ';
    }
}