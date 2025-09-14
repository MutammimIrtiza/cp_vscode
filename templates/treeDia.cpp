void dfs(ll node, vvll &gr, vll &vis, vll &dis, ll d) {
    vis[node] = 1;
    dis[node] = d;
    for(ll ch : gr[node]) {
        if(vis[ch]) continue;
        dfs(ch, gr, vis, dis, d+1);
    }
}
ll get_dia(vvll &gr) {
    vll dis(n+1);
    vll vis(n+1);
    dfs(rnd()%n+1, gr, vis, dis, 0);
    ll end1 = max_element(all(dis)) - dis.begin();
    L(i, 1, n) dis[i] = 0, vis[i] = 0;
    dfs(end1, gr, vis, dis, 0);
    return *max_element(all(dis));
}