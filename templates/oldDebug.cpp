#define DEBUG

#ifdef DEBUG
#define debug(n) cout<<__LINE__<<" "<<#n<<" "<<n<<endl;
#define debugc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<el<<" ";}cout<<']'<<endl;
#define debugcc(a) cout<<__LINE__<<" "<<#a<<" "<<'['<<" ";for(auto el:a){cout<<'{'<<" "<<el.F<<','<<el.S<<" "<<'}'<<" ";}cout<<']'<<endl;
#else
#define debug(n)
#define debugc(a)
#define debugcc(a)
#endif
