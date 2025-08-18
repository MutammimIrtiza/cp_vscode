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
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))

template <typename T>
struct ordered_multiset {
    using Tpair = pair<T, int>;
    tree<Tpair,null_type,less<Tpair>,rb_tree_tag,tree_order_statistics_node_update> t;
    int _idx = 0;
    void insert(const T &x) {
        t.insert({x, _idx++});
    }
    void erase(const T &x) {
        auto it = t.lower_bound({x, 0});
        if (it != t.end() && it->first == x)
            t.erase(it);
    }
    int order_of_key(const T &x) const {
        return t.order_of_key({x, 0});
    }
    T find_by_order(int k) const {
        auto it = t.find_by_order(k);
        if (it == t.end()) return 1000000000;
        return it->first;
    }
    int size() const { return t.size();}
    bool empty() const { return t.empty();}
};

#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

struct find_bridges_and_cutpoints { // black box
    struct edge {
        ll node, index;

        edge() {}
        edge(ll _node, ll _index) : node(_node), index(_index) {}
    };

    ll n, m;
    vector<vector<edge>> adj;
    vector<array<ll, 2>> edge_list;

    vector<ll> tin, low, subtree_size;
    vector<bool> visited, is_bridge, is_cutpoint;
    ll timer;

    find_bridges_and_cutpoints(ll _n = 0) {
        init(_n);
    }

    void init(ll _n) {
        n = _n;
        m = 0;
        adj.assign(n+1, {});
        edge_list.clear();
        tin.resize(n+1);
        low.resize(n+1);
        subtree_size.resize(n+1);
    }

    void add_edge(ll u, ll v) {
        adj[u].emplace_back(v, m);
        adj[v].emplace_back(u, m);
        edge_list.push_back({u, v});
        m++;
    }

    void dfs(ll u, ll parent_edge) {
        visited[u] = true;
        tin[u] = low[u] = timer++;
        subtree_size[u] = 1;

        ll children = 0;
        bool cut = false;

        for (edge &e : adj[u]) {
            ll v = e.node;
            if (e.index == parent_edge) continue;

            if (visited[v]) {
                // Back edge
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, e.index);
                low[u] = min(low[u], low[v]);

                if (low[v] > tin[u])
                    is_bridge[e.index] = true;

                if (low[v] >= tin[u] && parent_edge != -1)
                    cut = true;

                subtree_size[u] += subtree_size[v];
                children++;
            }
        }

        // Root condition
        if (parent_edge == -1 && children > 1)
            cut = true;

        is_cutpoint[u] = cut;
    }

    void run() {
        visited.assign(n+1, false);
        is_bridge.assign(m, false);
        is_cutpoint.assign(n+1, false);
        subtree_size.assign(n+1, 0);
        timer = 0;

        for (ll i = 1; i <= n; ++i)
            if (!visited[i])
                dfs(i, -1);
    }
};



void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N);

void solve(){
    cin >> n >> m;
    find_bridges_and_cutpoints graph(n);
    L(i, 1, m){
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    graph.run();

    ll ans = 0;
    L(i, 1, n) {
        for(auto &e : graph.adj[i]) {
            if(graph.is_bridge[e.index]) {
                ll s1 = min(graph.subtree_size[i], graph.subtree_size[e.node]);
                ll s2 = n - s1;
                ans = max(ans, s1 * s2);
            }
        }
    }
    cout << (n*(n-1)/2 - ans) << endl;
// dont forget to cleanup !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}