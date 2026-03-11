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

using namespace std;
const int INF = { INT_MAX };

int N, K;

bool inBound(int nr, int nc);
bool inBound(int next) {
    if (next >= 0 && next <= 100000) {
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N >> K;

    int MINTIME[100001] = {};
    int ROUTENUM[100001] = {}; ROUTENUM[N]= 1;

    queue<int>q; q.push(N); int sum_route{ 0 };

    while (!q.empty()) {
        int level = q.size();
        bool is_Finished{ false };

        for (int i = 0; i < level; i++) {
            int now = q.front(); q.pop();

            if (now == K) {
                is_Finished = true;
                sum_route += ROUTENUM[now];
            }

            int Move[3] = { {now + 1},{now - 1},{now * 2} };

            for (auto& next : Move) {
                if (inBound(next)) {
                    if (MINTIME[next] == 0) {
                        MINTIME[next] = MINTIME[now] + 1;
                        ROUTENUM[next] += ROUTENUM[now];
                        q.push(next);
                    }
                    else if (MINTIME[next] == MINTIME[now] + 1) {
                        ROUTENUM[next] += ROUTENUM[now];
                    }
                }
            }
        }

        if (is_Finished == true) {
            break;
        }
    }
    
    cout << MINTIME[K] << '\n' << sum_route;
}