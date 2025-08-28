vll prefixFunction(string s) { // 0 based !!!
    int n = s.size();
    vll pi(n);
    pi[0] = 0;
    for(int i = 1; i < n; ++i) {
        int j = pi[i-1];
        while(j > 0 and s[j] != s[i]) {
            j = pi[j-1];
        }
        if(s[j] == s[i]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}