    #include<bits/stdc++.h>
    using namespace std;

    #define ll long long
    #define vll vector<long long>
    #define pll pair<long long, long long>
    #define F first 
    #define S second
    #define all(v) v.begin(),v.end()
    #define For(i,a,b) for(long long i=(a); i<=(b); ++i)
    #define Size(x) (ll)((x).size())
    #define gp " "

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


    
    const int mod = 998244353;
    const int N = 3e5 + 5;

ll fact[N];

ll Pow(ll b, ll e){
    ll ans = 1;
    while(e > 0){
        if(e & 1) ans = (ans * b) % mod;
        b = (b * b) % mod;
        e /= 2;
    }
    return ans;
}

ll modinv(ll x){ return Pow(x, mod - 2); }

ll divide(ll x, ll y){ return (x * modinv(y)) % mod; }

ll ncr(ll n, ll r){
    ll ans = fact[n];
    ll den = (fact[r] * fact[n-r]) % mod;
    ans = divide(ans, den);
    return ans;
}

void prep(){
    fact[0] = 1;
    For(i, 1, N-1) fact[i] = (fact[i-1] * i) % mod;
}

ll n,m,k,q;
ll a[N];


void solve(){  
    

}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}