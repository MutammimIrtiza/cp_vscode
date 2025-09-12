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
#define nl "\n"
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define isSet(x, i) ((x>>i)&1)

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
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////


ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N);

// query : min max
// update : range assignment
struct minMaxSeg{
    struct node{
        ll mn = inf;                                            // TODO
        ll mx = -inf;                                           // TODO
        ll lazy = inf;                                          // TODO
 
        node() {}
        node(ll x) : mn(x), mx(x) {}
        void apply(int l, int r, ll y) {                        // TODO
            mn = mx = y;
            if(l != r) lazy = y; // => applied here, but pending in children
        }
    };

    int size;
    vector<node> tree;

    minMaxSeg(vll & a) {
        ll n = sz(a) - 1;                           // TODO: rem -1 for 0 based
        size = 1; while(size < n) size *= 2;
        tree.assign(2 * size , node()); // 

        For(i, 1, n) { // leaves (input array)      // TODO: 0 to n-1 for 0 based
            tree[size + i - 1] = a[i];              // TODO: rem -1 for 0 based
        }
        for(ll j = size - 1; j >= 1; j--) { // tree is 1 based
            pull(j);
        }
    }

    node unite(node a, node b){                                     // TODO
        node res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        return res;
    }
    void push(int pos, int l, int r){
        if(l == r) return;
        if (tree[pos].lazy != inf) {  
            int mid = (l + r) / 2;
            tree[2*pos].apply(l, mid, tree[pos].lazy);
            tree[2*pos+1].apply(mid+1, r, tree[pos].lazy);
            tree[pos].lazy = inf;                                   // TODO
        }
    }
    void pull(int pos){
        tree[pos] = unite(tree[pos * 2], tree[pos * 2 + 1]);
    }


    node query(int ql, int qr){
        return query(1, 1, size, ql, qr);
        // return query(1, 0, size-1, ql, qr);                       // 0 based
    }
    node query(int pos, int l, int r, int ql, int qr) {
        push(pos, l, r);
        if (l >= ql && r <= qr) { return tree[pos];}
        int mid = (l + r) / 2;
        node res;
        if (qr <= mid) res = query(2 * pos, l, mid, ql, qr);
        else if (ql > mid) res = query(pos * 2 + 1, mid + 1, r, ql, qr);
        else res = unite(query(pos * 2, l, mid, ql, qr), 
                            query(pos * 2 + 1, mid + 1, r,  ql, qr));
        pull(pos);
        return res;
    }


    void modify(int ql, int qr, ll y) {
        modify(1, 1, size, ql, qr, y);
        // modify(1, 0, size-1, ql, qr, y);                         // 0 based
    }
    void modify(int pos, int l, int r, int ql, int qr, ll y){
        push(pos, l, r);
        if (l >= ql && r <= qr){
            tree[pos].apply(l, r, y);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) modify(2 * pos, l, mid, ql, qr, y);
        if (qr > mid) modify(2 * pos + 1, mid + 1, r, ql, qr, y);
        pull(pos);
    }    #include<bits/stdc++.h>
    using namespace std;

    using ll = long long;
    using vll = vector<long long>;
    using pll = pair<long long, long long>;

    #define F first 
    #define S second
    #define all(v) v.begin(),v.end()
    #define For(i,a,b) for(long long i=(a); i<=(b); ++i)
    #define Size(x) (ll)((x).size())
    #define gp " "

    #define DEBUG

    #ifdef DEBUG
    #define debug(n) cout<<__LINE__<<" "<<#n<<" "<<n<<endl;
    #define debugc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<el<<" ";}cout<<']'<<endl;
    #define debugcc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<'{'<<" "<<el.F<<','<<el.S<<" "<<'}'<<" ";}cout<<']'<<endl;
    #else
    #define debug(n) // single variable, string
    #define debugc(a) // vector, deque, array
    #define debugcc(a) // map, vector<pll>
    #endif
    
    const int mod = 1e9 + 7;
    const int N = 1e6 + 5;


struct DisjointSet {
    vll par, sz; ll c; vll exp;

    DisjointSet(ll n){
        sz.resize(n+1, 0LL); par.resize(n+1,0LL); c = n; exp.resize(n+1, 0LL);

        For(i, 0, n) {
            par[i] = i, sz[i] = 1;
        }
    }

    ll getSize(ll node) {
        return sz[findUlt(node)];
    }

    ll cccnt(){
        return c;
    }

    ll findUlt(ll node){ // findUPar
        if(par[node] == node) return node; // root

        ll x = findUlt(par[node]); // x = root

        // do stuff here if needed
        // passing down is not needed for node just below root, coz connection stays
        // else, connection will be gone due to path compression
        // so we push down exp[par[node]] 
        // NOT exp[x]. careful
        // also, this par[node] is never going to store anything in future, so its ok
        // bye bye par[node]. x is the new par. you have done your job and passed down :)
        if(par[node] != x)  exp[node] += exp[par[node]];
        

        par[node] = x; // path compression. remove ???

        return x;
    }

    void Union(ll u, ll v){ // finds and unites roots
        ll ulpu = findUlt(u); ll ulpv = findUlt(v);
        if(ulpu == ulpv) return;
        --c;
        if(sz[ulpu] < sz[ulpv]) swap(ulpu, ulpv);

        par[ulpv] = ulpu;
        sz[ulpu] += sz[ulpv]; 

        // do stuff here if needed
        exp[ulpv] -= exp[ulpu]; // এখনই করে রাখতেসি, কারণ পরে উপর থেকে নিতেইইই হবে 

        
    }

    // extra functions

    void addExp(ll node, ll val){
        exp[findUlt(node)] += val;
    }

    ll getExp(ll node){
        findUlt(node);
        return exp[node] + (par[node] == node ? 0 : exp[par[node]]);
        // exp[ulpu] + extra stored
        // exp[ulpv] - exp[ulpu]
        // sum = exp[ulpv] + extra stored

        // for long chain, it works like induction and all extras are passed down :)
    }
};


ll n,m,k,q;
ll a[N];

void solve(){
    cin >> n >> q;

    DisjointSet ds(n);
    while(q--){
        string typ; cin >> typ;
        if(typ == "add"){
            ll node, val; cin >> node >> val; ds.addExp(node, val);
        }
        else if(typ == "join"){
            ll u, v; cin >> u >> v; ds.Union(u,v);
        }
        else{
            ll x; cin >> x;
            cout << ds.getExp(x) << endl;
        }
    }
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}
};

void prep(){
    
}


void solve(){
    

// dont forget to cleanup !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

int main() {
    auto begin = std::chrono::high_resolution_clock::now();

    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    prep();
    // int t; cin >> t; while(t--)
    solve();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // cout << "\nTime measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}