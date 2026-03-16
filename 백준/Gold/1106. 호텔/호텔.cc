#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;
const int INF{ INT_MAX };

struct City {
    int cost;
    int customer;
};

int C, N;
City CITIES[20];

int main() {
    ios::sync_with_stdio(false); //앞은 현재 도시, 뒤는 현재 선택한 개수
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
  
    cin >> C >> N; 
    int max_gain{ 0 };
    for (int i = 0; i < N ; i++) {
        cin >> CITIES[i].cost >> CITIES[i].customer;
        if (CITIES[i].customer > max_gain) {
            max_gain = CITIES[i].customer;
        }
    }


    vector<int>DP(C + max_gain,INF);

    for (auto& j : CITIES) {
        DP[j.customer] = min(DP[j.customer],j.cost);
    }

    for (int i = 0; i < C + max_gain; i++) {
        for (auto &j: CITIES) {
            if (i - j.customer >= 0 && DP[i - j.customer] != INF ) {
                DP[i] = min(DP[i], DP[i - j.customer] + j.cost);
            }
        }
    }
    
    int min_ans{ INF };


    for (int i = C; i < C + max_gain; i++) {
        if (DP[i] < min_ans) {
            min_ans = DP[i];
        }
    }
    cout << min_ans;
}