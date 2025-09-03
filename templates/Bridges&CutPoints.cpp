

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

struct find_bridges_and_cutpoints { // nodes start from 1. edge numbering starts from 0. 
                                    
    struct edge {
        ll node, index;
        edge() {}
        edge(ll _node, ll _index) : node(_node), index(_index) {}
    };

    ll n, m;
    vector<vector<edge>> gr;
    vector<array<ll, 2>> edge_list;
    vector<bool> vis, is_active, is_bridge, is_cutpoint;
    vector<ll> dp;
    vector<ll> back_edge_up_cnt, back_edge_down_cnt;
    vll parent, subtree_size, edge_type, depth;     // for solving problems
                                                    // type0 = back edge, type1 = tree edge 

    find_bridges_and_cutpoints(ll _n) {
        n = _n;
        m = 0;
        gr.assign(n+1, {});
        edge_list.clear();
    }

    void add_edge(ll u, ll v) {
        gr[u].emplace_back(v, m);
        gr[v].emplace_back(u, m);
        edge_list.push_back({u, v});
        m++;
    }

    void dfs(ll node, ll par_edge_idx, ll par) {
        parent[node] = par;
        if(par_edge_idx != -1) edge_type[par_edge_idx] = 1, depth[node] = depth[par]+1;
        vis[node] = is_active[node] = true;
        subtree_size[node] = 1;
        ll ch_cnt = 0;

        for(auto ch : gr[node]) {
            if(ch.node == node) continue;
            if(ch.index == par_edge_idx) continue;
            
            if(vis[ch.node]) {
                if(is_active[ch.node]) {    // prevents considering a back-edge twice
                    back_edge_down_cnt[ch.node]++;
                    back_edge_up_cnt[node]++;
                }
            } else {
                ll prev = back_edge_down_cnt[node];
                dfs(ch.node, ch.index, node);
                dp[node] += dp[ch.node];
                ch_cnt++;
                if(par_edge_idx != -1 and dp[ch.node] == back_edge_down_cnt[node] - prev) is_cutpoint[node] = true;
                subtree_size[node] += subtree_size[ch.node];
            }
        }

        if(par_edge_idx == -1 and ch_cnt > 1) is_cutpoint[node] = true;

        dp[node] += back_edge_up_cnt[node] - back_edge_down_cnt[node];
        if(par_edge_idx != -1) is_bridge[par_edge_idx] = (dp[node]==0);

        is_active[node] = false;
    }

    void run() {
        vis.assign(n+1, false);
        is_active.assign(n+1, false);
        is_bridge.assign(m, false);
        is_cutpoint.assign(n+1, false);
        dp.assign(n+1, 0);
        back_edge_up_cnt.assign(n+1, 0);
        back_edge_down_cnt.assign(n+1, 0);
        parent.assign(n+1, 0);
        subtree_size.assign(n+1, 0);
        edge_type.assign(m+1, 0);
        depth.assign(n+1, 0);

        for (ll i = 1; i <= n; ++i)
            if (!vis[i]) {
                depth[i] = 0;
                dfs(i, -1, -1);
            }
    }
};

vector<bool> vis(N);
vll subtree_size(N);
vll par(N);
void dfs(ll node) {
    vis[node] = 1;
    subtree_size[node] = 1;
    for(ll ch : gr[node]) {
        if(vis[ch]) continue;
        dfs(ch);
        par[ch] = node;
        subtree_size[node] += subtree_size[ch];
    }
}

void solve(){
    
    // testcases ?

    // cleanup ?
    
    cin >> n >> m;

    L(i, 1, n) {
        gr[i].clear();
        vis[i] = false;
        subtree_size[i]=0;
        par[i]= 0;
    }

    find_bridges_and_cutpoints graph(n);
    L(i, 1, m) {
        cin >> u >> v; 
        graph.add_edge(u, v);
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    graph.run();

    dfs(1);
    ll mxrem = 0;
    L(i, 0, m-1) {
        if(graph.is_bridge[i]) {
            ll ch;
            auto [u, v] = graph.edge_list[i];
            if(par[u]==v) ch=u;
            else ch=v;
            mxrem = max(mxrem, subtree_size[ch]*(n-subtree_size[ch]));
        }
    }
    cout << n*(n-1)/2 - mxrem << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}