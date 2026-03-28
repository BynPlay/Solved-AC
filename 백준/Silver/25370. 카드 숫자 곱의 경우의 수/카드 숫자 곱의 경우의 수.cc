#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

int n;
set<int>s;

void cardSelect(int depth, int mul) {

    if (depth == n) {
        s.insert(mul);
        return;
    }

    for (int i = 1; i <= 9; i++) {

        cardSelect(depth + 1, mul * i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> n;

    cardSelect(0, 1);
    cout << s.size();

}
