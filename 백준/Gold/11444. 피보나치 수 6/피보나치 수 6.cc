#include <iostream>
using namespace std;

const long long MOD = 1000000007;

struct Matrix {
    long long m[2][2];
};

Matrix mul(Matrix a, Matrix b) {
    Matrix res;
    res.m[0][0] = (a.m[0][0]*b.m[0][0]%MOD + a.m[0][1]*b.m[1][0]%MOD)%MOD;
    res.m[0][1] = (a.m[0][0]*b.m[0][1]%MOD + a.m[0][1]*b.m[1][1]%MOD)%MOD;
    res.m[1][0] = (a.m[1][0]*b.m[0][0]%MOD + a.m[1][1]*b.m[1][0]%MOD)%MOD;
    res.m[1][1] = (a.m[1][0]*b.m[0][1]%MOD + a.m[1][1]*b.m[1][1]%MOD)%MOD;
    return res;
}

Matrix pow(Matrix a, long long n) {
    if (n == 1) return a;
    Matrix half = pow(a, n/2);
    Matrix res = mul(half, half);
    if (n%2) res = mul(res, a);
    return res;
}

int main() {
    long long n;
    cin >> n;

    if (n == 0) { cout << 0; return 0; }

    Matrix A = {{{1,1},{1,0}}};
    Matrix res = pow(A, n);
    
    cout << res.m[0][1] << "\n"; // F(n)
}