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
#define vvll vector<vll>
#define vvvll vector<vvll>
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
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl

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

// Extended Euclidean Algorithm
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

inline long long normalize(long long x, long long mod) { x %= mod; if (x < 0) x += mod; return x; }
inline long long LCM(long long a, long long b) { return a / gcd(a, b) * b; }
pll CRT(vll &a, vll &m, ll n) { 
    ll ans = a[1];
    ll lcm = m[1];
    L(i, 2, n) {
        ll x1, y1;
        ll g = ext_gcd(lcm, m[i], x1, y1);
        if((a[i] - ans) % g != 0) {return {0, 0};} // no solution
        ans = normalize(ans + x1 * (a[i] - ans) / g % (m[i] / g) * lcm, lcm * m[i] / g);
        lcm = LCM(lcm, m[i]);
    }
    return {ans, lcm};
}

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?
    
    vll a(3), m(3); // size = no. of equations +1
    L(i, 1, 2) {
        cin >> a[i] >> m[i]; normalize(a[i], m[i]);
    }
    pll x = CRT(a, m, 2);
    if(x.F) cout << x.F << gp << x.S;
    else cout << "no solution";
    cout << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}