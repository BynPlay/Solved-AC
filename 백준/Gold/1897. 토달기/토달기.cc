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



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int d; string word; cin >> d >> word;

    set<string>v [1001];

    for (int i = 0; i < d; i++) {
        string w; cin >> w;
        v[w.size()].insert(w);
    }
    
    queue<string>q; q.push(word);
    string ans = word;

    while (true) {
        int size = q.size(); bool succeding{ false };

        for (int c = 0; c < size; c++) {
            string now = q.front(); q.pop();
            ans = now;

            for (auto& next : v[now.size() + 1]) {

                bool is_possible{ true };
                int ch = 0;
                
                for (auto& o : next) {
                    if (o == now[ch]) {
                        ch++;
                        if (ch == now.size()) {
                            succeding = true;
                            q.push(next);
                            break;
                        }
                    }
                }

            }

        }
        if (succeding == false) {
            break;
        }
    }

    cout << ans;
   
}