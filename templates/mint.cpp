struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t xx) : x(xx % mod) { if (x < 0) x += mod; }

    mint& operator+=(const mint& b) { x += b.x; if (x >= mod) x -= mod; return *this; }
    mint& operator-=(const mint& b) { x -= b.x; if (x < 0) x += mod; return *this; }
    mint& operator*=(const mint& b) { x = (int)((1LL * x * b.x) % mod); return *this; }
    mint& operator/=(const mint& b) { return *this *= b.inv(); }

    mint operator-() const { return mint() - *this; }
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
