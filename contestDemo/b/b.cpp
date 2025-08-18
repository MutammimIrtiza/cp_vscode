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
#define nl "\n"
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
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?

    

}

int main() {
    auto begin = std::chrono::high_resolution_clock::now();

    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    prep();
    int t; cin >> t; while(t--)
    solve();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // cout << "\nTime measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}