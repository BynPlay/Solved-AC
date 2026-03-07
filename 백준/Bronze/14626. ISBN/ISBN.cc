#include <iostream>
#include <string>
using namespace std;

int main() {

    string s;
    cin >> s;

    int star = -1;

    for (int i = 0; i < 13; i++) {
        if (s[i] == '*') {
            star = i;
            break;
        }
    }

    for (int x = 0; x <= 9; x++) {

        s[star] = x + '0';

        int sum = 0;

        for (int i = 0; i < 13; i++) {
            int num = s[i] - '0';

            if (i % 2 == 0) sum += num;
            else sum += num * 3;
        }

        if (sum % 10 == 0) {
            cout << x;
            break;
        }
    }
}