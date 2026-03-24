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

bool inbound(int nr, int nc);


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int N; cin >> N;
    vector<int>SKILLS(N + 1);
    for (int i = N; i > 0; i--) {
        cin >> SKILLS[i];
    }

    deque<int>d;
    for (int i = 1; i <= N; i++) {

        if (SKILLS[i] == 1) {
            d.push_front(i);
        }
        else if (SKILLS[i] == 2) {
            int top = d.front(); d.pop_front();
            d.push_front(i); d.push_front(top);
        }
        else if (SKILLS[i] == 3) {
            d.push_back(i);
        }
    }

    for (auto& i : d) {
        cout << i << ' ';
    }

    return 0;
}