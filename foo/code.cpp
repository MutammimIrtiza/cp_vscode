#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#define int long long
#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
#define vvll vector<vll>
#define vi vector<int>
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
#define extract(m, x) { auto it = (m).find(x); if (it != (m).end()) (m).erase(it); } // set, multiset, map
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
#define msb(x) ((x) ? (63 - __builtin_clzll((unsigned long long)(x))) : -1)
#define lsb(x) ((x) ? (__builtin_ctzll((unsigned long long)(x))) : -1)


#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 1e9 + 7;
// const int N = ; ///////////////////////////////////////
const ll inf = 1e18; /////////////////////////////////////////////

// struct Node {
//     Node *left = nullptr, *right = nullptr;  ll sum = 0;
//     ~Node() {delete left; delete right;}
// };
// // Builds a segment tree on [l, r)
// // Returns a pointer to the constructed tree.
// Node *build(int l, int r) {
//     Node *p = new Node();
//     if (r - l == 1) return p;
//     int m = (l + r) / 2;
//     p->left = build(l, m);
//     p->right = build(m, r);
//     return p;
// }
// // Changes value in position k to x in tree p.
// // Returns a pointer to the new tree.
// Node *change(Node *p, int l, int r, int k, int x) {
//     Node *n = new Node(*p);
//     if (r - l == 1) { n->sum = x; }
//     else {
//         int m = (l + r) / 2;
//         if (k < m) { n->left = change(p->left, l, m, k, x); }
//         else { n->right = change(p->right, m, r, k, x); }
//         n->sum = n->left->sum + n->right->sum;
//     } return n;
// }
// // Returns the sum of values in range [ql, qr).
// ll query(Node *p, int l, int r, int ql, int qr) {
//     if (qr <= l || r <= ql) return 0;
//     if (ql <= l && r <= qr) return p->sum;
//     int m = (l + r) / 2;
//     return query(p->left, l, m, ql, qr) + 
//             query(p->right, m, r, ql, qr);
// }

// #include <vector>
// #include <set>
// #include <cstdint> // for int64_t, assuming ll is int64_t



struct Node {
    Node *left = nullptr, *right = nullptr;
    ll sum = 0;
};

struct PerSegTree {
    std::set<Node*> allocated_nodes;
    std::vector<Node*> roots;
    int n;
    PerSegTree(int n) : n(n) { roots.push_back(build(0, n)); }
    ~PerSegTree() {
        for (auto ptr : allocated_nodes) delete ptr;
    }
private:
    Node* build(int l, int r) {
        Node* p = new Node();  allocated_nodes.insert(p);
        if (r - l == 1) return p;
        int m = (l + r) / 2;
        p->left = build(l, m);  p->right = build(m, r);
        return p;
    }
    Node* change(Node* p, int l, int r, int k, int x) {
        Node* n = new Node(*p);  allocated_nodes.insert(n);
        if (r - l == 1) { n->sum = x; }
        else {
            int m = (l + r) / 2;
            if (k < m) n->left = change(p->left, l, m, k, x);
            else n->right = change(p->right, m, r, k, x);
            n->sum = n->left->sum + n->right->sum;
        }
        return n;
    }
    ll query(Node* p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return p->sum;
        int m = (l + r) / 2;
        return query(p->left, l, m, ql, qr) +
               query(p->right, m, r, ql, qr);
    }
public:
    // // Creates a new version by changing position k to x.
    // Returns the new version index.
    int update(int version, int k, int x) {
        Node* new_root = change(roots[version], 0, n, k, x);
        roots.push_back(new_root);
        return roots.size() - 1;
    }
    // Queries the sum in [ql, qr) for the given version.
    ll query(int version, int ql, int qr) {
        return query(roots[version], 0, n, ql, qr);
    }
};

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;

