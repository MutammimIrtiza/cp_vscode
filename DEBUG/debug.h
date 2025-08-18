#pragma once
#include <bits/stdc++.h>
using namespace std;

// ─── Print Helpers ───────────────────────────────────────────── //
void __print() { cout << '\n'; }

template<typename T>
void __print(const T& x) { cout << x; }

template<typename T, typename U>
void __print(const pair<T, U>& p) {
    cout << "("; __print(p.first); cout << ", "; __print(p.second); cout << ")";
}

template<typename T, size_t N>
void __print(const array<T, N>& a) {
    cout << "[";
    for (size_t i = 0; i < N; ++i) {
        if (i) cout << ", ";
        __print(a[i]);
    }
    cout << "]";
}

template<typename T>
void __print(const vector<T>& v) {
    cout << "["; 
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin()) cout << ", ";
        __print(*it);
    }
    cout << "]";
}

template<typename T>
void __print(const deque<T>& v) {
    cout << "["; 
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it != v.begin()) cout << ", ";
        __print(*it);
    }
    cout << "]";
}

template<typename T>
void __print(const set<T>& s) {
    cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) cout << ", ";
        __print(*it);
    }
    cout << "}";
}

template<typename T>
void __print(const multiset<T>& s) {
    cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) cout << ", ";
        __print(*it);
    }
    cout << "}";
}

template<typename T, typename U>
void __print(const map<T, U>& m) {
    cout << "{";
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it != m.begin()) cout << ", ";
        __print(it->first);
        cout << ": ";
        __print(it->second);
    }
    cout << "}";
}

// ─── New Variadic Printer ────────────────────────────────────── //
// Splits the string `names` at commas, trims spaces, then prints
// each name/value pair separated by two spaces.
template<typename... Args>
void dbg_print(const char* names, Args&&... args) {
    // split names at commas
    vector<string> varnames;
    string s(names), cur;
    for (char c: s) {
        if (c == ',') {
            if (!cur.empty()) varnames.push_back(cur);
            cur.clear();
        } else if (!(cur.empty() && isspace(c))) {
            cur += c;
        }
    }
    if (!cur.empty()) varnames.push_back(cur);

    // print each pair
    bool first = true;
    int idx = 0;
    // fold expression over the pack:
    ((cout << (first ? "" : "   ")
           << varnames[idx++] << ":",
      __print(args),
      first = false),
     ...);

    cout << '\n';
}

// ─── Debug Macro ─────────────────────────────────────────────── //
#ifdef LOCAL
  #define deb(...) \
    cout << __LINE__ << "| ", dbg_print(#__VA_ARGS__, __VA_ARGS__)
#else
  #define deb(...) (void)0
#endif
