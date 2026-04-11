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
    string s; cin >> s;
    set<string> ss;
    int ans = 0;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        for(int j  = i; j < n; j++) {
            string cur = s.substr(i, j-i+1);
            if(ss.count(cur)) continue;
            ss.insert(cur);
            ans += j-i+1;
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