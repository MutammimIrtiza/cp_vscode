struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t xx) : x(xx % mod) { if (x < 0) x += mod; }
    int val() const { return x; }
    mint& operator++() { if (++x == mod) x = 0; return *this; }
    mint& operator--() { if (x == 0) x = mod; --x; return *this; }
    mint operator++(int32_t) { mint res(*this); ++*this; return res; }
    mint operator--(int32_t) { mint res(*this); --*this; return res; }
    mint& operator+=(const mint& b) { x += b.x; if (x >= mod) x -= mod; return *this; }
    mint& operator-=(const mint& b) { x -= b.x; if (x < 0) x += mod; return *this; }
    mint& operator*=(const mint& b) { x = (int)((1LL * x * b.x) % mod); return *this; }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint& operator/=(const mint& b) { return *this *= b.inv(); }
    mint inv() const { return power(mod - 2); }
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

mint ncr_fact(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (n < N) return fact[n] * inv_fact[r] * inv_fact[n - r];
    if (r > n - r) r = n - r;
    mint num = 1, den = 1;
    for (ll i = 0; i < r; i++) {
        num *= mint(n - i);
        den *= mint(i + 1);
    }
    return num / den;
}
mint ncr_lucas(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    mint res = 1;
    while (n || r) {
        ll ni = n % mod;
        ll ri = r % mod;
        if (ri > ni) return 0;
        res *= ncr_fact(ni, ri);
        n /= mod;
        r /= mod;
    }
    return res;
}
mint ncr(ll n, ll r) {
    if (n < 0 || r < 0) return 0;
    if (n < N) return ncr_fact(n, r);
    return ncr_lucas(n, r);
}


void prep() {
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i;
    inv_fact[N - 1] = fact[N - 1].inv();
    for (int i = N - 2; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1);
}