vll factors[N];
void prep_factors(){ 
    L(i, 1, N-1){
        for(ll j = i; j <= N-1; j += i){
            factors[j].push_back(i);
        }
    }
}