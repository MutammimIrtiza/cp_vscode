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

    #define DEBUG
    
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
    const int N = 505;

ll n,m,k,q;
ll ar[N];
// vector<pll> edges[N]; // not needed
ll ans[N][N];

void solve(){  
    cin >> n >> m >> q;
    
    For(i, 1 , n){
        For(j, 1, n){
            ans[i][j] = i==j? 0 : 1e18;
        }
    } 


    // initialization.... self: 0, given: given, others: inf
    ll a, b, c;
    For(i, 1, m){
        cin >> a >> b >> c;
        ans[a][b] = min(ans[a][b], c); // min necessary
        ans[b][a] = min(ans[a][b], c); // min necessary
    }


    For(k, 1, n){ // possible intermediate nodes
        For(i, 1, n){
            For(j, 1, n){
                ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
            }
        }
    }
    

    while(q--){
        cin >> a >> b;
        cout << (ans[a][b] == 1e18 ? -1 : ans[a][b]) << endl;
    }
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}