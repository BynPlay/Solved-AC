#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int INF{ INT_MAX };

vector<vector<char>>FLAG(6, vector<char>(9));

vector<pair<char, int>> findMax(int pos) {
    
    vector<pair<char, int>>LIST;

    vector<pair<int, char>>Alph(26);
    for (int a = 0; a < 26; a++) {
        Alph[a].second = 'A' + a;
    }
    for (int row = pos; row < pos + 2; row++) {
        for (int col = 0; col < 9; col++) {
            Alph[FLAG[row][col] - 'A'].first++;
        }
    }
    sort(Alph.begin(), Alph.end());

    LIST.push_back({ Alph[25].second,Alph[25].first });
    LIST.push_back({ Alph[24].second,Alph[24].first });
    LIST.push_back({ Alph[23].second,Alph[23].first });

    return LIST;
}

vector<pair<char, int>> findMax2(int pos) {

    vector<pair<char, int>>LIST;

    vector<pair<int, char>>Alph(26);
    for (int a = 0; a < 26; a++) {
        Alph[a].second = 'A' + a;
    }
    for (int row = 0; row < 6; row++) {
        for (int col = pos; col < pos + 3; col++) {
            Alph[FLAG[row][col] - 'A'].first++;
        }
    }
    sort(Alph.begin(), Alph.end());

    LIST.push_back({ Alph[25].second,Alph[25].first });
    LIST.push_back({ Alph[24].second,Alph[24].first });
    LIST.push_back({ Alph[23].second,Alph[23].first });

    return LIST;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    for (int row = 0; row < 6; row++) {
        string rows; cin >> rows;
        for (int col = 0; col < 9; col++) {
            FLAG[row][col] = rows[col];
        }
    }
 
    int max_int{ 0 };

    vector<pair<char, int>>TOP = findMax(0);
    vector<pair<char, int>>MID = findMax(2);
    vector<pair<char, int>>BOTTOM = findMax(4);

    for (int t = 0; t < 2; t++) {
        for (int m = 0; m < 2; m++) {
            for (int b = 0; b < 2; b++) {
                if (TOP[t].first != MID[m].first && BOTTOM[b].first != MID[m].first) {
                    if (TOP[t].second + MID[m].second  + BOTTOM[b].second > max_int) {
                        max_int = TOP[t].second + MID[m].second + BOTTOM[b].second;
                    }
                }
            }
        }
    }

    vector<pair<char, int>>LEFT = findMax2(0);
    vector<pair<char, int>>CENTER = findMax2(3);
    vector<pair<char, int>>RIGHT = findMax2(6);

    for (int t = 0; t < 2; t++) {
        for (int m = 0; m < 2; m++) {
            for (int b = 0; b < 2; b++) {
                if (LEFT[t].first != CENTER[m].first && RIGHT[b].first != CENTER[m].first) {
                    if (LEFT[t].second + CENTER[m].second + RIGHT[b].second > max_int) {
                        max_int = LEFT[t].second + CENTER[m].second + RIGHT[b].second;
                    }
                }
            }
        }
    }

    cout << 54 - max_int;
}