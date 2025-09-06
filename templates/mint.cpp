struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t xx) : x(xx % mod) { if (x < 0) x += mod; }

    mint& operator+=(const mint& b) { x += b.x; if (x >= mod) x -= mod; return *this; }
    mint& operator-=(const mint& b) { x -= b.x; if (x < 0) x += mod; return *this; }
    mint& operator*=(const mint& b) { x = (int)((1LL * x * b.x) % mod); return *this; }
    mint& operator/=(const mint& b) { return *this *= b.inv(); } 

    mint operator-() const { return mint() - *this; }
    mint inv() const { return power(mod - 2); } // for prime mod only
    mint power(int64_t n) const {
        mint a = *this, res = 1;
        while (n) {
            if (n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    friend bool operator==(const mint& a, const mint& b) { return a.x == b.x; }
    friend bool operator!=(const mint& a, const mint& b) { return a.x != b.x; }
    friend ostream& operator<<(ostream& os, const mint& m) { return os << m.x; }

    explicit operator bool() const { return x != 0; }
};


mint fact[N], inv_fact[N];
void prep_factorials() {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i;
    inv_fact[N - 1] = fact[N - 1].inv();
    for (int i = N - 2; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1);
}

// limitation : small n
mint nCr_precomp(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] * inv_fact[n-r];
}

// limitation : small r
mint nCr_loop(long long n, long long r) {
    if (r < 0 || r > n) return 0;
    mint num(1), den(1);
    for (long long i = 0; i < r; i++) {
        num *= mint(n - i);
        den *= mint(i + 1);
    }
    return num / den;
}

// limitation : small mod
mint nCr_lucas(long long n, long long r) {
    if (r < 0 || r > n) return 0;
    mint res(1);
    while (n > 0 || r > 0) {
        int ni = n % mod, ri = r % mod;
        if (ri > ni) return 0;
        res *= nCr_precomp(ni, ri);
        n /= mod; r /= mod;
    }
    return res;
}

mint nCr(long long n, long long r) {
    if (n < N) return nCr_precomp((int)n, (int)r);
    else if (mod <= N) return nCr_lucas(n, r);
    else if (r < N) return nCr_loop(n, r);
    else {cout << "parina" << nl; exit(0);}
}