// بِسْمِ ٱللّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ //

#include<bits/stdc++.h>
using namespace std;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// using namespace __gnu_pbds
// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
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

#define DEBUG

#ifdef DEBUG
#define debug(n) cout<<__LINE__<<" "<<#n<<" "<<n<<endl;
#define debugc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<el<<" ";}cout<<']'<<endl;
#define debugcc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<'{'<<" "<<el.F<<','<<el.S<<" "<<'}'<<" ";}cout<<']'<<endl;
#else
#define debug(n)
#define debugc(a)
#define debugcc(a)
#endif

const int mod = 1e9 + 7;
const int N = 200005; ///////////////////////////////////////
const ll inf = 1e18; /////////////////////////////////////////////

ll n,m,k,q;
ll a[N];

// use the 0 based one for prefix sums

ll mx(ll a, ll b) {return a > b ? a : b;} // identity = -inf
ll mn(ll a, ll b) {return a < b ? a : b;} // identity = inf
ll sum(ll a, ll b) {return a + b;}        // identity = 0
ll Gcd(ll a, ll b) {return __gcd(a, b);}  // identity = 0
struct segtree{
    ll size;
    vll tree;
    function<ll(ll, ll)> func;  
    ll identity;                
    // take more vectors if multiple values need to be stored at each node


    segtree(vll& a, function<ll(ll, ll)> func, ll identity){
        this->func = func;
        this->identity = identity;
        ll n = sz(a) - 1; // a has 1 extra element
        
        size = 1; while(size < n) size *= 2;
        tree.assign(2 * size , identity);

        For(i, 1, n) {      // leaves (input array)
            tree[size + i - 1] = a[i]; 
        }
        for(ll j = size - 1; j >= 1; j--) { // tree is 1 based
            tree[j] = func(tree[2 * j], tree[2 * j + 1]);
        }
    }


    ll query(ll query_left, ll query_right){
        return query(1, 1, size, query_left, query_right);
    }
    // a node does not know what range it represents (of original array, 1 to size)
    ll query(ll node, ll node_left, ll node_right, ll query_left, ll query_right){     
        if(node_right < query_left || node_left > query_right) return identity;

        if(node_left >= query_left && node_right <= query_right) return tree[node];

        ll left_child_right_idx = (node_right + node_left) / 2;
        return func(query(2 * node , node_left, left_child_right_idx, query_left, query_right), 
            query(2 * node + 1, left_child_right_idx  + 1, node_right, query_left, query_right));
    }


    void update(ll arIdx, ll new_val){
        ll node = arIdx + size - 1;
        tree[node] = new_val;

        for(ll i = node / 2; i >= 1; i /= 2) {
            tree[i] = func(tree[2 * i], tree[2 * i + 1]);
        }
    }
};


void solve(){  
    cin >> n >> q; 
    vll a(n+1); // 1 based. leaves have 1 based indexing for original array.
                // leaves have indices 'size' to '2*size-1' for tree array
                // original array index i => tree array index 'size + i - 1'
    For(i, 1, n) cin >> a[i];


    segtree st(a, sum, 0);

    while(q--){
        int typ; cin >> typ;

        if(typ == 1){
            ll node, new_val; cin >> node >> new_val; 
            st.update(node, new_val);
        }

        else{
            ll ql, qr;
            cin >> ql >> qr; 
            cout << st.query(ql, qr) << endl;
        }
    }
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}