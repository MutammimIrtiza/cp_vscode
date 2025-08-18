vll factors[N];
void prep(){ 
    L(i, 1, 1000000){
        for(ll j = i; j <= 1000000; j += i){
            factors[j].push_back(i);
        }
    }
}