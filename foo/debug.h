#ifdef LOCAL

template<class T> 
auto pr(T x) -> decltype(cout<<x, void()) {cout<<x;}
void pr(string s) {cout << '"' << s << '"';}

template<class A, class B>
void pr(pair<A,B> p){
    cerr << "{";   pr(p.F);   cerr << ", ";
    pr(p.S);   cerr << "}";
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

void d(){ cerr << " ]\n"; }

template<class T,  class... U>
void d(T& t,  U&... u){
    pr(t);  if(sizeof...(u)) cerr << ", ";   
    d(u...);
}

#define deb(...) \
cerr<<__LINE__<<": ["<<#__VA_ARGS__<<"] = [" , d(__VA_ARGS__)

#else
#define deb(...)
#endif