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
    cout << "[";
    for(auto it = c.begin(); it != c.end(); ){ _p(*it); if(++it != c.end()) cout << ", "; }
    cout << "]";
}
template<class... A>
void debug(const char* s, int l, A... a){
    cout << l << "| "; vector<string> names; size_t i = 0;
    for(stringstream ss(s); getline(ss, names.emplace_back(), ','););
    ((cout << (i ? "   " : "") << names[i] << ": ", _p(a), i++), ...);
    cout << "\n";
}
