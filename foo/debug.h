#pragma once

template<class T> 
auto pr(T x) -> decltype(cerr<<x, void()) {cerr<<x;}
void pr(string s) {cerr<<s;}

template<class A, class B>
void pr(pair<A,B> p){
  cerr << "{";  pr(p.F);  cerr << ", ";  pr(p.S);  cerr << "}";
}

template<class... A>
void pr(tuple<A...> t){
    cerr << "(";
    bool f = true;
    apply([&](auto... x){
        ((cerr << (f ? (f=false, "") : ", "), pr(x)), ...);
    }, t);
    cerr << ")";
}

template<class T>
auto pr(T v) -> decltype(v.begin(), void()){
    cerr << "[";   
    bool f = 1;
    for(auto x : v){
        if(!f) cerr << ", ";
        f = false;
        pr(x);
    }
    cerr << "]";
}

template<class... T>
void d_b(const T&... x){
    ((pr(x), cerr << ", "), ...);
    cerr << '\n';
}

#define deb(...) cerr << __LINE__ << "| " << #__VA_ARGS__ << \
 " : ", d_b(__VA_ARGS__)
