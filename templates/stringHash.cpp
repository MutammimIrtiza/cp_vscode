// بِسْمِ ٱللّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ //

#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
#define ar array
#define F first
#define S second

#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define For(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define L(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define R(i, a, b) for(long long i = (a); i >= (b); --(i))
#define sz(x) (ll)(x.size())
#define gp " "
#define nl "\n"

#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define getBit(x, i) (((x) >> (i)) & 1)
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)


#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

struct DoubleHash {
    using u64 = uint64_t;
    static inline const u64 mod1 = 1000000007;   
    static inline const u64 mod2 = 1000000009;   
    static inline const u64 base = mt19937_64{random_device{}()}() % (mod1 - 256) + 256;

    ll n; 
    vector<u64> hash1, pow1, hash2, pow2;

    static u64 add(u64 a, u64 b, u64 mod) {
        a += b;
        if (a >= mod) a -= mod;
        return a;
    }
    static u64 mul(u64 a, u64 b, u64 mod) {
        return (a * b) % mod;
    }

    DoubleHash(const string& s) : n(s.size()), 
        hash1(n + 1), pow1(n + 1, 1),
        hash2(n + 1), pow2(n + 1, 1) 
    {
        for (ll i = 0; i < n; i++) {
            pow1[i + 1] = mul(pow1[i], base, mod1);
            pow2[i + 1] = mul(pow2[i], base, mod2);
            hash1[i + 1] = add(mul(hash1[i], base, mod1), s[i], mod1);
            hash2[i + 1] = add(mul(hash2[i], base, mod2), s[i], mod2);
        }
    }

    // return pair of hashes for substring [l, r)
    pair<u64,u64> get(ll l, ll r) const {
        u64 x1 = add(hash1[r], mod1 - mul(hash1[l], pow1[r - l], mod1), mod1);
        u64 x2 = add(hash2[r], mod2 - mul(hash2[l], pow2[r - l], mod2), mod2);
        return {x1, x2};
    }

    // helper: compare two substrings in O(1)
    bool equal(ll l1, ll r1, ll l2, ll r2) const {
        return get(l1, r1) == get(l2, r2);
    }
};


void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){ // https://cses.fi/problemset/task/1753/
    
    // testcases ?

    // cleanup ?

    string s, p; cin >> s >> p;
    DoubleHash sh(s), ph(p);
    auto patternHash = ph.get(0, p.size());
    int ans = 0;
    L(i, 0, sz(s) - sz(p)) {
        ans += sh.get(i, i + sz(p)) == patternHash;
    }
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}