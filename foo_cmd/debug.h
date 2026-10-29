#include<bits/stdc++.h>
using namespace std;

#define deb(...) debug(#__VA_ARGS__, __LINE__, __VA_ARGS__)

template<class T> 
auto pr(T x) -> decltype(cerr<<x, void()) {cerr<<x;}
void pr(string s) {cerr << '"' << s << '"';}

template<class T, size_t N>
void pr(array<T, N> a) {cerr << "{"; for(size_t i=0; i<N; i++) 
  {pr(a[i]);  if(i+1 < N) cerr << ", ";  }   cerr << "}"; }

template<class T, class U> 
void pr(pair<T,U> x) {cerr << "{";   pr(x.first); 
    cerr << ",";   pr(x.second);   cerr << "}"; }

template<class T> 
auto pr(T v) -> decltype(v.begin(), v.end(), void()){
 cerr << "["  ; for(auto it = v.begin(); it != v.end(); )
 { pr(*it);  if(++it != v.end()) cerr << ", "  ; } cerr << "]";}

#define eb emplace_back
template<class... A>
void debug(const char* s, int l, A... a){
    cerr << l << "| ";   vector<string> names;   int i = 0;
for(stringstream ss(s);   getline(ss,  names.eb(),  ','  );  ){};
    ( (cerr << "  " << names[i] << ": ",  pr(a),  i++),  ...);
    cerr << "\n"; }
