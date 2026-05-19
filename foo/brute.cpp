#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define L(i, a, b) for (int i = (a); i <= (b); ++i)

// Robust division helpers
ll floor_div(ll a, ll b)
{
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return a / b;
    return (a - b + 1) / b;
}

ll ceil_div(ll a, ll b)
{
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return (a + b - 1) / b;
    return a / b;
}

void solve()
{
    int n; string s1, s2; cin >> n >> n >> s1 >> s2;
        int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if((s1.substr(0, i+1) + s2.substr(j, n-j)) == (s1.substr(j, n-j) + s2.substr(0,i+1))) ans++;
        }
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}