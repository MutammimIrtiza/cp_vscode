struct minMaxSeg{
    struct node{
        ll mn = inf;                                            // TODO
        ll mx = -inf;                                           // TODO
        ll lazy = inf;                                          // TODO
 
        node() {}
        node(ll x) : mn(x), mx(x) {}
        void apply(int l, int r, ll y) {                        // TODO
            mn = mx = y;
            // if(l != r) lazy = y; // => applied here, but pending in children
        }
    };

    int size;
    vector<node> tree;

    minMaxSeg(vll & a) {
        ll n = sz(a) ;                           // TODO: rem -1 for 0 based
        size = 1; while(size < n) size *= 2;
        tree.assign(2 * size , node()); // 

        For(i, 0, n-1) { // leaves (input array)      // TODO: 0 to n-1 for 0 based
            tree[size + i ] = a[i];              // TODO: rem -1 for 0 based
        }
        for(ll j = size - 1; j >= 1; j--) { // tree is 1 based
            pull(j);
        }
    }

    node unite(node a, node b){                                     // TODO
        node res;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        return res;
    }
    void push(int pos, int l, int r){
        if(l == r) return;
        if (tree[pos].lazy != inf) {  
            int mid = (l + r) / 2;
            tree[2*pos].apply(l, mid, tree[pos].lazy);
            tree[2*pos+1].apply(mid+1, r, tree[pos].lazy);
            tree[pos].lazy = inf;                                   // TODO
        }
    }
    void pull(int pos){
        tree[pos] = unite(tree[pos * 2], tree[pos * 2 + 1]);
    }


    node query(int ql, int qr){
        // return query(1, 1, size, ql, qr);
        return query(1, 0, size-1, ql, qr); // pref
    }
    node query(int pos, int l, int r, int ql, int qr) {
        push(pos, l, r);
        if (l >= ql && r <= qr) { return tree[pos];}
        if (qr < l || ql > r) return node();
        int mid = (l + r) / 2;
        node res;
        if (qr <= mid) res = query(2 * pos, l, mid, ql, qr);
        else if (ql > mid) res = query(pos * 2 + 1, mid + 1, r, ql, qr);
        else res = unite(query(pos * 2, l, mid, ql, qr), 
                            query(pos * 2 + 1, mid + 1, r,  ql, qr));
        pull(pos);
        return res;
    }


    void modify(int ql, int qr, ll y) {
        // modify(1, 1, size, ql, qr, y);
        modify(1, 0, size-1, ql, qr, y); // pref
    }
    void modify(int pos, int l, int r, int ql, int qr, ll y){
        push(pos, l, r);
        if (l >= ql && r <= qr){
            tree[pos].apply(l, r, y);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) modify(2 * pos, l, mid, ql, qr, y);
        if (qr > mid) modify(2 * pos + 1, mid + 1, r, ql, qr, y);
        pull(pos);
    }
};