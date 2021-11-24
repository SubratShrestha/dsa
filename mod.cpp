#include <iostream>

using namespace std;

// safe mod function for subtractions, deals with negatives.
long long safe_mod(long long a, long long b, int mod) {
    return (((a - b) % mod) + mod) % mod;
}
