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

struct mint {
    int x;
    mint() : x(0) {}
    mint(int64_t xx) : x(xx % mod) { if (x < 0) x += mod; }

    mint& operator+=(const mint& b) { x += b.x; if (x >= mod) x -= mod; return *this; }
    mint& operator-=(const mint& b) { x -= b.x; if (x < 0) x += mod; return *this; }
    mint& operator*=(const mint& b) { x = (int)((1LL * x * b.x) % mod); return *this; }
    mint& operator/=(const mint& b) { return *this *= b.inv(); } 

    mint operator-() const { return mint() - *this; }
    mint inv() const { return power(mod - 2); } // for prime mod only
    mint power(int64_t n) const {
        mint a = *this, res = 1;
        while (n) {
            if (n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    friend bool operator==(const mint& a, const mint& b) { return a.x == b.x; }
    friend bool operator!=(const mint& a, const mint& b) { return a.x != b.x; }
    friend ostream& operator<<(ostream& os, const mint& m) { return os << m.x; }

    explicit operator bool() const { return x != 0; }
};

mint power(mint a, int64_t n) {
    mint res = 1;
    while (n) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

// for each position (0 based ***) of s, what is the best match of a suffix at that position with a prefix of s
vector<int> prefixFunction(const string &s) { 
    int n = s.size();
    vector<int> pi(n);
    pi[0] = 0;
    for(int i = 1; i < n; ++i) {
        int j = pi[i-1];
        while(j > 0 and s[j] != s[i]) j = pi[j-1];
        if(s[j] == s[i]) j++;
        pi[i] = j;
    }
    return pi;
}
// if the automaton is built on string s, then :
// aut[j][ch] = if i'm scanning/constructing some string and rn the best match between prefix_of_s and suffix_of_MY_string 
// is of LENGTH j, and the next scanned/put character is ch, then what would be the best matched LENGTH
vector<vector<int>> prefixAutomaton(const string &s) {
    int m = s.size();
    vector<int> pi = prefixFunction(s);
    const int alph = 26;
    vector<vector<int>> aut(m+1, vector<int>(alph));
    for (int j = 0; j <= m; j++) {
        for (int c = 0; c < alph; c++) {
            if (j < m && s[j] == char('a' + c)) aut[j][c] = j+1;
            else if (j == 0) aut[j][c] = 0;
            else aut[j][c] = aut[pi[j-1]][c];
        }
    }
    return aut;
}


void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 
mint dp[1005][105]; // dp[i][j] = no. of strings of length i that have a suffix match of length j with prefix of s

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n;
    string s; cin >> s; L(i,0,sz(s)-1) s[i] = s[i] - 'A' + 'a'; // :)
    auto pref_aut = prefixAutomaton(s);
    ll m = sz(s);
    // the nature of automatons is : what happens if i ADD this character
    // so push dp fits in well
    mint ans;
    dp[0][0] = 1;
    L(i, 0, n) {
        L(j, 0, m) {
            // ive built some string of length i, having a suffix match of length j with prefix of s
            // in how many ways can i extend ?

            // if ive reached the full prefix, i will update ans
            // also, i will not extend this count further, coz it will build on top of this, and overcount
            if(j==m) {
                ans += dp[i][j] * power(26, n-i);
                continue;
            }
            
            // if full prefix not reached, i try extending with all chars, of course if i != n
            L(ch, 0, 25) {
                if(i!=n) dp[i+1][ pref_aut[j][ch] ] += dp[i][j];
            }
        }
    }
    L(i,0,n) L(j,0,m) deb(i,j,dp[i][j]);
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}