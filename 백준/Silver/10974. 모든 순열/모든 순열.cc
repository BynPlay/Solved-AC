#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;

int N;
int visited[9];

void soonyeol(int cnt, int path[9]) {
    
    if (cnt == N+1) {
        for (int i = 1; i <= N; i++) {
            cout << path[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for (int i = 1; i <= N; i++) {
        if (visited[i] == false) {
            path[cnt] = i;
            visited[i] = true;
            soonyeol(cnt + 1, path);
            visited[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N;
   
    int path[9] = {};
    soonyeol(1, path);

    return 0;
}