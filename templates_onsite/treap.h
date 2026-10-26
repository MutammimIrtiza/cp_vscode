/**
 * Author: chatgpt
 * Date: ...
 * Source: ...
 * Description: ...
 * Time: $O(\log N)$
 * Status: ...
 */
#pragma once
// Indexing is 0-based
/**
 * Description: Implicit treap with lazy range add and reverse
 * Time: Expected O(log N) per operation
 */
#pragma once
// Indexing is 0-based

struct Treap {
    mt19937 rng{
        (uint32_t)chrono::steady_clock::now().time_since_epoch().count()
    };

    struct Node {
        int val, sum, size;
        uint32_t prior;
        int lazy = 0;
        bool rev = false;
        Node *l = nullptr, *r = nullptr;

        Node(int v, uint32_t p)
            : val(v), sum(v), size(1), prior(p) {}
    };

    Node* root = nullptr;

    int _sz(Node* t) { return t ? t->size : 0; }
    int sum(Node* t) { return t ? t->sum : 0; }

    void apply_add(Node* t, int v) {
        if (!t) return;
        t->val += v;
        t->sum += v * _sz(t);
        t->lazy += v;
    }

    void push(Node* t) {
        if (!t) return;

        if (t->lazy) {
            apply_add(t->l, t->lazy);
            apply_add(t->r, t->lazy);
            t->lazy = 0;
        }

        if (t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = false;
        }
    }

    void upd(Node* t) {
        if (!t) return;
        t->size = 1 + _sz(t->l) + _sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
    }

    // l = first k elements, r = remaining elements
    void split(Node* t, int k, Node*& l, Node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }

        push(t);

        if (_sz(t->l) < k) {
            split(t->r, k - _sz(t->l) - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }

        upd(t);
    }

    // Concatenate l followed by r
    Node* merge(Node* l, Node* r) {
        push(l);
        push(r);

        if (!l || !r) return l ? l : r;

        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            upd(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            upd(r);
            return r;
        }
    }

    // Insert val at pos; valid for 0 <= pos <= size
    void insert(int pos, int val) {
        Node *a, *b;
        split(root, pos, a, b);
        root = merge(merge(a, new Node(val, rng())), b);
    }

    // Erase element at pos; requires 0 <= pos < size
    void erase(int pos) {
        Node *a, *b, *mid, *c;
        split(root, pos, a, b);
        split(b, 1, mid, c);
        delete mid;
        root = merge(a, c);
    }

    // Add v to every element in [l, r]
    void range_add(int l, int r, int v) {
        Node *a, *b, *c;
        split(root, r + 1, b, c);
        split(b, l, a, b);

        apply_add(b, v);

        root = merge(merge(a, b), c);
    }

    // Sum of elements in [l, r]
    int range_sum(int l, int r) {
        Node *a, *b, *c;
        split(root, r + 1, b, c);
        split(b, l, a, b);

        int ans = sum(b);
        root = merge(merge(a, b), c);
        return ans;
    }

    // Reverse the subsequence [l, r]
    void range_reverse(int l, int r) {
        Node *a, *b, *c;
        split(root, r + 1, b, c);
        split(b, l, a, b);

        if (b) b->rev ^= 1;

        root = merge(merge(a, b), c);
    }

    // Return element at zero-based position pos
    int at(int pos) {
        assert(0 <= pos && pos < _sz(root));

        Node* t = root;
        while (t) {
            push(t);
            int left = _sz(t->l);

            if (pos == left) return t->val;
            if (pos < left) {
                t = t->l;
            } else {
                pos -= left + 1;
                t = t->r;
            }
        }

        return 0; // Unreachable for a valid position
    }

    // Debug: print sequence in order
    void print(Node* t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }

    void print() {
        print(root);
        cout << '\n';
    }
};