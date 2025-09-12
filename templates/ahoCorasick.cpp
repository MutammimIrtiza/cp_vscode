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
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

struct Aho {
    static const int K = 26; // alphabet size
    struct Vertex {
        int next[K];      // trie edges
        int link;         // suffix link
        int term_link;    // terminal link (output link)
        bool output;      // true if this node is end of some pattern
        vector<int> ids;  // pattern ids ending here
        int len;

        Vertex() {
            fill(begin(next), end(next), -1);
            link = -1;
            term_link = -1;
            output = false;
            len = 0;
        }
    };

    vector<Vertex> t = { Vertex() }; // root = state 0

    // Insert a pattern into the trie
    void add_string(const string &s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) {
                t[v].next[c] = t.size();
                t.emplace_back();
            }
            v = t[v].next[c];
        }
        t[v].output = true;
        t[v].ids.push_back(id);
    }

    // Build suffix and terminal links
    void build_automaton() {
        queue<int> q;
        t[0].link = 0;

        for (int c = 0; c < K; c++) {
            int u = t[0].next[c];
            if (u != -1) {
                t[u].link = 0;
                q.push(u); t[u].len = 1;
            } else {
                t[0].next[c] = 0; // missing edge from root loops to root
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int c = 0; c < K; c++) {
                int u = t[v].next[c];
                if (u != -1) {
                    // compute suffix link
                    t[u].link = t[t[v].link].next[c];
                    
                    t[u].len = t[v].len + 1;
                    q.push(u);
                } else {
                    t[v].next[c] = t[t[v].link].next[c];
                }
            }

            // compute terminal link
            if (t[t[v].link].output)
                t[v].term_link = t[v].link;
            else
                t[v].term_link = t[t[v].link].term_link;
        }
    }
};


void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?

    string s; cin >> s; n = sz(s); s = ' ' + s;
    cin >> k;
    Aho aho;
    string p;
    L(i, 1, k) {
        cin >> p; aho.add_string(p, i);
    }
    aho.build_automaton();
    vll dp(n+1); dp[0] = 1;
    ll cur = 0;
    L(i, 1, n) {
        cur = aho.t[cur].next[s[i] - 'a'];
        ll tem = cur;
        if(!aho.t[tem].output) tem = aho.t[tem].term_link;
        while(tem != -1) {
            dp[i] += dp[i - aho.t[tem].len]; dp[i] %= mod;
            tem = tem = aho.t[tem].term_link;
        }
    }
    cout << dp[n] << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}