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

// query : range sum
// update : range add
struct sumSeg{
    struct node{
        ll sum = 0;                                              // TODO
        ll lazy = 0;                               // TODO : change both in push
 
        node() {}
        node(ll x) : sum(x) {}
        void apply(int l, int r, ll y) {                         // TODO
            sum += y * (r - l + 1);
            if(l != r) lazy += y; // => applied here, but pending in children
            // sum = y * (r - l + 1);               // assignment
            // if(l != r) lazy = y;                 // assignment
        }
    };

    int size;
    vector<node> tree;

    sumSeg(vll & a) {
        ll n = sz(a) - 1;                           // TODO: rem -1 for pref
        size = 1; while(size < n) size *= 2;
        tree.assign(2 * size , node()); // 

        For(i, 1, n) { // leaves (input array)
            tree[size + i - 1] = a[i];              // TODO: rem -1 for pref
        }
        for(ll j = size - 1; j >= 1; j--) { // tree is 1 based
            pull(j);
        }
    }

    node unite(node a, node b){
        node res;
        res.sum = a.sum + b.sum;                                // TODO
        return res;
    }
    void push(int pos, int l, int r){
        if(l == r) return;
        if (tree[pos].lazy != 0) {                            // TODO
            int mid = (l + r) / 2;
            tree[2*pos].apply(l, mid, tree[pos].lazy);
            tree[2*pos+1].apply(mid+1, r, tree[pos].lazy);
            tree[pos].lazy = 0;                                 // TODO
        }
    }
    void pull(int pos){
        tree[pos] = unite(tree[pos * 2], tree[pos * 2 + 1]);
    }


    node query(int ql, int qr){
        return query(1, 1, size, ql, qr);
        // return query(1, 0, size-1, ql, qr); // pref
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
        // modify(1, 0, size-1, ql, qr, y); // pref
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


void solve(){
    cin >> n; 
    vll a(n+1);
    L(i, 1, n) cin >> a[i];
    sumSeg st(a);
    // cout << st.query(5, 6).mx << gp << st.query(5, 6).mn << endl << nl;
    // cout << st.size << endl;
    cout << nl;
    
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