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
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

struct Trie {
    static const int ALPHABET = 26;
    static const char BASE = 'a';
    struct Node {
        int next[ALPHABET];
        int ends_here_cnt;
        int count; // passes this node

        Node() {
            fill(next, next + ALPHABET, -1);
            ends_here_cnt = 0;
            count = 0;
        }
    };

    vector<Node> nodes;

    Trie() {
        nodes.emplace_back(); // root node
    }

    void insert(const string &s) {
        int cur = 0;
        for (char ch : s) {
            int c = ch - BASE;
            if (nodes[cur].next[c] == -1) {
                nodes[cur].next[c] = nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].next[c];
            nodes[cur].count++;
        }
        nodes[cur].ends_here_cnt++;
    }

    bool erase(const string &s) {
        if (!search(s)) return false;
        
        int cur = 0;
        for (char ch : s) {
            int c = ch - BASE;
            cur = nodes[cur].next[c];
            nodes[cur].count--;  
        }
        nodes[cur].ends_here_cnt--;
        return true;
    }

    bool search(const string &s) const {
        int cur = 0;
        for (char ch : s) {
            int c = ch - BASE;
            if (nodes[cur].next[c] == -1 || nodes[nodes[cur].next[c]].count == 0) return false;
            cur = nodes[cur].next[c];
        }
        return nodes[cur].ends_here_cnt > 0;
    }

    bool starts_with(const string &prefix) const {
        int cur = 0;
        for (char ch : prefix) {
            int c = ch - BASE;
            if (nodes[cur].next[c] == -1 || nodes[nodes[cur].next[c]].count == 0) return false;
            cur = nodes[cur].next[c];
        }
        return true;
    }

    int count_prefix(const string &prefix) const {
        int cur = 0;
        for (char ch : prefix) {
            int c = ch - BASE;
            if (nodes[cur].next[c] == -1 || nodes[nodes[cur].next[c]].count == 0) return 0;
            cur = nodes[cur].next[c];
        }
        return nodes[cur].count;
    }

    // add more methods if needed. eg: https://codeforces.com/problemset/problem/1902/E
    ll fun(const string &s) const {
        int cur = 0;
        int ans = 0;
        for (char ch : s) {
            int c = ch - BASE;
            if (nodes[cur].next[c] == -1 || nodes[nodes[cur].next[c]].count == 0) break;
            cur = nodes[cur].next[c];
            ans += nodes[cur].count;
        }
        return ans;
    }

};

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N);

void solve(){
    cin >> n;
    vector<string> v(n+1); string s;
    Trie trie;
    ll tot = 0;
    L(i, 1, n){
        cin >> s;
        v[i] = s;
        reverse(all(s));
        trie.insert(s);
        tot += s.size();
    }
    ll ans = 2*n*tot; 
    L(i, 1, n) {
        ans -= 2 * trie.fun(v[i]);
    }
    cout << ans << endl;
// dont forget to cleanup !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}