#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

long long mod_pow(long long a, long long b) {
    long long result = 1;
    a %= MOD;

    while (b) {
        if (b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M;
    cin >> M;

    long long ans = 0;

    while (M--) {
        long long N, S;
        cin >> N >> S;

        long long inv = mod_pow(N, MOD - 2);

        ans = (ans + S * inv % MOD) % MOD;
    }

    cout << ans;
}