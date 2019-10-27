//
// Created by kirill on 20.10.2019.
//

#include <assert.h>
#include "stdio.h"

typedef long long ll;


ll offset = 0;
int cnt = 0;
ll m;
ll SIZE = 1000LL * 1000LL * 1000LL * 1000LL * 1000LL * 1000LL;

ll max(ll x, ll y) {
    return (x > y) ? x : y;
}
ll min(ll x, ll y) {
    return (x < y) ? x : y;
}

ll normalize(ll res, ll kek) {
    while (res < 1) res += kek;
    while (res > kek) res -= kek;
    return res;
}

ll get(ll x) {
    assert(++cnt <= 10);
    printf("? %lld\n", x);
    fflush(stdout);
    ll res;
    scanf("%lld", &res);
    if (res - offset < 1) res += (ll)1e18;
    return res - offset;
}

_Bool has_ans = 1;
ll solve(ll x) {
    ll l = max(0LL, x - SIZE), r = min(m, x - 1);
    while (l < r) {
        ll mid = l + (r - l) / 2LL;
        ll res = get(x - mid);
        if (res < x) {
            r = mid - 1;
        }
        if (res > x) {
            l = mid + 1;
        }
        if (res == x) {
            return x - mid;
        }
    }

    if (get(x - l) == x) {
        return x - l;
    } else {
        has_ans = 0;
        return -1;
    }
}

signed main() {
    ll x;
    scanf("%lld%lld", &x, &m);
    SIZE -= m;
    offset = get(1) - 1;
    x -= offset;
    x = normalize(x, 1e18);
    ll res = solve(x);
    res = normalize(res, SIZE);
    if (!has_ans) res = -1;
    printf("! %lld\n", res);
    fflush(stdout);
}