vector<bool> is_prime;
vll primes;
void sieve(ll n) { 
    is_prime.resize(n + 1, true);  
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
}