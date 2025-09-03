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
vll gr[N];
vll ans(N);
vll which(N);
set<ll> s[N];
 
// put this in a lambda inside dfs if needed. eg: https://codeforces.com/contest/2127/problem/E
ll merge(ll a, ll b) { // merge set no. a and set no. b and return no. of larger set
    if(sz(s[a]) < sz(s[b])) swap(a, b);
    for(ll x : s[b]) s[a].insert(x);
    s[b].clear();
    return a;
}
 
ll dfs(ll node, ll par) {
    ll cur_set = which[node];
    for(ll ch : gr[node]) {
        if(ch == par) continue;
        cur_set = merge(cur_set, dfs(ch, node));
    }
    ans[node] = sz(s[cur_set]);
    return cur_set;
}
 
void solve(){ // cses tree : distinct colors
     
    // testcases ?
 
    // cleanup ?
 
    cin >> n;
    L(i, 1, n) {
        cin >> a[i];
        s[i].insert(a[i]);
        which[i] = i;
    }
    L(i, 1, n-1) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }    
    dfs(1, -1);
    L(i, 1, n) cout << ans[i] << gp;
    cout << nl;
 
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}