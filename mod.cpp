#include <iostream>

using namespace std;

long long safe_mod(long long a, long long b, int mod) {
    return (((a - b) % mod) + mod) % mod;
}
