#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>

using namespace std;

struct Lecture{
int ab;
int ac;
int bc;
};

int N, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    vector<int>ab(N);
    vector<int>ac(N);
    vector<int>bc(N);
    for(int i = 0; i < N; i++){
        int a, b, c; cin >> a >> b >> c;
        ab[i] = a + b;
        ac[i] = a + c;
        bc[i] = b + c;
    }

    sort(ab.begin(),ab.end(),greater<int>());
    sort(ac.begin(),ac.end(),greater<int>());
    sort(bc.begin(),bc.end(),greater<int>());

    int mas_ans{0};
    int max_ab{0}; int max_ac{0}; int max_bc{0};
    
    for(int i = 0; i < K; i++){
        max_ab += ab[i];
        max_ac += ac[i];
        max_bc += bc[i];
    }

    cout << max({max_ab,max_ac,max_bc});
 
}