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

// query : min max sum
// update : range addition
struct Seg{
    struct node{
        ll mn = inf;
        ll mx = -inf;
        ll lazy = 0;
        ll sum = 0;
 
        node() {}
        node(ll x) : mn(x), mx(x), sum(x) {}
        void apply(int l, int r, ll y) {
            mn += y; mx += y;
            sum += y * (r - l + 1);
            if(l != r) lazy += y;    // => applied here, but pending in children

            // mn = mx = y;          // for range assignment
            // sum = y * (r - l + 1) // for range assignment
            // if(l != r) lazy = y;  // for range assignment
        }
    };

    int size;
    vector<node> tree;

    Seg(vll & a) {
        ll n = sz(a);
        size = 1; while(size < n) size *= 2;
        tree.assign(2 * size , node()); 

        For(i, 0, n-1) { // leaves (input array) 
            tree[size + i] = a[i];  
        }
        for(ll j = size - 1; j >= 1; j--) { 
            pull(j);
        }
    }

    node unite(node a, node b){ 
        node res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        res.sum = a.sum + b.sum;
        return res;
    }
    void push(int pos, int l, int r){
        if(l == r) return;
        if (tree[pos].lazy != inf) {  
            int mid = (l + r) / 2;
            tree[2*pos].apply(l, mid, tree[pos].lazy);
            tree[2*pos+1].apply(mid+1, r, tree[pos].lazy);
            tree[pos].lazy = 0;                           // default lazy
        }
    }
    void pull(int pos){
        tree[pos] = unite(tree[pos * 2], tree[pos * 2 + 1]);
    }


    node query(int ql, int qr){
        return query(1, 0, size-1, ql, qr); 
    }
    node query(int pos, int l, int r, int ql, int qr) {
        push(pos, l, r);
        if (l >= ql && r <= qr) { return tree[pos];}
        if (qr < l || ql > r) return node();
        int mid = (l + r) / 2;
        node res;
        if (qr <= mid) res = query(2 * pos, l, mid, ql, qr);
        else if (ql > mid) res = query(pos * 2 + 1, mid + 1, r, ql, qr);
        else res = unite(query(pos * 2, l, mid, ql, qr), 
                            query(pos * 2 + 1, mid + 1, r,  ql, qr));
        return res;
    }


    void modify(int ql, int qr, ll y) {
        modify(1, 0, size-1, ql, qr, y); 
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
    }
};

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n >> q;
    vll a(n);
    L(i, 0, n-1) {
        cin >> a[i];
    }

    Seg seg(a);

    while(q--) {
        int typ; cin >> typ;
        ll l, r;
        if(typ==1) {
            cin >> l >> r >> x;
            seg.modify(--l, --r, x);
        } else {
            cin >> l >> r;
            cout << seg.query(--l, --r).mn << nl;
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}