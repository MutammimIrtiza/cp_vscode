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

// spf (smallest prime factor) sieve
vector<int> spf(10000005);
void prep(){ // modified sieve
    L(i, 2, 10000000) {
        if(spf[i] == 0) {
            spf[i] = i;
            for(ll j = i * i; j <= 10000000; j += i) {
                if(spf[j] == 0) spf[j] = i;
            }
        }
    }
}