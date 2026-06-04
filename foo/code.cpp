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
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, q, kk, u, v, w;
vll ar(N);
vll gr[N];

// 
void solve(){
    cin >> n >> m >> kk;
    L(i, 1, kk){
        cin >> ar[i];
    }
    L(i, 1, m){
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }

    ll mnod = inf;
    L(i, 1, kk) if(ar[i] & 1) mnod = min(mnod, ar[i]);

    ll sum = accumulate(range(ar, 1, kk), 0LL);
    ll evtar, odtar;
    if(sum & 1){
        odtar = sum;
        evtar = sum - mnod;
    }
    else{
        evtar = sum;
        odtar = sum - mnod;
    }

    vector<vll> dis(n+1, vll(2, inf));
    queue<array<ll, 2>> q; // {node, parity of entrance}
    q.push({1, 0});
    dis[1][0] = 0;
    while(sz(q)){
        auto [node, p] = q.front();
        q.pop();
        for(auto nexnode : gr[node]){
            if(dis[nexnode][!p] == inf){
                dis[nexnode][!p] = dis[node][p] + 1;
                q.push({nexnode, !p});
            }
        }
    }
    L(i, 1, n){
        if(evtar >= dis[i][0] or odtar >= dis[i][1]) cout << 1;
        else cout << 0;
    }
    cout << endl;


// dont forget to cleanup !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    L(i, 1, n){
        gr[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    int t; cin >> t; while(t--)
    solve();
}