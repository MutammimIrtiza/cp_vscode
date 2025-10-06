#include<bits/stdc++.h>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

// Indexing is 0-based.
struct Treap {
    struct Node {
        int val, sum, sz, prior;
        int mn, mx;
        int lazy_add = 0;
        Node *l = nullptr, *r = nullptr;
        Node(int v) : val(v), sum(v), sz(1), prior(rnd()), mn(v), mx(v) {}
    };
    Node* root = nullptr;

    int sz(Node* t){ return t ? t->sz : 0; }
    int sum(Node* t){ return t ? t->sum : 0; }

    void push(Node* t){
        if(!t) return;
        if(t->lazy_add){
            t->val += t->lazy_add;
            t->sum += t->lazy_add * t->sz;
            t->mn += t->lazy_add;
            t->mx += t->lazy_add;
            if(t->l) t->l->lazy_add += t->lazy_add;
            if(t->r) t->r->lazy_add += t->lazy_add;
            t->lazy_add = 0;
        }
    }

    void upd(Node* t){
        if(!t) return;
        push(t->l); push(t->r);
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
        t->mn = t->mx = t->val;
        if(t->l){ t->mn = min(t->mn, t->l->mn); t->mx = max(t->mx, t->l->mx); }
        if(t->r){ t->mn = min(t->mn, t->r->mn); t->mx = max(t->mx, t->r->mx); }
    }

    void split(Node* t,int k,Node*& l,Node*& r){
        if(!t){ l=r=nullptr; return; }
        push(t);
        if(sz(t->l)<k){ split(t->r,k-sz(t->l)-1,t->r,r); l=t; }
        else{ split(t->l,k,l,t->l); r=t; }
        upd(t);
    }

    Node* merge(Node* l,Node* r){
        push(l); push(r);
        if(!l||!r) return l?l:r;
        if(l->prior>r->prior){ l->r=merge(l->r,r); upd(l); return l; }
        else{ r->l=merge(l,r->l); upd(r); return r; }
    }

    void insert(int pos,int v){
        Node *t1,*t2;
        split(root,pos,t1,t2);
        root = merge(merge(t1,new Node(v)),t2);
    }

    void range_add(int l,int r,int v){
        Node *t1,*t2,*t3;
        split(root,r+1,t2,t3); split(t2,l,t1,t2);
        if(t2) t2->lazy_add += v;
        root = merge(merge(t1,t2),t3);
    }

    int range_sum(int l,int r){
        Node *t1,*t2,*t3;
        split(root,r+1,t2,t3); split(t2,l,t1,t2);
        int ans = t2 ? t2->sum : 0;
        root = merge(merge(t1,t2),t3);
        return ans;
    }

    int range_min(int l,int r){
        Node *t1,*t2,*t3;
        split(root,r+1,t2,t3); split(t2,l,t1,t2);
        int ans = t2 ? t2->mn : INT_MAX;
        root = merge(merge(t1,t2),t3);
        return ans;
    }

    int range_max(int l,int r){
        Node *t1,*t2,*t3;
        split(root,r+1,t2,t3); split(t2,l,t1,t2);
        int ans = t2 ? t2->mx : INT_MIN;
        root = merge(merge(t1,t2),t3);
        return ans;
    }
};