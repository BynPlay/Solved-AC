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

struct Passenger {
    int seat_R;
    int nowRow{ 0 };
};

struct Airplane {
    deque<Passenger>passengers;
    vector<pair<Passenger,int>>onwaiting;
    bool CORRIDOR[1001] = {};
    int time{ 0 };

    bool timePass() {

        if (passengers.empty() && onwaiting.empty()) {
            return true;
        }

        time++;

        for (int p = passengers.size() - 1; p >= 0; p--) {
            if (CORRIDOR[passengers[p].nowRow + 1] == false) {
                CORRIDOR[passengers[p].nowRow] = false;
                passengers[p].nowRow++;
                CORRIDOR[passengers[p].nowRow] = true;

                if (passengers[p].nowRow == passengers[p].seat_R) {
                    onwaiting.push_back({ passengers[p], 5 });
                    passengers.erase(passengers.begin() + p);
                }
            }
        }

        for (int p = onwaiting.size() - 1; p >= 0; p--) {
            onwaiting[p].second--;
            if (onwaiting[p].second == 0) {
                CORRIDOR[onwaiting[p].first.nowRow] = false;
                onwaiting.erase(onwaiting.begin() + p);
            }

        }

        return false;
    }
};

bool CORRIDOR[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N; cin >> N;

    Airplane airplane;

    for (int i = 1; i <= N; i++) {
        int R; cin >> R;
        airplane.passengers.push_front({ R });
    }

    while (!airplane.timePass());
    cout << airplane.time;

}