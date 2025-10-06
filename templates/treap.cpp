// بِسْمِ ٱللّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ //

#include<bits/stdc++.h>
using namespace std;

// Extra functionality :
// *st.find_by_order(index) = value at index
// st.order_of_key(value) = number of elements strictly less than value

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#define ll long long
#define lld long double
#define vll vector<long long>
#define pll pair<long long, long long>
#define vvll vector<vll>
#define vvvll vector<vvll>
#define ar array
#define F first
#define S second

#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define For(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define L(i, a, b) for(long long i = (a); i <= (b); ++(i))
#define R(i, a, b) for(long long i = (a); i >= (b); --(i))
#define sz(x) (ll)(x.size())
#define gp " "
#define nl "\n"
#define yes cout<<"YES"<<nl
#define no cout<<"NO"<<nl

#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define getBit(x, i) (((x) >> (i)) & 1)
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)


#ifdef LOCAL
#include "debug.h"
#else
#define deb(...) (void)0
#endif

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int dx4[4] = {0, 0, 1, -1}, dy4[4] = {1, -1, 0, 0};
const lld pi = 2*acos(0.0);
const int mod = 1e9 + 7;
const int N =500005; ///////////////////////////////////////
const int rt = 450;
const ll inf = 1e15; /////////////////////////////////////////////

ll n, m, x, y, z, q, k, u, v, w;
vll a(N), b(N); 

// Indexing is 0-based
struct Treap {
    struct Node {
        int val, sum, size, prior, lazy;
        Node *l = nullptr, *r = nullptr;
        Node(int v) : val(v), sum(v), size(1), prior(rand()), lazy(0) {}
    };

    Node* root = nullptr;

    int _sz(Node* t) { return t ? t->size : 0; }
    int sum(Node* t) { return t ? t->sum : 0; }

    void push(Node* t) {
        if (!t || t->lazy == 0) return;
        t->val += t->lazy;
        t->sum += t->lazy * _sz(t);
        if (t->l) t->l->lazy += t->lazy;
        if (t->r) t->r->lazy += t->lazy;
        t->lazy = 0;
    }

    void upd(Node* t) {
        if (!t) return;
        push(t->l); push(t->r);
        t->size = 1 + _sz(t->l) + _sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
    }

    void split(Node* t, int k, Node*& l, Node*& r) { // l holds first k indices [0...k-1] 
                                                     // r holds rem. indices [k...n-1]
        if (!t) { l = r = nullptr; return; }
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

    Node* merge(Node* l, Node* r) {
        push(l); push(r);
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) { 
            l->r = merge(l->r, r); upd(l); return l;
        } else { 
            r->l = merge(l, r->l); upd(r); return r;
        }
    }

    // Range add [l, r]
    void range_add(int l, int r, int v) {
        Node *t1, *t2, *t3; // [0...l-1], [l...r], [r+1...n-1] 
        split(root, r+1, t2, t3);
        split(t2, l, t1, t2);
        if (t2) t2->lazy += v;
        root = merge(merge(t1, t2), t3);
    }

    // Range sum [l, r]
    int range_sum(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, r+1, t2, t3);
        split(t2, l, t1, t2);
        int ans = sum(t2);
        root = merge(merge(t1, t2), t3);
        return ans;
    }

    // inserts val at index pos [0 based], shifting the rest right
    void insert(int pos, int val) {
        Node *t1, *t2;
        split(root, pos, t1, t2);
        root = merge(merge(t1, new Node(val)), t2);
    }

    void erase(int pos) {
        Node *t1, *t2, *t3; // [0...pos-1], [pos...pos], [pos+1...n-1]
        split(root, pos + 1, t2, t3);
        split(t2, pos, t1, t2);
        clear(t2);
        root = merge(t1, t3);
    }

    void clear(Node* t) {
        if (!t) return;
        clear(t->l);
        clear(t->r);
        delete t;
    }

    ~Treap() {
        clear(root);
        root = nullptr;
    }

    // add functions if necessary

    void f(ll a, ll b) {
        if(a >= b) return;

        // both cases can be generalized to ...|block|...|block|...
        // any of the ... can be null, no problem

        Node *t1, *t2, *t3, *t4, *t5;
        int blocksize = min(n-b, b-a);
        split(root, b+blocksize, t4, t5);
        split(t4, b, t3, t4);
        split(t3, a+blocksize, t2, t3);
        split(t2, a, t1, t2);
        Node *res = merge(t1, t4);
        res = merge(res, t3);
        res = merge(res, t2);
        res = merge(res, t5);
        root = res;
    }

    void print() {
        print(root); cout << nl;
    }
    void print(Node* root) { // simply in-order
        if(!root) return;
        print(root->l);
        cout << root->val << gp;
        print(root->r);
    }

};


void prep(){
    
}

void solve(){ // https://codeforces.com/gym/102787/problem/A
    
    // testcases ?

    // cleanup ?

    cin >> n;
    Treap tr;
    L(i, 1, n) tr.insert(i-1, i);

    ll a, b;
    L(i, 1, n) {
        cin >> a >> b; a--, b--;
        tr.f(a, b);
    }
    tr.print();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    prep();
    // int t; cin >> t; while(t--)
    solve();
}