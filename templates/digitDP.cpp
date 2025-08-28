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
ll a[N];
ll dp[19][11][2][2];
 
bool is_valid() {
    return 1; 
    // in this problem,by construction, reaching the end => 1 valid number formed
    // if problem was even sum, we would do return sum % 2 == 0;
}

ll cnt(string s, ll pos, ll prev, bool started, bool tight){
    if(pos == Size(s)) return is_valid(); // number of such numbers = 1
 
    if(dp[pos][prev][started][tight] != -1) return dp[pos][prev][started][tight];
 
    ll ans = 0;
    ll digMax = tight ? s[pos]-'0' : 9;
    for(ll dig = 0; dig <= digMax; dig++){
        // ***
        if(started and dig == prev) continue; // no repitition. 0s can repeat if number hasnt started
 
        bool startedNext = started ? 1 : dig != 0; // started || (dig != 0)
        bool tightNext = tight ?  (dig == digMax) : 0; // tight && (dig == digMax)
 
        ans += cnt(s, pos+1, dig, startedNext, tightNext);
    }
    return dp[pos][prev][started][tight] = ans;
 
}
 
// digit dp generally done top-down with recursion + memoization, instead of iterative (bottom up)
void solve(){  

    // Your task is to count the number of integers between a and b where no two adjacent digits are the same.

    ll n1, n2; cin >> n1 >> n2;
 
    // 10 is a dummy value for prev.
 
    string s1 = to_string(n1 - 1); 
    memset(dp, -1, sizeof(dp));
    ll ans1; if(n1-1 < 0) ans1 = 0;
    else ans1 = cnt(s1, 0, 10, 0, 1);
 
    string s2 = to_string(n2);
    memset(dp, -1, sizeof(dp));
    ll ans2 = cnt(s2, 0, 10, 0, 1);
 
    cout << ans2 - ans1 << endl;
 
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}