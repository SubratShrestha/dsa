#include <iostream>
#include <vector>

using namespace std;

// Use sieve of Eratosthenes to find all primes less than n.
vector<int> find_primes(int n) {
    vector<int> primes;
    vector<bool> is_prime(n+1, true);
    for (long long p = 2; p*p <= n; p++) {
        if (is_prime[p])
            for (long long i = 2*p; i<= n; i++) {
                is_prime[i] = false;
            }
    }

    for (int p = 2; p <= n; p++)
        if (is_prime[p])
            primes.push_back(p);

    return primes;
}
