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


/*
    Paths from the start form substrings of the main string, and ALL substrings are included
    There can be multiple paths leading to a state
    The state corresponds to strings formed by those paths
    starting from the initial state, EVERY SUBSTRING can be formed.
    also, start from ANY state, follow transitions, whay you get is a substring.

    ...cab...cab...cab...
    endpos_set(string p) = set of all positions in main string where p ends, i.e. p is a suffix if we cut the string there...
    each state corresponds to one or more subsrings having same endpos_set !
    obviously, all of them are suffixes of the biggest 
    their lengths form a certain interval [x:y]
    the first few suffixes (decreasing length) of the biggest are included here
    they are together called an equivalence class
    the remaining smaller suffixes occur in more places, so they are in some other state
    
    ...cab...cab...cab...jab...jab
    if string p1 is a suffix of p2, and occurs in more positions than p2, then obviously they are in different states
    in this case, endpos_set(p2) is a subset of endpos_set(p1)
    
    suffix link of current state leads to the state having the longest suffix that is absent here
    suffix links form a tree
    minlen(state) = maxlen(link(state)) + 1

    what does a transition mean in suffix automaton?
    if there is a transition from state p to state q of character c, 
    then all the strings of p, appended by c, will be in q
    we might think maxlen[q] = maxlen[p] + 1
    but no, q might have more strings
    so, maxlen[q] >= maxlen[p] + 1
    
    if the strings of a state are suffixes of the main array, the state is a terminal state

    number of different substrings = for all states (1 to sz(st)-1), sum maxlen[i] - maxlen[link[i]]

    counting repititions for each node <after processing whole string> :
        build tree [edges in reverse direction of suffix link]
        repitition of strings in a node = sum of reps. of children
        base case : 1 for was_terminal states

    problems:
        uses total : https://vjudge.net/contest/738971#problem/E
        uses koybar and koyta : https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D
        uses next : https://cses.fi/problemset/task/2102/
*/
struct SAM {
    struct State {
        int link, maxlen;
        map<char,int> next;  
        State() { link = -1; maxlen = 0; }
    };
    vector<State> st;
    vector<vector<int>> gr; vector<ll> koybar; vector<bool> was_terminal;
    int last, sz;
    long long total; // number of unique substrings

    SAM(int n) {
        st.resize(2*n); gr.resize(2*n); koybar.resize(2*n); was_terminal.resize(2*n);
        st[0] = State();
        sz = 1;
        last = 0;
        total = 0;
    }

    void extend(char c) {
        int cur = sz++;
        st[cur].maxlen = st[last].maxlen + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) { 
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].maxlen + 1 == st[q].maxlen) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone] = st[q]; 
                st[clone].maxlen = st[p].maxlen + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur; was_terminal[last] = true;
        total += st[cur].maxlen - st[st[cur].link].maxlen;
    }

    void build_tree() {     // USE (sam.sz-1) when you need to visit all states. DO NOT USE sz(sam.st) ***
        L(i, 1, sz-1) gr[st[i].link].push_back(i);
    }
    
    void guno() {       // count repetitions in the string for each node < after building tree *** >
        int cur = last;
        L(i, 1, sz-1) koybar[i] = was_terminal[i];
        function<void(int)> dfs = [&](int node) {
            for(int ch : gr[node]) {
                dfs(ch); koybar[node] += koybar[ch];
            }
        };
        dfs(0);
    }

    ll koyta(int i) {return st[i].maxlen - st[st[i].link].maxlen;}

    // after adding the entire string, if you need terminal states, do the following:
    // start from last, go back by suffix links. all the visited states are terminal states
};


void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){ 
    
    // testcases ?

    // cleanup ?

    string s; cin >> s;
    SAM sam(sz(s));
    for(char c : s) sam.extend(c);

    sam.build_tree(); 
    sam.guno();

    ll ans = 0;
    L(i, 1, sam.sz-1) { // DO NOT USE sz(sam.st).   DO NOT FORGET -1.
        ans += sam.koyta(i) * sam.koybar[i] * (sam.koybar[i]-1) / 2; // :)
    }

    n = sz(s);
    cout << n*(n+1)/2 + ans << nl;

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}