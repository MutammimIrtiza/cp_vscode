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
const int N = 200005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

    // CENTROID starts
ll n, m, x, y, z, q, k, u, v, w;
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
vll cen_tree[N]; // centroid tree
int form_cen_tree() { // form graph, return root(centroid)
    decompose(1, 0);
    int root;
    L(i, 1, n) {
        if(cenpar[i] == 0) root = i;
        if(cenpar[i] != 0) {
            cen_tree[i].push_back(cenpar[i]);
            cen_tree[cenpar[i]].push_back(i);
        }
    }
    return root;
}
    // CENTROID ends

void prep(){
    
}

bool dead[N];
vector<ar<ll,2>> wgr[N];
vll best(1000006, inf);
ll ans;
vll tem;

void dfs2(ll node, ll par, ll len, ll cnt) { // on main graph ofc
    if(len > k) return;  // ********** TLE ISSUE
    best[len] = min(best[len], cnt), tem.push_back(len);

    for(auto [ch, w] : wgr[node]) {
        if(ch==par || dead[ch]) continue;
        dfs2(ch, node, len+w, cnt+1);
    }
}

void dfs1(ll node, ll par, ll len, ll cnt) { // on main graph ofc
    if(len > k) return;  // ********** TLE ISSUE
    if(best[k - len] != inf) ans = min(ans, best[k - len] + cnt), deb(best[k - len]);

    for(auto [ch, w] : wgr[node]) {
        if(ch==par || dead[ch]) continue;
        dfs1(ch, node, len+w, cnt+1);
    }
}

void run(int peak) {
    best[0] = 0;  // ****************** WA ISSUE
    dead[peak] = 1; 
    for(ll x : tem) best[x] = inf;
    tem.clear();  // ****************** WA ISSUE

    for(auto [ch, w] : wgr[peak]) {
        if(ch and !dead[ch]) {
            dfs1(ch, peak, w, 1);
            dfs2(ch, peak, w, 1);
        }
    }

    for(auto ch : cen_tree[peak]) {
        if(ch and !dead[ch]) run(ch);
    }
}



int best_path(int N, int K, int H[][2], int L[]) {
    /*
        consider all paths with a node as "peak".
        then consider it dead.
        repeat.

        centroid tree gives good complexity for the process.

        [time can be improved slightly by avoiding dfs2 and instead pushing lengths in some vector during dfs1]
    */

    n = N; k = K;
    L(i, 1, n-1) {
        u = H[i-1][0]; v = H[i-1][1]; u++; v++; w = L[i-1];
        wgr[u].push_back({v, w}); wgr[v].push_back({u, w});
        gr[u].push_back(v); gr[v].push_back(u);
    }
    int cen = form_cen_tree();
    ans = inf;
    run(cen);
    return (ans==inf) ? -1 : ans;
}


void solve(int tcase){
    
    // testcases ?

    // cleanup ?

    cin >> n >> k;
    int H[n-1][2]; int L[n-1];
    L(i, 0, n-2) {
        cin >> u >> v >> w; H[i][0] = u, H[i][1] = v, L[i] = w;
    }
    cout << best_path(n,k,H,L) << nl;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int tcase = 1;
    // int t; cin >> t; for(; tcase <= t; ++tcase)
    solve(tcase);
}
