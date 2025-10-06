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
const int N = 200005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

// start
vector<int> gr[N];
int sz[N];
int tot, done[N], cenpar[N];
void calc_sz(int node, int p) {
  tot ++;
  sz[node] = 1;
  for (auto ch : gr[node]) {
    if(ch == p || done[ch]) continue;
    calc_sz(ch, node);
    sz[node] += sz[ch];
  }
}
int find_cen(int node, int p) { // find centroid
  for (auto ch : gr[node]) {
    if(ch == p || done[ch]) continue;
    else if(sz[ch] > tot / 2) return find_cen(ch, node);
  }
  return node;
}
void decompose(int node, int p) { // find centroid of subtree of node, and assign p as parent of the centroid 
  tot = 0;
  calc_sz(node, p);
  int cen = find_cen(node, p);
  cenpar[cen] = p;
  done[cen] = 1;
  for(auto ch : gr[cen]) {
    if(ch == p || done[ch]) continue;
    decompose(ch, cen);
  }
}
vll cen_gr[N]; // cen. decom. tree
int form_cen_gr() { // form graph, return root(centroid)
    decompose(1, 0);
    int root;
    L(i, 1, n) {
        if(cenpar[i] == 0) root = i;
        cen_gr[i].push_back(cenpar[i]);
        cen_gr[cenpar[i]].push_back(i);
    }
    return root;
}
// end



ll ans = 0;
bool niyechi[N]; // for cengr
int cnt[N] = {1}; // cnt[0] = 1, rest 0
int mxdep = 0;
void dfs(int node, int par, int dep, vector<int> &depths_in_subtree) { 
    if(dep>k) return;
    mxdep = max(mxdep, dep);
    ans += cnt[k-dep];
    depths_in_subtree.push_back(dep);
    for(int ch : gr[node]) {
        if(ch==par or niyechi[ch]) continue; // both needed !!!
        dfs(ch, node, dep+1, depths_in_subtree);
    }
}
void guno(ll node) { // on original graph ofc.
    for(int ch : gr[node]) {
        if(niyechi[ch]) continue;
        // update ans first, then cnt array
        vector<int> dephts_in_subtree;
        dfs(ch, node, 1, dephts_in_subtree); // combine with previous subtrees
        for(int d : dephts_in_subtree) cnt[d]++; // from now on its a "previous subtree", so update
    }
}
void dfs_on_cengr(int node) {
    niyechi[node] = 1;
    guno(node);
    L(i, 1, mxdep) cnt[i] = 0; mxdep = 0; // cleanup of guno call. IMPORTANT. CANT DO UPTO n
    for(int ch : cen_gr[node]) {
        if(niyechi[ch]) continue;
        dfs_on_cengr(ch);
    }
}


void solve(){ 
    
    // testcases ?

    // cleanup ?

    /*
        when we want to form all pairs of 1,2,3,4,5 what do we do?
        1 + 2/3/4/5
        2 + 3/4/5
        ...
        ...
        we do the same here.
        count all paths of length k containing some node.
        then ignore it in all next turns.
        but in what order do we fix nodes?
        centroid decomp here gives us an efficient order.
        we CAN form the tree, but its not necessary
    */

    https://cses.fi/problemset/task/2080/
    cin >> n >> k;
    L(i, 1, n-1) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    int cen = form_cen_gr();
    dfs_on_cengr(cen);
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}