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
        int n; string a, b;
        cin >> n >> a >> b;
        int ans = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                string x = a.substr(0, i+1) + b.substr(j, n-j);
                string y = a.substr(j, n-j) + b.substr(0, i+1);
                ans += (x==y);
            }
        }

        cout << ans << endl;
    }
}
