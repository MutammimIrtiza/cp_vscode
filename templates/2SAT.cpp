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
const int N = 100005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

// variables are zero indexed
struct twosat {
  int n;  
  vector< vector<int> > g, gt;
  vector<bool> vis, res;
  vector<int> comp;
  stack<int> ts;
  twosat(int vars = 0) {
    n = vars << 1;
    g.resize(n);
    gt.resize(n);
  }

  //if you want to force variable a to be true : addOR (a,1,a,1);
  //if you want to force variable a to be false : addOR (a,0,a,0);
  
  // adds an implication
  void _add(int a,bool sign_a,int b,bool sign_b) {
    a += a + (sign_a ^ 1);
    b += b + (sign_b ^ 1);
    g[a].push_back(b);
    gt[b].push_back(a);
  }
  //(x_a or (not x_b))-> sign_a=1,sign_b=0
  void addOR(int a, bool sign_a, int b, bool sign_b) {
    a += a + (sign_a ^ 1);
    b += b + (sign_b ^ 1);
    g[a ^ 1].push_back(b);  // !a => b
    g[b ^ 1].push_back(a);  // !b => a
    gt[b].push_back(a ^ 1);
    gt[a].push_back(b ^ 1);
  }
  //(!x_a xor !x_b)-> sign_a=0, sign_b=0
  void addXOR(int a, bool sign_a, int b, bool sign_b) {
    addOR(a, sign_a, b, sign_b);
    addOR(a, !sign_a, b, !sign_b);
  }
  void dfs1(int u) {
    vis[u] = true;
    for(int v : g[u]) if(!vis[v]) dfs1(v);
    ts.push(u);
  }
  void dfs2(int u, int c) {
    comp[u] = c;
    for(int v : gt[u]) if(comp[v] == -1) dfs2(v, c);
  }
  bool run() { // returns true if possible, else false
    vis.resize(n, false);
    for(int i = 0; i < n; ++i) if(!vis[i]) dfs1(i);
    int scc = 0;
    comp.resize(n, -1);
    while(!ts.empty()) {
      int u = ts.top();
      ts.pop();
      if(comp[u] == -1) dfs2(u, scc++);
    }
    res.resize(n / 2);
    for(int i = 0; i < n; i += 2) {
      if(comp[i] == comp[i + 1]) return false;
      res[i / 2] = (comp[i] > comp[i + 1]);
    }
    return true;
  }
};

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){ // https://cses.fi/problemset/task/1684/ 
    
    // testcases ?

    // cleanup ?

    cin >> n >> m;
    twosat ts(m);
    L(i, 1, n) {
        char s1, s2; int x1, x2; cin >> s1 >> x1 >> s2 >> x2;
        x1--, x2--;
        bool _s1 = s1=='+' ? true : false;
        bool _s2 = s2=='+' ? true : false;
        ts.addOR(x1, _s1, x2, _s2);
    }
    bool ok = ts.run();
    if(!ok) {cout << "IMPOSSIBLE" << nl; return;}
    L(i,0,m-1) cout << (ts.res[i]==true ? '+' : '-') << gp;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}