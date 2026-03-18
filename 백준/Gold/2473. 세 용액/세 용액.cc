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

bool inbound(int nr, int nc);

void findMove(int row, int col, vector<vector<bool>>& VISITED, const int& id);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    int N; cin >> N; 
    vector<long long>LIQUIDS(N);
    for (int i = 0; i < N; i++) {
        cin >> LIQUIDS[i];
    }
    sort(LIQUIDS.begin(), LIQUIDS.end());

    int final_first = 0; int final_second = 1; int final_third = N - 1;
    long long final_sum = abs(LIQUIDS[final_first] + LIQUIDS[final_second] + LIQUIDS[final_third]);

    for (int sel = 0; sel < N - 2; sel++) {
        int first = sel;

        int start = sel + 1; int end = N - 1; long long sum = abs(LIQUIDS[start] + LIQUIDS[end] + LIQUIDS[first]);
        int second = start, third = end;

        while (true) {

            if (start == end) {
                break;
            }

            if (abs(LIQUIDS[start] + LIQUIDS[end] + LIQUIDS[first]) < sum) {
                sum = abs(LIQUIDS[start] + LIQUIDS[end] + LIQUIDS[first]);
                second = start; third = end;
            }

            if (LIQUIDS[start] + LIQUIDS[end] + LIQUIDS[first] < 0) {
                start++;
            }
            else {
                end--;
            }
        }

        if (sum < final_sum) {
            final_sum = sum;
            final_first = first; final_second = second; final_third = third;
        }

    }

    cout << LIQUIDS[final_first] << ' ' << LIQUIDS[final_second] << ' ' << LIQUIDS[final_third];
   
}
