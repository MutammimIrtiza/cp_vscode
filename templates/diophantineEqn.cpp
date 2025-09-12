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

bool solve_diophantine_non_neg(long long a, long long b, long long c,
                                long long &x, long long &y, long long &g) {
    if (!solve_diophantine(a, b, c, x, y, g)) return false;
    long long dx = (b / g);
    long long dy = (a / g);
    if (x < 0) {
        long long k =  (-x + abs(dx) - 1) / abs(dx); // ceil
        if(dx < 0) k = -k;
        x += k * dx;
        y -= k * dy;
    }
    if (y < 0) {
        long long k =  (-y + abs(dy) - 1) / abs(dy); 
        if(dy < 0) k = -k;
        y += k * dy;
        x -= k * dx;
    }
    return x >= 0 and y >= 0;
}