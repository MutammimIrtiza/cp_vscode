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
const int rt = 450;
const ll inf = 1e15; /////////////////////////////////////////////

struct BitTrie {
    struct Node {
        int child[2];   
        int cnt;        // how many numbers pass through this node. trie[0] = total numbers inserted in trie
        Node() { child[0] = child[1] = -1; cnt = 0; }
    };

    vector<Node> trie;
    int BITS;  

    BitTrie(int maxBits = 30) {  // 30 for numbers up to 1e9
        BITS = maxBits;
        trie.push_back(Node()); // root
    }

    void insert(int x) {
        int node = 0;
        trie[node].cnt++;
        for (int b = BITS; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (trie[node].child[bit] == -1) {
                trie[node].child[bit] = trie.size();
                trie.push_back(Node());
            }
            node = trie[node].child[bit];
            trie[node].cnt++;
        }
    }

    void erase(int x) {
        int node = 0;
        trie[node].cnt--;
        for (int b = BITS; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int nxt = trie[node].child[bit];
            node = nxt;
            trie[node].cnt--;
        }
    }

    // add functions

    ll max_xor(ll x) { // find y from this trie that maximizes x ^ y, return x ^ y
        if(trie[0].cnt == 0) return 0; // empty trie. 

        ll cur = 0; ll y = 0;
        R(bit, BITS, 0) {
            int nextbit = getBit(x, bit); // at root, nextbit = 30
            if(trie[cur].child[!nextbit] != -1 and trie[ trie[cur].child[!nextbit] ].cnt) {
                cur = trie[cur].child[!nextbit];
                if(!nextbit) y = setbit(y, bit);
            } else { // has to exist, since tire is not empty
                cur = trie[cur].child[nextbit];
                if(nextbit) y = setbit(y, bit);
            }
        }
        return x ^ y;
    }

};

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 
vector<ar<ll, 2>> gr[N];

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n >> q;
    L(i, 1, n-1) {
        cin >> u >> v >> w;
        gr[u].push_back({v, w});
        gr[v].push_back({u, w});
    }
    vector<BitTrie> trie(2);
    vll rx(n+1), depth(n+1);
    function<void(ll, ll, ll, ll)> dfs = [&](ll node, ll par, ll dep, ll Xor) {
        trie[dep%2].insert(Xor);
        rx[node] = Xor, depth[node] = dep;
        for(auto [ch, w] : gr[node]) {
            if(ch == par) continue;
            dfs(ch, node, dep+1, Xor^w);
        }
    };
    dfs(1, 0, 0, 0);
    ll oddxor = 0;
    while(q--) {
        char ty; cin >> ty;
        if(ty == '^') {
            cin >> x; oddxor ^= x;
        } else {
            cin >> u >> x;
            trie[depth[u]%2].erase(rx[u]);
            ll ans0 = 0, ans1 = 0;
            if(depth[u] & 1) {
                ans0 = trie[0].max_xor(rx[u]^x^oddxor);
                ans1 = trie[1].max_xor(rx[u]^x);
            } else {
                ans0 = trie[0].max_xor(rx[u]^x);
                ans1 = trie[1].max_xor(rx[u]^x^oddxor);
            }
            cout << max(ans0, ans1) << gp;
            trie[depth[u]%2].insert(rx[u]);
        }   
    }
    cout << nl;
    L(i, 1, n) {
        gr[i].clear();
    }

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}