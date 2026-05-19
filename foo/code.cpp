#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const int MOD = 1'000'000'007;
static const int BASE = 5782344;


int addmod(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int mulmod(ll a, ll b) {
    return int((a * b) % MOD);
}

/*
    recall:
    # range qry of fixed value : prefix sum
    # range qry of a qry value : vectors of pos for each value + binary search first, last
    # range qry of a range of qry values : persistent seg tree
*/

/*
    for each persistent seg tree, we need to know:
    -- what do versions represent?
    -- what do leaves in a particular seg tree version represent?
    -- what do leaves store?
    -- what do inner nodes store? sum/max/min?
*/

static const ll INF = -(1LL << 60);
struct PersistentSegTree {
    struct Node {
        int l = 0, r = 0; ll mx = -INF; // change as needed
    };

    vector<Node> st;

    PersistentSegTree() {st.push_back(Node());} // 0 = null

    int update(int prev, int tl, int tr, int pos, ll val) {
        st.push_back(st[prev]); // new copy of prev's root
        int cur = (int)st.size() - 1;
        if (tl == tr) {
            st[cur].mx = val;
            return cur;
        }
        int tm = (tl + tr) >> 1; // either l/r of root changes
        if (pos <= tm) st[cur].l = update(st[prev].l, tl, tm, pos, val);
        else st[cur].r = update(st[prev].r, tm + 1, tr, pos, val);
        st[cur].mx = max(st[st[cur].l].mx, st[st[cur].r].mx);
        return cur;
    }

    // query(root[i], 0, n-1, l, r) means
    // maximum on range [l,r] in version i
    ll query(int node, int tl, int tr, int l, int r) {
        if (!node || r < tl || tr < l) return -INF;
        if (l <= tl && tr <= r) return st[node].mx;

        int tm = (tl + tr) >> 1;
        return max( 
            query(st[node].l, tl, tm, l, r),
            query(st[node].r, tm + 1, tr, l, r)
        );
    }

    // CUSTOM:

    // Collect all ids in this version whose stored v >= need.
    // We traverse left first, so ids are collected in increasing order.
    // Problem statement bounds total leaves accessed, so its not costly
    void collect(int node, int tl, int tr, ll v_need, vector<int>& out) const {
        if (node == 0 || st[node].mx < v_need) return;
        if (tl == tr) {
            out.push_back(tl);
            return;
        }
        int tm = (tl + tr) >> 1;
        collect(st[node].l, tl, tm, v_need, out);
        collect(st[node].r, tm + 1, tr, v_need, out);
    }
};

struct Point {
    ll u, v;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
        ym = y of gun
        xm = x of gun

        |y-ym| <= (x-xm)/2
        -(x-xm)/2 <= y-ym <= (x-xm)/2
        -(x-xm) <= 2(y-ym) <= (x-xm)

        split:
        2y-2ym <= x-xm
        2ym-2y <= x-xm

        rearrange:
        x-2y >= xm-2ym
        x+2y >= xm+2ym

        transformation:
        x' = x-2y
        y' = x+2y

        Then condition becomes simply:
        u >= um
        v >= vm

        i.e. a triangular query is transformed into a rectangular query. much easier.

        now to answer queries:
        create persistent seg tree with versions for each u (sorted)
        for the given um, bin search to find first u >= um
        go to the seg tree of that version
        here, leaves = ids, and leaf value = v of that enemy
        and, each node stores max value of v of its subtree
        so we just dfs the tree, and stop when v_node < vm
        else, continue till root and push back id into the answer vector
        finally loop to calculate the sum

        NOTE: TLE was coz leaves were not sorted by v. Fixed.
    */

    int N, q;
    cin >> N >> q;

    vector<Point> pts(N);
    for (int i = 0; i < N; i++) {
        ll x, y;
        cin >> x >> y;
        pts[i] = {x - 2LL * y, x + 2LL * y, i};
    }


    // Sort by v ascending and store [seg tree leaves are in this order, not Id order]
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.v != b.v) return a.v < b.v;
        return a.u < b.u;
    });
    vector<int> pos(N), leaf_id(N);
    for(int i = 0; i < N; ++i) {
        pos[pts[i].id] = i;
        leaf_id[i] = pts[i].id;
    }


    // Sort by u ascending [versions are in this order]
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });

    vector<ll> uvals(N);
    for (int i = 0; i < N; i++) uvals[i] = pts[i].u;

    // Persistent seg tree over ids [0..N-1]
    PersistentSegTree pst;
    vector<int> root(N + 1, 0);

    // root[i] = version containing points i..N-1 (all with u >= uvals[i])
    // root[N] = empty
    for (int i = N - 1; i >= 0; i--) {
        root[i] = pst.update(root[i + 1], 0, N - 1, pos[pts[i].id], pts[i].v);
    }


    // powers of BASE
    vector<int> pw(N + 1);
    pw[0] = 1;
    for (int i = 1; i <= N; i++) pw[i] = mulmod(pw[i - 1], BASE);

    int last = 0;


    while (q--) {
        int a, b;
        cin >> a >> b;

        ll xm = -1LL - ((last + a) % MOD);
        ll ym = (last + b) % MOD;

        ll U = xm - 2LL * ym;
        ll V = xm + 2LL * ym;

        // Find first point with u >= U
        int idx = lower_bound(uvals.begin(), uvals.end(), U) - uvals.begin();

        vector<int> leaves;
        if (idx < N) pst.collect(root[idx], 0, N - 1, V, leaves);

        vector<int> ids; 
        for(int leaf : leaves) ids.push_back(leaf_id[leaf]);
        sort(ids.begin(), ids.end());

        int ans = 0;
        for (int j = 0; j < (int)ids.size(); j++) {
            ans = addmod(ans, mulmod(ids[j] + 1, pw[j]));
        }

        cout << ans << '\n';
        last = ans;
    }

    return 0;
}