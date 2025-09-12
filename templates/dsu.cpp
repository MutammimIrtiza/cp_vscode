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
    vll par, sz; ll c; vll exp;

    DisjointSet(ll n){
        sz.resize(n+1, 0LL); par.resize(n+1,0LL); c = n; exp.resize(n+1, 0LL);

        For(i, 0, n) {
            par[i] = i, sz[i] = 1;
        }
    }

    ll getSize(ll node) {
        return sz[findUlt(node)];
    }

    ll cccnt(){
        return c;
    }

    ll findUlt(ll node){ // findUPar
        if(par[node] == node) return node; // root

        ll x = findUlt(par[node]); // x = root

        // do stuff here if needed
        // passing down is not needed for node just below root, coz connection stays
        // else, connection will be gone due to path compression
        // so we push down exp[par[node]] 
        // NOT exp[x]. careful
        // also, this par[node] is never going to store anything in future, so its ok
        // bye bye par[node]. x is the new par. you have done your job and passed down :)
        if(par[node] != x)  exp[node] += exp[par[node]];
        

        par[node] = x; // path compression. remove ???

        return x;
    }

    void Union(ll u, ll v){ // finds and unites roots
        ll ulpu = findUlt(u); ll ulpv = findUlt(v);
        if(ulpu == ulpv) return;
        --c;
        if(sz[ulpu] < sz[ulpv]) swap(ulpu, ulpv);

        par[ulpv] = ulpu;
        sz[ulpu] += sz[ulpv]; 

        // do stuff here if needed
        exp[ulpv] -= exp[ulpu]; // এখনই করে রাখতেসি, কারণ পরে উপর থেকে নিতেইইই হবে 

        
    }

    // extra functions

    void addExp(ll node, ll val){
        exp[findUlt(node)] += val;
    }

    ll getExp(ll node){
        findUlt(node);
        return exp[node] + (par[node] == node ? 0 : exp[par[node]]);
        // exp[ulpu] + extra stored
        // exp[ulpv] - exp[ulpu]
        // sum = exp[ulpv] + extra stored

        // for long chain, it works like induction and all extras are passed down :)
    }
};


ll n,m,k,q;
ll a[N];

void solve(){ // edu 1 C
    cin >> n >> q;

    DisjointSet ds(n);
    while(q--){
        string typ; cin >> typ;
        if(typ == "add"){
            ll node, val; cin >> node >> val; ds.addExp(node, val);
        }
        else if(typ == "join"){
            ll u, v; cin >> u >> v; ds.Union(u,v);
        }
        else{
            ll x; cin >> x;
            cout << ds.getExp(x) << endl;
        }
    }
}
                        
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //int t; cin >> t; while(t--)
    solve();
}