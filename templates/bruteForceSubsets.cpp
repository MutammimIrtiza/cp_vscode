    #include<bits/stdc++.h>
    using namespace std;

    using ll = long long;
    using vll = vector<long long>;
    using pll = pair<long long, long long>;

    #define F first 
    #define S second
    #define all(v) v.begin(),v.end()
    #define For(i,a,b) for(long long i=(a); i<=(b); ++i)
    #define Size(x) (ll)((x).size())
    #define gp " "

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


    struct DisjointSet {
    vll par, sz; ll c;

    DisjointSet(ll n){
        sz.resize(n+1, 0LL); par.resize(n+1,0LL); c = n; 

        For(i, 0, n) {
            par[i] = i, sz[i] = 1;
        }
    }

    ll find_ult(ll node){ // findUPar

        // with path compression
        //return ( par[node] == node ? node : (par[node] = find_ult(par[node])) );

        // without
        //return ( par[node] == node ? node : find_ult(par[node]) );
    }

    ll getSize(ll node) {
        return sz[find_ult(node)];
    }

    ll cccnt(){
        return c;
    }

    void Union(ll u, ll v){ // finds and unites roots
        ll ulpu = find_ult(u); ll ulpv = find_ult(v);
        if(ulpu == ulpv) return;
        --c;
        if(sz[ulpu] < sz[ulpv]) swap(ulpu, ulpv);

        par[ulpv] = ulpu;
        sz[ulpu] += sz[ulpv]; 

    }

    };


    ll n,m,k,q;
    ll a[N];

    void solve(){
    cin >> n >> q;

    DisjointSet ds(n);
    while(q--){

    }
    }
                        
    int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
    }