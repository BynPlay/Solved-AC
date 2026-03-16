#include <bits/stdc++.h>
using namespace std;

int main() {
    int C, N;
    cin >> C >> N;

    vector<pair<int,int>> city(N);
    for (auto& [c, g] : city) cin >> c >> g;

    int maxGain = 0;
    for (auto [c, g] : city) maxGain = max(maxGain, g);

    const int INF = 1e9;
    vector<int> dp(C + maxGain, INF);
    dp[0] = 0;

    for (int j = 1; j < C + maxGain; j++) {
        for (auto [cost, gain] : city) {
            int prev = max(0, j - gain);
            if (dp[prev] != INF)
                dp[j] = min(dp[j], dp[prev] + cost);
        }
    }

    int ans = INF;
    for (int j = C; j < C + maxGain; j++)
        ans = min(ans, dp[j]);

    cout << ans;
}