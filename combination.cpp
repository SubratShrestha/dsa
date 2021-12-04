#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 500;
long long f[MAX];

// Calculate the x^n in O(logn) time.
long long modpow(long long x, long long n) {
    if (n == 0) return 1;

    long long a = modpow(x, n/2);
    a = (a * a) % MOD;
    
    // multiply an extra x if n is odd.
    if (n % 2 == 1)
        a = (a * x) % MOD;
    return a;
}

long long inv(long long x) {
    return modpow(x, MOD - 2);
}

void factorials(int n) {
    f[0] = 1;
    for (int i = 1; i < n; i++) {
        f[i] = (i * f[i-1]) % MOD;
    }
}

// Calculate nCk in O(N log MOD) time.
// Depends on factorials array being precomputed.
long long combination(int n, int k) {
    long long res = (f[n] * inv(f[n-k])) % MOD;
    res = (res * inv(f[k])) % MOD;
    return res;
}

int main() {
    int N; cin >> N;
    factorials(N);                        // Here N > a.
    
    int a, b; cin >> a >> b;
    cout << combination(a, b);
    return 0;
}

