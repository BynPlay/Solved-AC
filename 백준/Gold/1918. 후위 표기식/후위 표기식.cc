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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    string notation; cin >> notation;

    map<char, int>priority; 
    priority['+'] = 0; priority['-'] = 0; 
    priority['*'] = 1; priority['/'] = 1;
    priority['('] = -1; priority[')'] = 2;

    stack<char>s;

    for (auto& i : notation) {
        if (i != '+' && i != '-' && i != '*' && i != '/' && i != '(' && i != ')') {
            cout << i;
        }
        else {
            if (s.size() == 0) {
                s.push(i);
            }
            else if (i == ')') {
                while (s.top() != '(') {
                    cout << s.top(); s.pop();
                }
                s.pop();
            }
            else if (i == '(') {
                s.push(i);
            }
            else if (priority[s.top()] >= priority[i]) {
                while (!s.empty()) {
                    if (priority[s.top()] < priority[i]) {
                        break;
                    }
                    cout << s.top(); s.pop();
                }
                s.push(i);
            }
            else {
                s.push(i);
            }
        }
    }

    while (!s.empty()) {
        cout << s.top(); s.pop();
    }

}

