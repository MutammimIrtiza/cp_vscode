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
    const int N = 3e5 + 5;


void prep(){ 

}

ll n,m,x,q;
ll ar[N];

void solve(){
    
    ll p, k;
    cin >> p >> k;
    k = -k;
    vll ans;
    while(p != 0){
        ll r = p%k;
        p /= k;
        if(r < 0){
            r += abs(k);
            p = p+1;
        } 

        ans.push_back(r);
    }
    cout << ans.size() << endl;
    for(ll y : ans) cout << y << gp;
    cout << endl;
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    //int t; cin >> t; while(t--)
    solve();
}
