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

struct M {
    vector<vll> mat;
    M () {
        mat.resize(n, vll(n));
    }

    void fill(){
        For(i, 0, n-1){
            For(j, 0, n-1){
                cin >> mat[i][j];
            }
        }
    }

    M operator* (M mat2){
        M ans;
        For(i, 0, n-1){
            For(j, 0, n-1){
                ll cur = 0;
                For(k, 0, n-1){
                    cur += (mat[i][k] * mat2.mat[k][j]) % mod;
                    cur %= mod;
                }
                ans.mat[i][j] = cur;
            }
        }
        return ans;
    }
};

void solve(){
    cin >> n >> x;
    M m;
    m.fill();

    M ans;
    For(i, 0, n-1){
        ans.mat[i][i] = 1; // identity matrix
    }

    while(x){
        if(x & 1) ans = ans * m;
        m = m * m;
        x /= 2;
    }

    ll res = 0;
    For(i, 0, n-1){
        For(j, 0, n-1){
            res += ans.mat[i][j];
            res %= mod;
        }
    }

    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    //int t; cin >> t; while(t--)
    solve();
}
