/*
    I should get rid of this tendency of (essentially) giving up if the solution doesnt click in 5 mins.

    bikes can be iterated one by one.
    create a vector named bike. 
    push p[i] into the vector q[i] times.
    dp[i] = min cost to get upto bike[i] done SUCH THAT A DISCOUNT COUPON ENDS RIGHT AT i [ends => either date ends or out of rides ]
    [consider a regular ride as a discount coupon of d=1, k=1, c=r]
    THEN THE ANSWER BECOMES dp[m] !!!
    [we never take a coupon if one is active, so we only need to push to the END.]
    INSANE!!!

    now the push dp is easy.

    helpful visualization:
    the bike vector : 1 1 1 2 2 3 5 5 5 5 6 ...
    the day blocks  : |   |   | |       | ...

    [i and k[i] have same dimension]
    [bike[i] and d[j] have same dimension]
    L(i,1,m) {
        L(j,1,n) {
            I have dp[i].
            taking coupon j means pushing to dp[i + k[j]]   // NOT i+d[j]. make sure you understand the bike vector.
            BUT 
            if bike[i+k[j]] exceeds the validity (which is : bike[i+1] + d[j] -1)
            then clamp i+k[j] to the last index of bike[i+1] + d[j] -1
        }
    }

*/