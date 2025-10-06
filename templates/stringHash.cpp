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

using u64 = uint64_t;
struct StringHash {
    static constexpr u64 mod = (1ull<<61) - 1;
    static inline const u64 base = uniform_int_distribution<ll>(256, mod - 1)(rnd);

    ll n; 
    vector<u64> hash, pow;

    static u64 add(u64 a, u64 b) {
        a += b;
        if (a >= mod) a -= mod;
        return a;
    }

    u64 mul(u64 a, u64 b) const {
        u64 l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
        u64 l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
        u64 ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret>>61);
        ret = (ret & mod) + (ret>>61);
        return ret-1;
    }

    StringHash(const string& s) : n(s.size()), 
        hash(n + 1), pow(n + 1, 1)
    {
        for (ll i = 0; i < n; i++) {
            pow[i + 1] = mul(pow[i], base);
            hash[i + 1] = add(mul(hash[i], base), s[i]);
        }
    }

    // return hash for substring [l, r]
    u64 get(ll l, ll r) const {
        u64 x = add(hash[r+1], mod - mul(hash[l], pow[r+1 - l]));
        return x;
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
    StringHash sh(s), ph(p);
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


