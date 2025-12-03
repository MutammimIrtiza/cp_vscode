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
const int N = 200005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

ll n, m, x, y, z, q, k, u, v;

    // LCA starts
vll gr[N];
vll depth(N), first(N);
vll in_time(N), out_time(N);
vector<ll> tour;    
vector<vll> st; // Sparse Table for RMQ
ll logn; 
ll timer = 0;

// Build sparse table : st[j][i] = node with min depth among first 2^j nodes in tour starting from i
void build_st() {
    logn = __lg(tour.size()) + 1;
    st.assign(logn, vll(tour.size()));
    st[0] = tour; // store node ids
    for (ll j = 1; j < logn; ++j) {
        for (ll i = 0; i + (1<<j) <= (ll)tour.size(); ++i) {
            ll a = st[j-1][i];  ll b = st[j-1][i + (1<<(j-1))];
            st[j][i] = (depth[a] < depth[b]) ? a : b;
        }
    }
}

void lca_dfs(ll node, ll par, ll dep) {
    in_time[node] = ++timer;
    depth[node] = dep;
    first[node] = tour.size();
    tour.push_back(node);
    for(ll ch : gr[node]) {
        if(ch == par) continue;
        lca_dfs(ch, node, dep + 1);
        tour.push_back(node);  
    }
    out_time[node] = ++timer;
}

void prep_lca(ll root = 1) {
    tour.clear(); tour.reserve(n*2-1);
    lca_dfs(root, -1, 0);
    build_st();
}

ll find_lca(ll u, ll v) {
    ll l = first[u], r = first[v]; 
    if(l > r) swap(l, r);
    ll j = __lg(r - l + 1);
    ll a = st[j][l];    ll b = st[j][r - (1<<j) + 1];
    return (depth[a] < depth[b]) ? a : b;
}

// is u ancestor of v ?
bool is_ancestor(ll u, ll v) {return in_time[u] < in_time[v] and out_time[u] > out_time[v];}

ll distance(ll u, ll v) {
    return depth[u] + depth[v] - 2*depth[find_lca(u, v)];
}
    // LCA ends


vll vadj[N]; // virtual tree
vll aux_tree(vll nodes) {  // ************************ dont forget to do prep_lca before aux_tree
    if(nodes.empty()) return {};
    auto cmp = [](ll n1, ll n2) {return in_time[n1] < in_time[n2];};
    sort(all(nodes), cmp);
    vll temp;
    for(int i = 0; i+1 < sz(nodes); ++i) {
        temp.push_back(find_lca(nodes[i], nodes[i+1]));
    }
    for(auto x : temp) nodes.push_back(x);
    sort(all(nodes), cmp);
    nodes.erase(unique(all(nodes)), nodes.end());
    for(auto x : nodes) vadj[x].clear();

    vll st;
    st.push_back(nodes[0]);
    for(int i = 1; i < sz(nodes); ++i) {
        while(!is_ancestor(st.back(), nodes[i])) st.pop_back();
        vadj[st.back()].push_back(nodes[i]);
        st.push_back(nodes[i]);
    }
    return nodes;
}

void prep(){
    
}


vll w(N), c(N); 
vll col_ver[N];

vll cnt(N); // cnt[node] = ei node koyta virtual tree te ache
void col_dfs(ll node, ll par, ll col) {
    cnt[node]++;
    if(!c[node]) c[node] = col;
    for(ll ch : vadj[node]) {
        if(ch == par) continue;
        col_dfs(ch, node, col);
    }
}

void dfs_down(ll node, ll par, ll col) {
    if(!c[node]) c[node] = col;
    else col = c[node];
    for(ll ch : gr[node]) {
        if(ch == par) continue;
        dfs_down(ch, node, col); // pass down color
    }
}

void solve(){  // https://codeforces.com/contest/2127/problem/E
    
    // testcases ?

    // cleanup ?

    /*
        lets build virtual trees for each color.
        
        colored node:
            in one+ virtual trees => cutie [its lca in a virtual tree thats not its color]
            in one virtual tree => not cutie

        non colored node:
            in one+ virtual tree   => cutie [its lca in two virtual trees. 
                                            give either color, its cutie. give any other color, its cutie]
                                            [lets give it either color. wont create any new cuties]

            in one virtual tree => give it the color of the tree (in col_dfs) => not cutie
            in no virtual tree => give it color of parent => not cutie
    */

    // lots of vectors, use N = 2e5
    
    cin >> n >> k;

    L(i, 1, n) {
        gr[i].clear();
        cnt[i] = 0;
    }
    L(i, 1, k) col_ver[i].clear();

    L(i, 1, n) cin >> w[i];
    L(i, 1, n) {
        cin >> c[i];
        col_ver[c[i]].push_back(i);
    }
    L(i, 1, n-1) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    prep_lca(1);    // ************************ dont forget to do prep_lca
    L(col, 1, k) {
        if(!col_ver[col].size()) continue;
        vll aux_nodes = aux_tree(col_ver[col]);
        col_dfs(aux_nodes[0], -1, col);
    }
    ll cost = 0;
    L(i, 1, n) {
        if(cnt[i] > 1) cost += w[i];
    }
    cout << cost << nl;
    dfs_down(1, -1, rnd()%k+1); 
    L(i, 1, n) cout << c[i] << gp;
    cout << nl;
}   

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}