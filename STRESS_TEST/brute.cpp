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
        int n, m;
        cin >> n >> m;
        // vector<vector<ll>> gr(n);
        vector<pair<ll, ll>> edges;
        for(int i = 0; i < m; ++i) {
            int u, v; 
            cin >> u >> v; u--; v--;    
            // gr[u].push_back(v);
            // gr[v].push_back(u);
            edges.push_back({u, v});
        }
        vector<ll> side(n);

        ll ans = 0;
        for(int mask = 0; mask < (1LL<<n); ++mask){
            vector<int> left, right;
            for(int i = 0; i < n; ++i) {
                if(isSet(mask, i)) left.push_back(i);
                else right.push_back(i);
            }
            do{
                do{
                    ll cur = 1;
                    vector<int> s(n), pos(n);
                    for(int i = 0; i < left.size(); ++i) s[left[i]] = 0, pos[left[i]] = i;
                    for(int i = 0; i < right.size(); ++i) s[right[i]] = 1, pos[right[i]] = i;
                    for (auto e : edges) {
    if (s[e.first] == s[e.second]) cur = 0; // endpoints must differ
}
for (int i = 0; i < m; i++) {
    for (int j = i+1; j < m; j++) {
        auto [a,b] = edges[i];
        auto [c,d] = edges[j];
        // normalize so a < b, c < d
        if (s[a]==1) swap(a,b);
        if (s[c]==1) swap(c,d);
        // now a and c are always on left, b and d on right
        if (pos[a] < pos[c] && pos[b] > pos[d]) cur = 0; // crossing
        if (pos[a] > pos[c] && pos[b] < pos[d]) cur = 0; // crossing
    }
}

                    ans += cur;
                }while(next_permutation(right.begin(), right.end()));

            }while(next_permutation(left.begin(), left.end()));

        }
    
        cout << ans << endl;
    }
}
