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
    int n, q;
    if (!(cin >> n >> q))
        return;
    vector<ll> v(n + 1), t(n + 1);
    L(i, 1, n)
        cin >> t[i] >> v[i];

    // Each event is {time, delta_change}
    vector<pair<ll, int>> events;
    auto add_range = [&](ll l, ll r)
    {
        if (l <= r)
        {
            events.push_back({l, 1});
            events.push_back({r + 1, -1});
        }
    };

    auto sub_range = [&](ll l, ll r)
    {
        if (l <= r)
        {
            events.push_back({l, -1});
            events.push_back({r + 1, 1});
        }
    };

    // Projectile i is strictly in the air for T such that:
    // H_i(T) > 0  => v(T-t) - 5(T-t)^2 > 0 => T-t < v/5
    // For integer T, max(T-t) = floor((v-1)/5)
    auto get_flight = [&](int i, ll &s, ll &e)
    {
        if (v[i] <= 5)
        {
            s = 1, e = 0;
            return;
        }
        s = t[i] + 1;
        e = t[i] + (v[i] - 1) / 5;
    };

    ll S1, E1;
    get_flight(1, S1, E1);

    L(i, 2, n)
    {
        ll Si, Ei;
        get_flight(i, Si, Ei);
        if (Si > Ei)
            continue;

        // Assume i wins for its entire flight
        add_range(Si, Ei);

        // If 1 is never in the air, i wins the whole range (already added)
        if (S1 > E1)
            continue;

        // Find overlapping flight time [OL, OR]
        ll OL = max(Si, S1);
        ll OR = min(Ei, E1);
        if (OL > OR)
            continue;

        // Inside the overlap, we must subtract where H_i(T) <= H_1(T)
        // H_i - H_1 = AT + B
        ll A = (v[i] + 10 * t[i]) - (v[1] + 10 * t[1]);
        ll B = -(v[i] * t[i] + 5 * t[i] * t[i]) + (v[1] * t[1] + 5 * t[1] * t[1]);

        // Subtract range where AT + B <= 0
        if (A == 0)
        {
            if (B <= 0)
                sub_range(OL, OR);
        }
        else if (A > 0)
        {
            // T <= -B/A
            ll boundary = floor_div(-B, A);
            sub_range(OL, min(OR, boundary));
        }
        else
        { // A < 0
            // T >= -B/A
            ll boundary = ceil_div(-B, A);
            sub_range(max(OL, boundary), OR);
        }
    }

    // Process events
    sort(all(events));
    vector<pair<ll, int>> compressed;
    int current_sum = 0;
    for (int i = 0; i < sz(events);)
    {
        ll cur_t = events[i].first;
        while (i < sz(events) && events[i].first == cur_t)
        {
            current_sum += events[i].second;
            i++;
        }
        compressed.push_back({cur_t, current_sum});
    }

    // Answer queries
    while (q--)
    {
        ll x;
        cin >> x;
        auto it = upper_bound(all(compressed), make_pair(x, (int)2e9));
        if (it == compressed.begin())
        {
            cout << 0 << "\n";
        }
        else
        {
            it--;
            cout << it->second << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}