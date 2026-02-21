#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

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
    string s; cin >> s; s = ' ' + s;

    int n = s.size();

    int ans = 1;
    L(i, 1, n) {
        L(j, i, n) {
            string t = s.substr(i, j-i+1);
            int k = i;
            int cur = 0;
            while(s.substr(k, j-i+1) == t) {
                k += j-i+1;
                cur++;
                if(k > n) break;
            }
            ans = max(ans, cur);
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