ll FactorCnt[1000001];
void prep(){ 
    ll n = 1e6;
    for(ll i = 1; i <= n; ++i){ // i =  factor
        for(ll j = i; j <= n; j += i){ // j = multiple. 
            FactorCnt[j]++;
        }
    }
}



ll properFactorCnt[1000001];
void prep(){ 
    ll n = 1e6;
    for(ll i = 1; i <= n; ++i){ // i = (proper) factor
        for(ll j = i + i; j <= n; j += i){ // j = multiple. (starts from 2i, because j = i is not proper)
            properFactorCnt[j]++;
        }
    }
}