struct Node {
    Node *left = nullptr, *right = nullptr;  ll sum = 0;
};
// Builds a segment tree on [l, r)
// Returns a pointer to the constructed tree.
Node *build(int l, int r) {
    Node *p = new Node();
    if (r - l == 1) return p;
    int m = (l + r) / 2;
    p->left = build(l, m);
    p->right = build(m, r);
    return p;
}
// Changes value in position k to x in tree p.
// Returns a pointer to the new tree.
Node *change(Node *p, int l, int r, int k, int x) {
    Node *n = new Node(*p);
    if (r - l == 1) { n->sum = x; }
    else {
        int m = (l + r) / 2;
        if (k < m) { n->left = change(p->left, l, m, k, x); }
        else { n->right = change(p->right, m, r, k, x); }
        n->sum = n->left->sum + n->right->sum;
    } return n;
}
// Returns the sum of values in range [ql, qr).
ll query(Node *p, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return p->sum;
    int m = (l + r) / 2;
    return query(p->left, l, m, ql, qr) + 
            query(p->right, m, r, ql, qr);
}



#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    Node *left = nullptr, *right = nullptr; ll sum = 0;
};
struct PerSegTree {
    std::set<Node*> allocated_nodes;
    std::vector<Node*> roots;
    int n;
    PerSegTree(int n) : n(n) { roots.push_back(build(0, n)); }
    ~PerSegTree() {
        for (auto ptr : allocated_nodes) delete ptr;
    }
private:
    Node* build(int l, int r) {
        Node* p = new Node();  allocated_nodes.insert(p);
        if (r - l == 1) return p;
        int m = (l + r) / 2;
        p->left = build(l, m);  p->right = build(m, r);
        return p;
    }
    Node* change(Node* p, int l, int r, int k, int x) {
        Node* n = new Node(*p);  allocated_nodes.insert(n);
        if (r - l == 1) { n->sum = x; }
        else {
            int m = (l + r) / 2;
            if (k < m) n->left = change(p->left, l, m, k, x);
            else n->right = change(p->right, m, r, k, x);
            n->sum = n->left->sum + n->right->sum;
        }
        return n;
    }
    ll query(Node* p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return p->sum;
        int m = (l + r) / 2;
        return query(p->left, l, m, ql, qr) +
               query(p->right, m, r, ql, qr);
    }
public:
    // Creates a new version by changing position k to x.
    // Returns the new version index.
    int update(int version, int k, int x) {
        Node* new_root = change(roots[version], 0, n, k, x);
        roots.push_back(new_root);
        return roots.size() - 1;
    }
    ll query(int version, int ql, int qr) {
        return query(roots[version], 0, n, ql, qr);
    }
};