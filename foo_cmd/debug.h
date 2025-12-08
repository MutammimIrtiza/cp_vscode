#include<bits/stdc++.h>
using namespace std;

#define deb(...) debug(#__VA_ARGS__, __LINE__, __VA_ARGS__)

template<class T> 
auto _p(const T& x) -> decltype(cout << x, void()) { cout << x; }

inline void _p(const string& s){ cout << '"' << s << '"'; }

template<class T, class U> 
void _p(const pair<T,U>& p){ cout << "{"; _p(p.first); cout << ","; _p(p.second); cout << "}"; }

template<class C> 
auto _p(const C& c) -> decltype(c.begin(), c.end(), void()){
    cout << "{";
    for(auto it = c.begin(); it != c.end(); ){ _p(*it); if(++it != c.end()) cout << ", "; }
    cout << "}";
}

template<class... A>
void debug(const char* s, int l, A... a){
    cout << l << "| ";
    string t(s); stringstream ss(t); string x; vector<string> names;
    while(getline(ss, x, ',')) { names.push_back(x); }
    size_t idx = 0;
    auto print_arg = [&](const auto& arg) {
        cout << (idx ? "   " : "") << names[idx] << ": "; _p(arg); idx++;
    };
    (print_arg(a), ...); cout << "\n";
}