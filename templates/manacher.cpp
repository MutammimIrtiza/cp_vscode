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
const int N = 1000006; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////
 
vector<ar<int,2>> manacher(string s) {  // ans[i][0] = radius of longest palindrome of even length centered at i
                                        // ans[i][1] = ... odd length ...
                                        // 0 - based !!!
                                        // for abcba, odd radius of c is 3
                                        // for abba, even radius of second b is 2, of first b is 0
                                        // i.e. for a even lengthed palindrome, in the central pair, the second one is center
    auto manacher_odd = [](string s) {
        int n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);
        int l = 0, r = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = min(r - i, p[l + (r - i)]);
            while(s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
    };
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto v = manacher_odd(t + "#");
    int n = sz(s);
    vector<ar<int,2>> ans(n);
    L(i,0,n-1) ans[i][0] = (v[2*i]-1)/2, ans[i][1] = v[2*i+1]/2;
    return ans;
}
 
void prep(){
    
}
 
ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 
 
void solve(){
    
    // testcases ?
 
    // cleanup ?
 
    string s; cin >> s; 
    vector<ar<int,2>> radi = manacher(s);
    ll pos, par, best = 0;
    L(i,0,sz(s)-1) {
        L(j,0,1) {
            ll cur = j&1 ? 2*(radi[i][j]-1) + 1 : 2 * radi[i][j];
            if(cur>best) pos = i, par = j, best = cur;
        }
    }
    deb(radi);
    string ans;
    if(par&1) ans = s.substr(pos-radi[pos][1]+1, best);
    else ans = s.substr(pos-radi[pos][0], best);
    cout << ans << nl;
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}