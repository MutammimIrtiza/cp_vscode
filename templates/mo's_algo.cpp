// بِسْمِ ٱللّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ //

#include<bits/stdc++.h>
using namespace std;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// using namespace __gnu_pbds;
// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

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

#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 1e9 + 7;
const int N = 1000005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}


int block_size;
struct Query {
    int l, r, idx;
    Query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
    bool operator<(const Query &other) const { // magic
        int block_own = l / block_size;
        int block_other = other.l / block_size;
        if (block_own != block_other)
            return block_own < block_other;
        return (block_own & 1) ? (r > other.r) : (r < other.r);
    }
};

ll n, m, x, y, z, q, kk, u, v, w;
vll a(N), b(N);
vector<Query> queries; // dont forget to clear
vll ans(N);
ll curr_answer = 0; // dont forget to clear
vll freq(N); // wont work if a[i] upto 1e9
            // dont forget to clear if there are multiple test cases


void add(int index) {
    ll val = a[index];
    // handle case where a[i] is upto 1e9

    freq[val]++;
    // TODO: Update curr_answer depending on the problem

    
}

void remove(int index) {
    ll val = a[index];
    // handle case where a[i] is upto 1e9

    freq[val]--;
    // TODO: Update curr_answer depending on the problem

    
}

void mo_algo() { // Turn multiple subarray queries into a sliding window problem.
    block_size = sqrt(n); 
    sort(queries.begin(), queries.end()); // magic. pointer moves are now at most sqrt(n)

    int curr_l = 1, curr_r = 0; // change if 0 based
                                // move to global if needed            
    for (const auto &query : queries) {
        int l = query.l;
        int r = query.r;

        while (curr_l > l) add(--curr_l);
        while (curr_r < r) add(++curr_r);
        while (curr_l < l) remove(curr_l++);
        while (curr_r > r) remove(curr_r--);

        ans[query.idx] = curr_answer;
    }
}


void solve() {
    cin >> n >> q;
    L(i, 1, n) {
        cin >> a[i];
    }
    int l, r;
    L(i, 1, q) {    
        cin >> l >> r;
        queries.push_back(Query(l, r, i));
    }
    mo_algo();
    L(i, 1, q) {cout << ans[i] << endl;}
// dont forget to cleanup !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}