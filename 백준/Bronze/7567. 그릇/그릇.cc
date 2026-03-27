#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    
    int height = 10;
    for (int i = 1; i < s.size(); i++) {
        height += (s[i] == s[i-1]) ? 5 : 10;
    }
    
    cout << height << "\n";
    return 0;
}