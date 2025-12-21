// spf (smallest prime factor) sieve
vector<int> spf(10000005);
void prep(){ // modified sieve
    L(i, 2, 10000000) {
        if(spf[i] == 0) {
            spf[i] = i;
            for(ll j = i * i; j <= 10000000; j += i) {
                if(spf[j] == 0) spf[j] = i;    }}}}
// prime factorize [upto 1e7. if you need 1e9, use loop upto sqrt]
vector<pll> prime_factorize(ll x) {
    vector<pll> ans;
    while(x!=1) {
        ll cur = spf[x];  ll cnt = 0;
        while(x%cur==0) cnt++, x/=cur;
        ans.push_back({cur, cnt});   }
    return ans;   }