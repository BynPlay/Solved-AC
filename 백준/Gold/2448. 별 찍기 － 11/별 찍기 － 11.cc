#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <climits>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

int N; int k;
vector<vector<char>>ans;

// 0 1 2 3 4 5
void makeStar(int n, vector<vector<char>> stars){

    if (n == k) {
        ans = stars;
        return;
    }

    int formal_N = 3 * pow(2, n);
    int new_N = 3 * pow(2, n + 1);

    vector<vector<char>>new_stars(new_N, vector<char>((new_N * 2) - 1,' '));

   
    for (int i = 0; i < formal_N; i++) {
        for (int j = formal_N; j < formal_N + (formal_N * 2) - 1; j++) {
            new_stars[i][j] = stars[i][j-formal_N];
        }
    }

    for (int i = formal_N; i < new_N; i++) {
        for (int j = 0; j < (formal_N * 2) - 1; j++) {
            new_stars[i][j] = stars[i-formal_N][j];
        }
    }
    for (int i = formal_N; i < new_N; i++) {
        for (int j = (formal_N * 2); j < (new_N * 2) - 1; j++) {
            new_stars[i][j] = stars[i - formal_N][j - (formal_N * 2)];
        }
    }

    makeStar(n+1, new_stars);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);

    cin >> N;

    int first_n = 3;
    vector<vector<char>>first{
        {' ',' ','*',' ',' ' },
        {' ','*',' ','*',' '},
        {'*','*','*','*','*'}
    };

    k = log2(N / 3);

    makeStar(0, first);

    for (auto& i : ans) {
        for (auto& j : i) {
            cout << j;
        }
        cout << endl;
    }
}

