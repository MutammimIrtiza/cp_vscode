// Extended Euclidean Algorithm
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Solve ax + by = c
// general solution : x + k*b/g, y - k*a/g
bool solve_diophantine(long long a, long long b, long long c, 
                       long long &x, long long &y, long long &g) {
    g = ext_gcd(abs(a), abs(b), x, y);
    if (c % g != 0) return false; // no solution
    x *= c / g;
    y *= c / g;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}
