#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <queue>
#include <cstdio>
#include <stack>
#include <cstring>
#include <deque>

using namespace std;
const int INF = { INT_MAX };

struct Jewerly {
    int M;
    int V;
};

int N, K;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> K;
    vector<Jewerly>J(N); vector<int>B(K);

    for (int i = 0; i < N ; i++) {
        cin >> J[i].M >> J[i].V;
    }

    for (int i = 0; i < K; i++) {
        cin >> B[i];
    }

    sort(B.begin(), B.end());  
    sort(J.begin(), J.end(), [](auto& a, auto& b) { return a.M < b.M; });

    priority_queue<int> pq;
    int j = 0;
    long long ans = 0;

    for (int i = 0; i < K; i++) {
        while (j < N && J[j].M <= B[i]) {
            pq.push(J[j].V);
            j++;
        }
        if (!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans;
}