#include <iostream>

using namespace std;

// Calculate the x^n in O(logn) time.
long long pow(long long x, long long n, int m) {
    if (n == 0) return 1;

    long long a = pow(x, n/2, m);
    a = (a * a) % m;
    
    // multiply an extra x if n is odd.
    if (n % 2 == 1)
        a = (a * x) % m;
    return a;
}
