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
const int N = 100005; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

ll n,m,k,q;
ll a[N];
vector<array<ll, 2>> gr[N];
vll d1(N);

void dijkstra(ll start, vll &d, vector<array<ll, 2>> gr[N]){

    For(i, 1, n) d[i] = inf;
    d[start] = 0;   

    bool vis[n+1] = {0};

    // pq better than set coz smallest element extraction O(1) vs O(logN)
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq; // {dist, node} .smaller first
    pq.push({0LL, start});

    while(!pq.empty()){
        auto [dist, node] = pq.top();
        pq.pop();

        // this works !!!
        if(vis[node]) continue;
        vis[node] = 1;

        for(auto [nextNode, weight] : gr[node]){

            if(weight + dist < d[nextNode]){
                d[nextNode] = weight + dist;
                pq.push({d[nextNode], nextNode});
            }
        }
    }
}


void solve(){  
    cin >> n >> m;
    ll a, b, c; 
    For(i, 1 , m){
        cin >> a >> b >> c;
        gr[a].push_back({b, c}); // {node, weight}
    }
    dijkstra(1, d1, gr);
    For(i, 1, n) cout << d1[i] << gp;
    cout << endl;
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}