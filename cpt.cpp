#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define ld long double
#define vi vector<int>
#define pii pair<int, int>
#define vec vector
#define ar array
#define F first
#define S second

#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define rep(i, a, b) for(long long i = (a); i < (b); ++(i))
#define L(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define R(i, a, b) for(long long i = (a); i >= (b); --(i))
#define sz(x) (ll)(x.size())
#define extract(m, x) \
 { auto it = (m).find(x); if (it != (m).end()) (m).erase(it); }
#define yes cout<<"YES\n"
#define no cout<<"NO\n"

#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)
#define msb(x) (ll)((x) ? (63 - __builtin_clzll((ll)(x))) : -1)
#define lsb(x) (ll)((x) ? (__builtin_ctzll((ll)(x))) : -1)

#ifdef LOCAL
#include "debug.h"
#else
#define deb(...)
#endif

mt19937_64 \
rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 998244353;
// const int N = ; 
const ll inf = 2e18; 

void prep(){

}

void solve(int tcase){
    
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t = 1;
    cin >> t;
    L(i, 1, t) solve(i);
}