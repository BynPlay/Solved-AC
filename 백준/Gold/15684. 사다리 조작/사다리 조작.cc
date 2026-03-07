#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <climits>
#include <cstdio>

using namespace std;
int INF = INT_MAX;

int N, M, H;
bool Bridge[31][11];
int min_set{ INF };

void checkBridge();
bool simulateLadder();

void bruteforceBridge(int idx, int cnt) {


    if (simulateLadder() && cnt < min_set) {
        min_set = cnt;
    }
  
    if (cnt == 3) {
        return;
    }

    for (int i = idx; i <= H * (N-1) ;i++) {
        int row = (i - 1) / (N - 1) + 1;
        int col = (i - 1) % (N - 1) + 1;

        if (Bridge[row][col] == true) { continue; }
        if (col - 1 >= 1 && Bridge[row][col-1] == true) { continue; }
        if (col + 1 <= N-1 && Bridge[row][col+1] == true) { continue; }

        Bridge[row][col] = true;
        bruteforceBridge(i + 1, cnt + 1);
        Bridge[row][col] = false;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    cin >> N >> M >> H;

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        Bridge[a][b] = true;
    }

    bruteforceBridge(1,0);

    if (min_set == INF) {
        min_set = -1;
    }

    cout << min_set;

    return 0;
}


void checkBridge() {
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= N-1; j++) {
            cout << Bridge[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

bool simulateLadder() {

    for (int i = 1; i <= N; i++) {
        int now = i;
        int end = now;

        for (int row = 1; row <= H; row++) {
            if (end - 1 >= 1 && Bridge[row][end - 1] == true) {
                end--;
                continue;
            }
            if (end <= N - 1 && Bridge[row][end] == true) {
                end++;
                continue;
            }
         
        }
        if (now != end) {
            return false;
        }
    }

    return true;
}