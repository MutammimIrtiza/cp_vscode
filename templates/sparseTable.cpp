#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SparseTable {
    int n;
    vector<int> lg;
    vector<vector<T>> st;

    SparseTable() = default;
    SparseTable(const vector<T>& a) { build(a); }

    void build(const vector<T>& a) {
        n = (int)a.size();
        if (n==0) return;
        lg.assign(n+1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i/2] + 1;
        int K = lg[n] + 1;
        st.assign(K, vector<T>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k) {
            int len = 1 << (k-1);
            for (int i = 0; i + (1<<k) <= n; ++i)
                st[k][i] = min(st[k-1][i], st[k-1][i + len]);
        }
    }

    // query on inclusive indices [l, r], 0-indexed
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1<<k) + 1]);
    }
};



int main() {
    vector<int> a = {5,2,4,7,1,3};
    SparseTable<int> st(a);
    cout << st.query(1,4) << "\n"; // min of {2,4,7,1} -> 1
}