struct Seg {
    using T = int;                 // change type if needed
    static constexpr T unit = 0;   // identity element
    int n;   vector<T> t;

    Seg(int _n = 0) : n(_n), t(2 * n, unit) {}
    T f(T a, T b) { return a + b; } // change operation

    void update(int p, T value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = f(t[p], t[p^1]);
    }
    T query(int l, int r) { // [l, r)
        T resL = unit, resR = unit;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = f(resL, t[l++]);
            if (r & 1) resR = f(t[--r], resR);
        }
        return f(resL, resR);
    }
};