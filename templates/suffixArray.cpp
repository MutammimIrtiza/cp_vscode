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

vll build_suffix_array(const string &ins) {
    string s = ins + '#';
    int n = s.size();
    vll p(n), c(n); // position, class
    vector<pair<char, int>> a(n);
    L(i, 0, n-1) a[i] = {s[i], i};
    sort(all(a));
    L(i, 0, n-1) p[i] = a[i].S;
    c[p[0]] = 0;
    L(i, 1, n-1) c[p[i]] = a[i].F == a[i-1].F ? c[p[i-1]] : c[p[i-1]] + 1;
    
    auto count_sort = [&](){
        vector<int> cnt(n);
        for(auto x : c) {
            cnt[x]++;
        }
        vll p_new(n);
        vector<int> pos(n);
        L(i, 1, n-1) pos[i] = pos[i-1] + cnt[i-1]; // starting position of buckets
        for(auto x : p) {
            int i = c[x];
            p_new[pos[i]++] = x;
        }
        p = p_new;
    };

    int k = 0;
    while((1<<k) < n) {
        // k -> k+1
        L(i, 0, n-1) p[i] = (p[i] - (1<<k) + n) % n;
        count_sort();
        vll c_new(n);
        c_new[p[0]] = 0;
        L(i, 1, n-1) {
            pll now = {c[p[i]], c[(p[i] + (1<<k)) %n]};
            pll prev = {c[p[i-1]], c[(p[i-1] + (1<<k)) %n]};
            c_new[p[i]] = now == prev ? c_new[p[i-1]] : c_new[p[i-1]] + 1;
        }
        c = c_new;
        k++;
    }
    return p;
}

vll build_lcp(const string &ins, vll &sa) {
    string s = ins + '#';
    int n = s.size();
    vll lcp(n-1), rnk(n);
    L(i, 0, n-1) rnk[sa[i]] = i;
    int k = 0;
    L(i, 0, n-2) {
        ll j = sa[rnk[i] - 1];
        while(i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
        lcp[rnk[i] - 1] = k;
        if(k) k--;
    }
    return lcp;
}

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), c(N); 

void solve(){ // number of distinct substrings of s. TLE :(
    
    // testcases ?

    // cleanup ?

    string s; cin >> s;
    cin >> q;
    while(q--) {
        ll l, r; cin >> l >> r; l--, r--;
        string now = s.substr(l, r-l+1);
        vll sa = build_suffix_array(now);
        vll lcp = build_lcp(now, sa); // 9
        ll nn = r-l+1; // 9 10
        ll ans = nn*(nn+1)/2;
        for(auto x : lcp) ans -= x;
        cout << ans << nl;
    }

}   

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}