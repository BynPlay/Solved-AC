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
const int INF{ INT_MAX };

int main() {
    ios::sync_with_stdio(false); //앞은 현재 도시, 뒤는 현재 선택한 개수
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    int T; cin >> T;

    for (int t = 0; t < T; t++) {

        int n; cin >> n; vector<int>TABLE(n + 1);
        vector<int>visited(n + 1, 0); int ans{ 0 };

        for (int i = 1; i <= n; i++) {
            cin >> TABLE[i];
            if (TABLE[i] == i) {
                visited[i] = 1;
            }
        }

        for (int i = 1; i <= n; i++) {

            if (visited[i] != 0) {
                continue;
            }

            stack<int>s;
            s.push(i); visited[i] = 2; 

            while (!s.empty()) {

                if (visited[TABLE[s.top()]] == 1) {
                    while (!s.empty()) {
                        visited[s.top()] = 1;
                        s.pop();
                        ans++;
                    }
                    break;
                }
                
                if (visited[TABLE[s.top()]] == 2) {
                    int now = TABLE[s.top()];
                    while (true) {
                        if (s.top() == now) {
                            visited[s.top()] = 1;
                            s.pop();
                            break;
                        }
                        visited[s.top()] = 1;
                        s.pop();
                    }
                    while (!s.empty()) {
                        visited[s.top()] = 1;
                        s.pop();
                        ans++;
                    }
                    break;
                }

                s.push(TABLE[s.top()]);
                visited[s.top()] = 2;
            }
        }

        cout << ans << endl;

    }
}

