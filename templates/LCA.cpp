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

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

// LCA start
vll gr[N];
vvll lift(N, vll(20)); // binary lifting
vll depth(N); // needed for distance calculation. dist(u, v) = depth[u] + depth[v] - 2*depth[find_lca(u, v)]
vll in_time(N), out_time(N);
ll timer = 0;

void lca_dfs(ll node, ll par, ll dep) {
    in_time[node] = ++timer;
    depth[node] = dep;
    lift[node][0] = par;
    for(int j = 1; j < 20; ++j) {
        if(lift[node][j-1] == -1) lift[node][j] = -1;
        else lift[node][j] = lift[ lift[node][j-1] ][j-1]; 
    }
    for(ll ch : gr[node]) {
        if(ch == par) continue;
        lca_dfs(ch, node, dep+1);
    }
    out_time[node] = ++timer;
}

// is u ancestor of v ?
bool is_ancestor(ll u, ll v) {return in_time[u] < in_time[v] and out_time[u] > out_time[v];}

ll find_lca(ll u, ll v) {
    if(u == v) return u;
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;

    for(ll i = 19; i >= 0; --i) {
        if(lift[u][i] != -1 and !is_ancestor(lift[u][i], v)) {
            u = lift[u][i];
        }
    }
    return lift[u][0];
}

void prep_lca(ll root) {
    timer = 0;
    lca_dfs(root, -1, 0); 
}
// LCA end

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n >> q;
    L(i, 1, n-1) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    prep_lca(1);
    while(q--) {
        cin >> u >> v;
        ll lca = find_lca(u, v);
        cout << depth[u] + depth[v] - 2*depth[lca] << nl;
    }

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}