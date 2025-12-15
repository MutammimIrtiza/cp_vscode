    #include<bits/stdc++.h>
    using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace __gnu_pbds;
// *st.find_by_order(i) : ith largest element
// st.order_of_key(k) : number of items strictly smaller than k 

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

ll n,m,k,q;
ll a[N];

void solve(){  
    is_sorted(a+1, a+n+1);
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while(t--)
    solve();
}