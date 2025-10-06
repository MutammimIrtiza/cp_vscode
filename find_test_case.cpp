// بِسْمِ ٱللّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ //

#include<bits/stdc++.h>
using namespace std;

namespace cfdebugger{
	// the test case you want to know
	const int _Errorcase=3412;
	// replace "_identity" with the first few lines of the test data 
	// this is an example
	string _identity=R"(
10000
1
0
1
1
2
00
2
10
2
01
2
11
3
000
3
100
3
010
3
110
3
001
3
101
3
011
3
111
)";
	
	stringstream _ss;
	void main(){
		string _s;
		bool _is_bad=1;
		int _ii=0;
		_identity.erase(0,1);
		_identity.pop_back();
		while(getline(cin,_s)){
			_s+='\n';
			for(const char &c:_s){
				if(_ii>=_identity.size()) break;
				if(c!=_identity[_ii]) _is_bad=0;
				_ii++;
			}
			_ss<<_s;
		}
		if(!_is_bad) return ;
		stringstream _tmp;
		_tmp.str(_ss.str());
		#define cin _tmp
		int _T; cin>>_T;
		for(int _test=1;_test<=_T;_test++){
			// input, following is an example, replace them with your input
			int n; string s; cin>>n>>s;
			
			if(_test==_Errorcase){
				// output, following is an example, replace them with your output
				cout<<n<<' '<<s<<'\n';
				
				cout<<"\nError Case End\n";
				exit(0);
			}
		}
		#undef cin
	}
}
#define cin cfdebugger::_ss
// your code below



// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
#define vvll vector<vll>
#define vvvll vector<vvll>
#define ar array
#define F first
#define S second

#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define For(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define L(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define R(i, a, b) for(long long i = (a); i >= (b); --(i))
#define sz(x) (ll)(x.size())
#define gp " "
#define nl "\n"
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl

#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define getBit(x, i) (((x) >> (i)) & 1)
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)


#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const lld pi = 2*acos(0.0);
const int mod = 1e9 + 7;
const int N = 1000006; ///////////////////////////////////////
const ll inf = 1e15; /////////////////////////////////////////////

void prep(){
    
}

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

void solve(){
    
    // testcases ?

    // cleanup ?

    cin >> n;
    string s; cin >> s; s = '1' + s + '1';
    vll dir(n+2);
    L(i, 2, n-1)  {
        if(s[i]=='0') {
            if(s[i+1]=='0' and s[i-1]=='0') continue;
            if(s[i-1]=='1' and s[i-2]=='1') {
                dir[i] = 1;
            }
            if(s[i+1]=='1' and s[i+2]=='1') {
                if(dir[i]==1) {no; return;}
                dir[i] = -1;
                if(s[i-1]=='1' and dir[i-2]==-1) {no; return;}
            }
            if(s[i-1]=='1') {
                if(dir[i-2]==1) dir[i]=-1;
                else dir[i]=1;
            }
        }
    }
    L(i, 1, n) if(dir[i]==1) if()
    yes;
}

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(NULL);
    cfdebugger::main();
    prep();
    int t; cin >> t; while(t--)
    solve();
}