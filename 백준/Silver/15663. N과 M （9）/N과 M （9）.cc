#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int N, M;
vector<int> v;
vector<int> now;
bool visited[9];
set<vector<int>> s;

void backtrack() {
    if ((int)now.size() == M) {
        s.insert(now);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            now.push_back(v[i]);
            backtrack();
            visited[i] = false;
            now.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    v.resize(N);
    for (int i = 0; i < N; i++) cin >> v[i];
    sort(v.begin(), v.end());

    backtrack();

    for (auto& seq : s) {
        for (int x : seq) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}