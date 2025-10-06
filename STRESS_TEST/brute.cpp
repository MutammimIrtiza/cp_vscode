#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define isSet(x, i) ((x>>i)&1)

const int MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t; 
    while(t--) {
        ll n, k, l, r;
        cin >> n >> k >> l >> r;
        vector<int> v(n+1);
        for(int i = 1; i <=n; i++) {
            cin >> v[i];
        }   

        ll ans =0;
        for(int i = 1; i <= n; i++) {
            for(int j = i; j <= n; j++) {
                set<ll> s;
                for(int kk = i; kk <= j; kk++) s.insert(v[kk]);
                ll d = j-i+1;
                if(s.size()==k and d>=l and d<=r) ans++;
            }
        }
        cout << ans << endl;
    }
}
