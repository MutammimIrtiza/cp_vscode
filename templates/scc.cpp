struct tarjan_scc {
    ll n, timer, scc_count;
    vector<vector<ll>> adj;
    vector<ll> tin, low, comp_id;
    vector<bool> on_stack;
    stack<ll> st;

    tarjan_scc(ll _n = 0) {
        init(_n);
    }

    void init(ll _n) {
        n = _n;
        timer = 0;
        scc_count = 0;
        adj.assign(n, {});
        tin.assign(n, -1);
        low.assign(n, -1);
        comp_id.assign(n, -1); // id of which SCC each node belongs to
        on_stack.assign(n, false);
        while (!st.empty()) st.pop();
    }

    void add_edge(ll u, ll v) {
        adj[u].push_back(v); // directed edge
    }

    void dfs(ll u) {
        tin[u] = low[u] = timer++;
        st.push(u);
        on_stack[u] = true;

        for (ll v : adj[u]) {
            if (tin[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            // Found a new SCC
            while (true) {
                ll v = st.top();
                st.pop();
                on_stack[v] = false;
                comp_id[v] = scc_count;
                if (v == u) break;
            }
            scc_count++;
        }
    }

    void find_scc() {
        for (ll i = 0; i < n; ++i)
            if (tin[i] == -1)
                dfs(i);
    }
};
