//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"

typedef long long ll;


ll offset = 0;
ll get(ll x) {
    printf("? %lld\n", x - offset);
    fflush(stdout);
    ll res;
    scanf("%lld", &res);
    return res;
}

ll m;
ll solve(ll x) {
    ll l  = 0, r = m;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        ll res = get(x - mid);
        if (res < x) {
            r = mid - 1;
        } else if (res > x) {
            l = mid + 1;
        } else {
            return x - mid;
        }
    }

    if (get(x - l) == x) {
        return x - l - offset;
    } else {
        return -1;
    }
}

signed main() {
    ll x;
    scanf("%lld%lld", &x, &m);
    offset = get(1) - 1;
    ll res = solve(x) %
    printf("! %lld\n", solve(x));
    fflush(stdout);
}