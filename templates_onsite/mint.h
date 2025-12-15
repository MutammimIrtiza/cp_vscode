const int MOD=1'000'000'007; const int N=2000005;
struct mint{
 int x; mint():x(0){}
 mint(int64_t xx):x(int(xx%MOD)){ if(x<0)x+=MOD; }

 mint& operator+=(const mint& b){ x+=b.x; if(x>=MOD)x-=MOD; return *this; }
 mint& operator-=(const mint& b){ x-=b.x; if(x<0)x+=MOD; return *this; }
 mint& operator*=(const mint& b){ x=int((1LL*x*b.x)%MOD); return *this; }
 mint& operator/=(const mint& b){ return *this*=b.inv(); }

 friend mint operator+(mint a,const mint& b){ return a+=b; }
 friend mint operator-(mint a,const mint& b){ return a-=b; }
 friend mint operator*(mint a,const mint& b){ return a*=b; }
 friend mint operator/(mint a,const mint& b){ return a/=b; }
 
 mint operator-()const{ return mint()-*this; }
 mint inv()const{ return power(MOD-2); }

 mint power(int64_t n)const{
  mint a=*this, res=1;
  while(n){ if(n&1)res*=a; a*=a; n>>=1; }
  return res; 
}

 friend ostream& operator<<(ostream& os,const mint& m){ return os<<m.x; }
 explicit operator bool()const{ return x!=0; }
};

mint power(mint a,int64_t n){
 mint res=1;
 while(n){ if(n&1)res*=a; a*=a; n>>=1; }
 return res; 
}

static mint fact[N],inv_fact[N];
void prep_factorials(){
 fact[0]=1;
 for(int i=1;i<N;++i) fact[i]=fact[i-1]*i;
 inv_fact[N-1]=fact[N-1].inv();
 for(int i=N-2;i>=0;--i) inv_fact[i]=inv_fact[i+1]*(i+1);
}

mint nCr(int n,int r){
 if(r<0||r>n) return mint(0);
 return fact[n]*inv_fact[r]*inv_fact[n-r]; 
}