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
 
using u64 = uint64_t;
struct SegHash {
    static constexpr u64 mod = (1ull<<61) - 1;
    static inline const u64 base = uniform_int_distribution<ll>(256, mod - 1)(rnd);
 
    struct Node { u64 h = 0; int len = 0; };
    int n; vector<Node> seg; vector<u64> pow; 
 
    SegHash(const string& s) {
        n = s.size(); seg.resize(4*n); pow.resize(n+1, 1);
        for (int i = 1; i <= n; i++) pow[i] = mul(pow[i-1], base);
        build(1, 0, n-1, s);
    }
 
    static u64 add(u64 a, u64 b) { a += b; if (a >= mod) a -= mod; return a; }
    
    static u64 mul(u64 a, u64 b) {
        u64 l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
        u64 l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
        u64 ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret>>61);
        ret = (ret & mod) + (ret>>61);
        return ret-1;
    }
 
    Node merge(const Node& L, const Node& R) {
        Node res;
        res.len = L.len + R.len;
        res.h = add(mul(L.h, pow[R.len]), R.h);
        return res;
    }
 
    void build(int idx, int l, int r, const string& s) {
        if (l == r) { seg[idx].h = s[l];  seg[idx].len = 1;  return; }
        int mid = (l+r)/2;
        build(idx*2, l, mid, s);
        build(idx*2+1, mid+1, r, s);
        seg[idx] = merge(seg[idx*2], seg[idx*2+1]);
    }
 
    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) { seg[idx].h = c;  return; }
        int mid = (l+r)/2;
        if (pos <= mid) update(idx*2, l, mid, pos, c);
        else update(idx*2+1, mid+1, r, pos, c);
        seg[idx] = merge(seg[idx*2], seg[idx*2+1]);
    }
 
    Node query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return {0,0};
        if (ql <= l && r <= qr) return seg[idx];
        int mid = (l+r)/2;
        Node L = query(idx*2, l, mid, ql, qr);
        Node R = query(idx*2+1, mid+1, r, ql, qr);
        return merge(L,R);
    }
 
    // external interface
    void update(int pos, char c) { update(1,0,n-1,pos,c); }
    u64 get_hash(int l, int r) { return query(1,0,n-1,l,r).h; }
};
 
 
void prep(){
    
}
 
ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 
 
void solve(){ // https://cses.fi/problemset/task/2420
    
    // testcases ?
 
    // cleanup ?
 
    cin >> n >> q;
    string s; cin >> s;
    string srev = s; reverse(all(srev));
    SegHash h(s), hrev(srev);
 
    while(q--)  {
        int t; cin >> t;
        if(t==1) {
            int id; char c; cin >> id  >> c;
            h.update(id - 1, c);
            hrev.update(n- id, c);
        } else {
            int i1, i2; cin >> i1 >> i2;
            h.get_hash(i1 - 1, i2 - 1) == hrev.get_hash(n - i2, n - i1) ? yes : no;
        }
    }
    
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}