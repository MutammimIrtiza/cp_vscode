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

#define isSet(x, i)       (((x) >> (i)) & 1)
#define setbit(x, i)      ((x) | (1LL << (i)))
#define resetbit(x, i)    ((x) & (~(1LL << (i))))
#define toggleBit(x, i)   ((x) ^ (1LL << (i)))
#define clz(x)            ((sizeof(x) == 4) ? __builtin_clz(x) : __builtin_clzll(x))
#define ctz(x)            ((sizeof(x) == 4) ? __builtin_ctz(x) : __builtin_ctzll(x))
#define csb(x)            ((sizeof(x) == 4) ? __builtin_popcount(x) : __builtin_popcountll(x))
#define msb(x)            ((sizeof(x) == 4) ? 31 - clz(x) : 63 - clz(x))
#define lsb(x)            (ctz(x))



#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const lld pi = 2*acos(0.0);
const int mod = 1e9 + 7;
const int N = 2; ///////////////////////////////////////
const int rt = 450;
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

using i128 = __int128_t;
i128 read() {
    string s; cin >> s;
    bool neg = false;
    size_t i = 0;
    if (s[0] == '-') { neg = true; i = 1; }
    i128 mag = 0;
    for (; i < s.size(); ++i) {
        mag = mag * 10 + (unsigned)(s[i] - '0');
    }
    return neg ? -mag : mag;
}

void print(i128 x) {
    if (x == 0) {cout<<0<<nl;return;}
    bool neg = x < 0;
    if (neg) x = -x;

    string s;
    while (x) {
        int d = (int)(x % 10);
        s.push_back(char('0' + d));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    cout << s << nl;
}
bool cmp(i128 x, i128 y) { return x > y; } // for sorting

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n;
    i128 a = read();
    i128 b = read();
    print(a);
    print(b);
    print(a*b);
    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}