// #include <bits/stdc++.h>
// using namespace std;

// #define ll long long
// #define nl "\n"
// #define gp " "

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// inline ll rnd(ll l, ll r) {
//     return uniform_int_distribution<ll>(l, r)(rng);

// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     // cout << 1 << endl;

// //     int n = rnd(2, 5);
// //     int k = (rnd(1, n));
// //     int r = rnd(1, n);
// //     int l = rnd(1, r);
// //     cout << n << " " << k << " " << l << " " << r << "" << endl;

// //     for(int i = 1; i <= n; ++i) {
// //         int u, v;
// //         u = rnd(1, 2*n);
// //         // do{
// //         //     v = rnd(1, n);
// //         // } while(u == v || tree.count({u, v}) || tree.count({v, u}));
// //         // tree.insert({u, v});
// //         cout << u << gp;
// //     }
// // cout << nl;

//     // int n = rnd(1, 10);
//     // string a, b;
//     // for(int i = 1; i <= n; i++) {
//     //     a.push_back('a' + rnd(0, 2));
//     //     b.push_back('a' + rnd(0, 2));
//     // }
//     // cout << n << endl;
//     // cout << a << endl << b << endl;

//     cout << 5 << " " << 8 << endl;
//     for(int i = 0; i < 5; i++)  {
//         cout << rnd(0, 6) << gp << rnd(1, 20) << endl;
//     }
//     for(int i = 0; i < 8; i++) {
//         cout << i << endl;
//     }


// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 8, q = 15;
    cout << n << " " << q << "\n";

    // Arya
    ll s1 = 3, v1 = 10;   // v multiple of 5, short flight
    cout << s1 << " " << v1 << "\n";

    vector<pair<ll,ll>> others = {
        {3,10},   // identical
        {3,11},   // same s, slightly faster
        {3,9},    // same s, slightly slower
        {4,10},   // same v, later
        {2,10},   // same v, earlier
        {3,5},    // v exactly 5 (edge of air)
        {0,20},   // long flight, intersects
    };

    for(auto &p: others){
        cout << p.first << " " << p.second << "\n";
    }

    vector<ll> queries = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
    };

    for(ll T: queries) cout << T << "\n";
}