void solve(int tcase){
    
    // testcases ?

    // cleanup ?

    /*
        if i fix a position
        and bin search on available cows to find the least one that can sit here
        i just need O(1) or O(log) way of verifying if the position is ok for the cow
    */

    cin >> n >> k;
    vector<ll> a(n+1); L(i,1,n) {cin >> a[i];}

    vector<pll> b(n+1); L(i,1,n) {b[i] = {a[i], -i};}
    sort(range(b, 1, n));
    vll ans(n+1);
    // map<ll, ll> pos; L(i,1,n) pos[b[i].S] = i;
    
    vll d(n+1);
    ll s = 0;
    L(i,1,n){
        d[i] = a[i] - s;
        s += a[i];
    }

    map<ll, ll> compd; int id = 0;
    L(i,1,n) {
        if(d[i] <= 0) continue;
        if(!compd.count(d[i])) compd[d[i]] = id++;
        // cout << d[i ] << nl;
    }
    // cout << "id: " << id << nl;

    PerSegTree prefd(id);

    
    L(i,1,n) {
        // cout << "hi " << i << nl;
        if(d[i] <= 0) {
            prefd.roots.push_back(prefd.roots.back()); continue;
        }
        d[i] = compd[d[i]];
        ll prev = prefd.query(i-1, d[i], d[i]+1);
        // cout << d[i] << gp << prev << nl;
        prefd.update(i-1, d[i], prev+1);
    }

    // cout << "Prefd: " << nl;
    // L(i,0,n) {
    //     cout << i << "[" << gp;
    //     L(j,0,id-1) {
    //         cout << query(prefd[i], 0, id, j, j+1) << gp;
    //     }
    //     cout << gp << "]" << nl;
    // }

    vll pref(n+1); L(i,1,n) pref[i] = pref[i-1] + a[i];

    L(pos, 1, n) {
        ll lo = 1, hi = n;
        ll x = -1;
        while(lo <= hi) {
            ll mid = (lo+hi)/2;
            auto [_, p] = b[mid]; p = -p;
            if(pos==4) {
                cout << _ << gp << p << nl;
            }
            if(p <= pos) {
                int c = 0;
                ll lefts = pref[pos] - a[p];
                c += lefts >= a[p];
                ll pore = - prefd.query(pos,  0, id) + prefd.query(n,  0, id); 
                c += pore;
                if(c <= k) x = mid, hi = mid-1;
                else lo = mid + 1;       
                if(pos == 4 and _==1) {
                    cout << "174" << nl;
                    cout << lefts << gp << pore << gp << c << nl;
                    cout << prefd.query(p, 0, id) << gp <<  prefd.query(n,  0, id) << nl;
                }        
            } else {
                int c = 0;
                ll lefts = pref[pos-1];
                c += lefts >= a[p];
                ll pore = -prefd.query(p, 0, id) + prefd.query(n, 0, id); 
                if(compd.upper_bound(a[p]) != compd.end()) {
                    ll md = (*compd.upper_bound(a[p])).S;
                    pore += -prefd.query(pos-1, md, id) + prefd.query(p-1, md, id); 
                }
                c += pore;
                if(c <= k) x = mid, hi = mid-1;
                else lo = mid + 1; 
                if(pos == 4 and _==1) {
                    cout << "174" << nl;
                    cout << lefts << gp << pore << gp << c << nl;
                    cout << prefd.query(pos, 0, id) << gp <<  prefd.query(n, 0, id) << nl;
                }       
            }
            if(pos==4)
            cout << "lo: " << lo << gp << "hi: " << hi << nl;
        }
        if(x != -1) ans[x]++;
        cout << "x: " << gp << x << nl;
    }
    L(i,1,n) ans[i] += ans[i-1];

    vll res(n+1); L(i,1,n) res[-b[i].S] = ans[i];
    L(i,1,n) cout << res[i] << gp;
    cout << nl;





    vvvll dp(n+1, vvll(n+1, vll(2, -1)));

    L(i,1,n) deb(dp[i]);

}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int tcase = 1;
    int t; cin >> t; for(; tcase <= t; ++tcase)
    solve(tcase);
}