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
const lld pi = 2*acos(0.0);
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 
vvll gr(N), revgr(N);
vector<bool> vis(N);
stack<ll> st;
void dfs1(ll node) {
    vis[node] = 1;
    for(ll ch : gr[node]) {
        if(!vis[ch]) dfs1(ch);
    }
    st.push(node);
}
void dfs2(ll node, vll &comp) {
    vis[node] = 1;
    comp.push_back(node);
    for(ll ch : revgr[node]) {
        if(!vis[ch]) dfs2(ch, comp);
    }
}
vvll kosaraju() {
    vvll comps;
    L(i, 1, n) if(!vis[i]) dfs1(i);
    L(i, 1, n) vis[i] = 0;
    while(st.size()) {
        ll now = st.top(); st.pop();
        if(!vis[now]) {
            vll comp;
            dfs2(now, comp);
            comps.push_back(comp);
        }
    }
    return comps;
}

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n >> m;
    L(i, 1, m) {
        cin >> u >> v;
        gr[u].push_back(v);
        revgr[v].push_back(u);
    }
    
    vvll comps = kosaraju();
    vll tag(n+1);
    L(i, 1, sz(comps)) {
        for(ll node : comps[i-1]) {
            tag[node] = i;
        }
    }
    cout << sz(comps) << nl;
    L(i, 1, n) cout << tag[i] << gp;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}