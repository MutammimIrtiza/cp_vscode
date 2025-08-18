    #include<bits/stdc++.h>
    using namespace std;

    #define ll long long
    #define lld long double
    #define vll vector<long long>
    #define pll pair<long long, long long>
    #define F first 
    #define S second
    #define all(v) v.begin(),v.end() // cannot use parentheses
    #define For(i, a, b) for(long long i = (a); i <= (b); ++(i))
    #define Size(x) (ll)((x).size())
    #define gp " "
    #define setbit(x, i) (x | (1LL<<i))
    #define resetbit(x, i) (x & (~(1LL << i)))

    //#define DEBUG
    
    #ifdef DEBUG
    #define debug(n) cout<<__LINE__<<" "<<#n<<" "<<n<<endl;
    #define debugc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<el<<" ";}cout<<']'<<endl;
    #define debugcc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<'{'<<" "<<el.F<<','<<el.S<<" "<<'}'<<" ";}cout<<']'<<endl;
    #else
    #define debug(n) // single variable, string
    #define debugc(a) // vector, deque, array
    #define debugcc(a) // map, vector<pll>
    #endif


    
    const int mod = 1e9 + 7;
    const int N = 1e6 + 5;

ll n,m,k,q;
ll ar[N];
vll edges[N];
bool vis[N];
vll ans;
bool active[N];

void dfs(ll node){
    active[node] = 1;
    vis[node] = 1;

    for(ll x : edges[node]){
        if(active[x]){ // cycle detected
            cout << "IMPOSSIBLE" << endl; exit(0);
        }
        else{
            if(!vis[x]){
                dfs(x);
            }
        }
    }

    active[node] = 0;
    ans.push_back(node);
}

// topological sort
// exists only in DAGs
// can also use stack for storing
// alt : kahn's algo.  but dorkar nai.
void solve(){  
    cin >> n >> m;
    ll a, b;
    For(i, 1, m){
        cin >> a >> b;
        edges[a].push_back(b);
        // edges[b].push_back(a); // eta hobe na. shabdhan.
    }
    
    For(i, 1, n){
        if(!vis[i]) dfs(i);
    }

    reverse(all(ans));
    for(ll x : ans) cout << x << gp;
    cout << endl;
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}