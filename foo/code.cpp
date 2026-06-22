#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(x) = no. of elements strictly less than x

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, \
 rb_tree_tag,tree_order_statistics_node_update>

#define int long long
#define ll long long
#define lld long double
#define vi vector<int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vll>
#define vvvll vector<vvll>
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
#define gp " "
#define nl "\n"
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl

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


struct mint{
 ll x; mint() { x=0; }
 mint(ll xx) {x = xx%mod; if(x<0)x+=mod; }

 mint& operator+=(mint b){ x=(x + b.x)%mod; return *this; }
 mint& operator*=(mint b){ x=(x * b.x)%mod; return *this; }
 mint& operator-=(mint b){ x=(x - b.x +mod)%mod; return *this;}

 friend mint operator+(mint a,mint b){ return a+=b; }
 friend mint operator-(mint a,mint b){ return a-=b; }
 friend mint operator*(mint a,mint b){ return a*=b; }
};

void solve(int tcase){
/*
    unlike most string dp problems, 
    the only strings of our concern are those centered at the center.
    This reduces time complexity.
*/
    string s; cin >> s;
    int n = sz(s); 
    s = " " + s;
    
    bool ispal[n+1][n+1]; memset(ispal,0,sizeof ispal);
    L(i,1,n) ispal[i][i] = 1;
    R(i,n-1,1) {
        L(j,i+1,n){
            ispal[i][j] = (s[i]==s[j]) && (j==i+1 || ispal[i+1][j-1]);
        }   
    }

    mint dp_sum_of_x_sq[n+1]; 
    mint dp_sum_of_x[n+1]; 
    mint dp_cnt[n+1]; 

    int m = n/2;
    if(n&1) dp_sum_of_x_sq[m+1] = 1, dp_sum_of_x[m+1] = 1, dp_cnt[m+1] = 1;
    
    R(l,m,1) {
        ll r = n-l+1;
        if(ispal[l][r]) {
            dp_sum_of_x_sq[l] = 1, dp_sum_of_x[l] = 1, dp_cnt[l] = 1; 
        }
        if(n%2==0 and ispal[l][m] and ispal[m+1][r]) {
            dp_sum_of_x_sq[l] += 4, dp_sum_of_x[l] += 2, dp_cnt[l] += 1;
        }
        L(len,1,n/2-l+1) {
            if(!ispal[l][l+len-1]) continue;
            if(!ispal[r-len+1][r]) continue;
            if(n%2==0 and len==n/2-l+1) continue;
            dp_sum_of_x_sq[l] += dp_sum_of_x_sq[l+len] + 4*dp_sum_of_x[l+len] + 4*dp_cnt[l+len];
            dp_sum_of_x[l] += dp_sum_of_x[l+len] + 2 * dp_cnt[l+len];
            dp_cnt[l] += dp_cnt[l+len];
        }
    }
    cout << dp_sum_of_x_sq[1].x << '\n';

}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t = 1;
    cin >> t;
    L(i, 1, t) solve(i);
}