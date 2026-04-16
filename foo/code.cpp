#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(x) = no. of elements strictly less than x

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, \
 rb_tree_tag,tree_order_statistics_node_update>

#define int long long
#define ll long long
#define lld long double
#define vi vector<int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define vvll vector<vll>
#define vvvll vector<vvll>
#define ar array
#define F first
#define S second

#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define rep(i, a, b) for(long long i = (a); i < (b); ++(i))
#define L(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define R(i, a, b) for(long long i = (a); i >= (b); --(i))
#define sz(x) (ll)(x.size())
#define extract(m, x) \
 { auto it = (m).find(x); if (it != (m).end()) (m).erase(it); }
#define gp " "
#define nl "\n"
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl

#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)
#define msb(x) (ll)((x) ? (63 - __builtin_clzll((ll)(x))) : -1)
#define lsb(x) (ll)((x) ? (__builtin_ctzll((ll)(x))) : -1)

#ifdef LOCAL
template<class T> 
auto pr(T x) -> decltype(cerr<<x, void()) {cerr<<x;}
void pr(string s) {cerr << '"' << s << '"';}

template<class A, class B>
void pr(pair<A,B> p){
    cerr << "{";   pr(p.F);   cerr << ", ";
    pr(p.S);   cerr << "}";
}

template<class... A>
void pr(tuple<A...> t){
    cerr << "(";
    bool f = true;
    apply([&](auto... x){
        ((cerr << (f ? (f=false, "") : ", "), pr(x)), ...);
    }, t);
    cerr << ")";
}

template<class T>
auto pr(T v) -> decltype(v.begin(), void()){
    cerr << "[";   
    bool f = 1;
    for(auto x : v){
        if(!f) cerr << ", ";
        f = false;
        pr(x);
    }
    cerr << "]";
}

void d_b(const char* s) {} 

template<class T, class... U>
void d_b(const char* s, T t, U... u) {
    while (*s == ',' || *s == ' ') s++;
    const char* c = strchr(s, ',');
    int len = c ? c - s : strlen(s);
    
    cerr.write(s, len) << " :"; 
    pr(t); 
    
    if (sizeof...(u)) { cerr << "    ";  d_b(c, u...); }
    else { cerr << endl ; }
}

#define deb(...) \
    cerr << __LINE__ << "| ", d_b(#__VA_ARGS__, __VA_ARGS__)

#else
#define deb(...)
#endif

mt19937_64 \
rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 998244353;
// const int N = ; 
const ll inf = 2e18; 

struct Node {
    vll freq = vll(41); // vll freq(41) is not allowed
    int cnt=0;
    static Node merge(Node &a, Node &b) {
        Node ans;
        L(i, 0, 40) {
            ans.freq[i] = a.freq[i] + b.freq[i];
            ans.cnt += (ans.freq[i] > 0);
        } 
        return ans;
    }
    Node () {}
    Node (int x) {
        freq[x] = 1;
    }
};

using T = Node;
struct Seg {
    int n, m=1;
    vector<T> t;
    const T unit = Node();   // identity element

    Seg(int _n): n(_n) {
        while(m<n) m<<=1;
        t.assign(2*m, unit);
    }
    T f(T a, T b) { return T::merge(a, b); } // operation

    void upd(int p, T v) {
        for(t[p+=m]=v;  p>1;  p>>=1)
            t[p>>1] = f(t[p&~1], t[p|1]);// parent, lef, right
    }
    T qry(int l, int r) {   // [l, r)
        T L=unit, R=unit;
        for(l+=m, r+=m;  l<r;  l>>=1, r>>=1) {
            if(l&1) L = f(L, t[l++]);
            if(r&1) R = f(t[--r], R);
        }
        return f(L,R);
    }
};

void prep(){

}

void solve(int tcase){
    int n, q; cin >> n >> q;
    Seg seg(n);
    L(i, 0, n-1) {
        int x; cin >> x; seg.upd(i, Node(x));
    }
    while(q--) {
        int typ; cin >> typ;
        if(typ == 1) {
            int l, r; cin >> l >> r; l--, r--;
            cout << seg.qry(l, r+1).cnt << nl;
        } else {
            int p, x; cin >> p >> x; p--;
            seg.upd(p, Node(x));
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t = 1;
    // cin >> t;
    L(i, 1, t) solve(i);
}