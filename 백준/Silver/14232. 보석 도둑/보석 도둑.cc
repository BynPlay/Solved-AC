#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    cin >> k;

    vector<long long> v;

    for (long long i = 2; i * i <= k; i++) {
        while (k % i == 0) {
            v.push_back(i);
            k /= i;
        }
    }

    if (k > 1) v.push_back(k);

    sort(v.begin(), v.end());

    cout << v.size() << "\n";
    for (auto x : v) cout << x << " ";

    return 0;
}