#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl "\n"
#define gp " "

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline ll rnd(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << 1 << endl;

    int n = rnd(2, 5);
    int m = min(rnd(2, 5), ((ll)n*(n-1)/2));
    cout << n << " " << m <<  endl;
    set<pair<int, int>> tree;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        u = rnd(1, n);
        do{
            v = rnd(1, n);
        } while(u == v || tree.count({u, v}) || tree.count({v, u}));
        tree.insert({u, v});
        cout << u << " " << v << nl;
    }


}