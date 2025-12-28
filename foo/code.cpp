#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#define int long long
#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
#define vvll vector<vll>
#define vi vector<int>
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
#define extract(m, x) { auto it = (m).find(x); if (it != (m).end()) (m).erase(it); } // set, multiset, map
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
#define msb(x) ((x) ? (63 - __builtin_clzll((unsigned long long)(x))) : -1)
#define lsb(x) ((x) ? (__builtin_ctzll((unsigned long long)(x))) : -1)


#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 1e9 + 7;
// const int N = ; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;

void solve(int tcase){
    
    // testcases ?

    // cleanup ?

    cin >> n >> k;
    vll gr[n+1];
    L(i, 1, n-1) {
        cin >> u >> v;
        gr[u].push_back(v); gr[v].push_back(u);
    }   

    vll minguard(n+1), maxuncv(n+1);
    bool vis[n+1];

    function<void(int, int, int&)>
    dfs = [&](int node, int rad, int &cnt)  {
        minguard[node] = inf, maxuncv[node] = 0; vis[node] = 1;

        for(ll ch : gr[node]) {
            if(!vis[ch]) {
                dfs(ch, rad, cnt);
                minguard[node] = min(minguard[node], minguard[ch]+1);
                maxuncv[node] = max(maxuncv[node], maxuncv[ch]+1);
            }
        }


        if(minguard[node] + maxuncv[node] <= rad) {
            maxuncv[node] = -inf;
        } else {
            if(maxuncv[node] == rad) {
                minguard[node] = 0; cnt++;
                maxuncv[node] = -inf;
            }
        }

        // we leave a node with  0 < maxunc[node] < rad  to be covered by some upper node
        // but the root has no upper node, right?
        // so we need extra check for root

        if(node == 1) {
            if(maxuncv[node] >= 0) cnt++;
        }

    };

    auto ok = [&](ll rad) {
        ll cnt = 0;
        memset(vis, 0, sizeof vis);
        dfs(1, rad, cnt); 
        return cnt <= k;
    };

    ll lo = 0;
    ll hi = n;
    ll ans;
    while(lo <= hi) {
        ll mid = lo+hi>>1;
        if(ok(mid)) {
            ans = mid;
            hi = mid-1;
        } else lo = mid+1;
    }

    cout << ans << nl;

}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int tcase = 1;
    int t; cin >> t; for(; tcase <= t; ++tcase)
    solve(tcase);
}