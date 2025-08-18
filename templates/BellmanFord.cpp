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
    const int N = 1e6 + 5;

ll n,m,k,q;
ll ar[N];
vector<pair<pll, ll>> edges;

// bellman-Ford
void solve(){  
    cin >> n >> m;
    ll a, b, c;
    For(i, 1, m){
        cin >> a >> b >> c;
        edges.push_back({{a, b}, c});
    }
    ll ans[n+1]; 
    ans[1] = 0;
    For(i, 2, n) ans[i] = 1e18;

    For(i, 1, n){ // n-1 times + 1 time
        for(auto x : edges){ // go over all edges

            // if you want a [REACHABLE FROM 1] neg. cycle
            // add ans[x.F.F]!=1e18 in the if statement below

            if(ans[x.F.F] + x.S < ans[x.F.S]){ // relaxation

                ans[x.F.S] = ans[x.F.S], ans[x.F.F] + x.S;

                if(i == n){ // negative cycle detected if reduction occurs in nth turn
                    cout << -1 << endl; return;
                }
            }
        }
    }


    cout << ans[n] << endl;

}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}