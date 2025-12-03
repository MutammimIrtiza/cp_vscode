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
#define extract(m, x) { auto it = (m).find(x); if (it != (m).end()) (m).erase(it); } // set, multiset, map
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
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;

const int N = 1<<20; 
vll cnt(N);
vll dp1(N);
vll dp2(N);

void fwd1(vll &dp) { // dp[x] = cnt of submask of x
    L(bit,0,19) {
        L(mask,0,N-1) {
            if(getBit(mask,bit)) dp[mask] += dp[resetbit(mask,bit)];
        }
    }
}

void bak1(vll &dp) {  // return from submask count to mask count
    R(bit,19,0) {
        R(mask,N-1,0) {
            if(getBit(mask,bit)) dp[mask] -= dp[resetbit(mask,bit)];
        }
    }
}

void fwd2(vll &dp) { // dp[x] = cnt of supermask of x
    L(bit,0,19) {
        R(mask,N-1,0){
            if(getBit(mask,bit)) dp[resetbit(mask,bit)] += dp[mask];
        }
    }
}

void bak2(vll &dp) {  // return from supermask count to mask count
    R(bit,19,0) {
        L(mask,0,N-1) {
            if(getBit(mask,bit)) dp[resetbit(mask,bit)] -= dp[mask];
        }
    }
}

void solve(int tcase){
    
    // testcases ?

    // cleanup ?

    /*
        for problems like sum/count involving submaks/supermask, we use sos dp to avoid overcounting.
        x|y = x  :  y is submask of x
        x&y = x  :  y is supermask of x
        x&y = 0  :  y is submask of ~x
    */

    cin >> n; vll a(n+1);
    L(i, 1, n) cin >> a[i], cnt[a[i]]++;
    L(i, 0, N-1) dp1[i] = cnt[i], dp2[i] = cnt[i];
    fwd1(dp1);
    fwd2(dp2);
    L(i, 1, n) cout << dp1[a[i]] << gp << dp2[a[i]] << gp << (n - dp1[a[i]^(N-1)]) << nl;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int tcase = 1;
    // int t; cin >> t; for(; tcase <= t; ++tcase)
    solve(tcase);
}