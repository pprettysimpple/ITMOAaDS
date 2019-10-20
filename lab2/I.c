//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

typedef long long ll;

typedef struct _tuple {
    int a, b, t;
    ll cnt;
} _tuple;

void sort_by_cnt(_tuple *arr, ll n);

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}



int is_ok(_tuple *arr, int size, int count, ll need_sum, ll t) {
    for (int i = 0; i < size; i++) {
        if (arr[i].a == 0) {
            if (t - (ll)arr[i].t - (ll)arr[i].b >= 0) {
                arr[i].cnt = need_sum;
            } else {
                arr[i].cnt = 0;
            }
        } else {
            arr[i].cnt = max(0, (t - (ll)arr[i].t - (ll)arr[i].b) / (ll)arr[i].a);
        }
    }
    sort_by_cnt(arr, size);
    ll sum = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i].cnt;
    }
    return sum >= need_sum;
}

signed main() {
    int m, n;
    ll p;
    scanf("%d", &m);
    _tuple *arr = malloc(m * sizeof(_tuple));
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &arr[i].a, &arr[i].b, &arr[i].t);
    }
    scanf("%d%lld", &n, &p);
    n = min(n, m);
    ll l = 0, r = 1e11;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (is_ok(arr, m, n, p, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    free(arr);
    printf("%lld", l);
}

_tuple* merge(_tuple *first, int sz1, _tuple *second, int sz2) { // returns pointer to NEW memory size(sz1+sz2) with sorted array
    int p1 = 0, p2 = 0;
    _tuple *tmp = malloc((sz1 + sz2) * sizeof(_tuple));
    while (p1 < sz1 && p2 < sz2) {
        if (first[p1].cnt >= second[p2].cnt) {
            *tmp = first[p1++];
        } else {
            *tmp = second[p2++];
        }
        tmp++;
    }
    while (p1 < sz1) {
        *tmp = first[p1++];
        tmp++;
    }
    while (p2 < sz2) {
        *tmp = second[p2++];
        tmp++;
    }
    tmp -= sz1 + sz2;
    return tmp;
}

void sort_by_cnt(_tuple *arr, ll n) {
    if (n <= 1) return;
    sort_by_cnt(arr, n / 2);
    sort_by_cnt(arr + n / 2, n - n / 2);
    _tuple *tmp = merge(arr, n / 2, arr + n / 2, n - n / 2);
    memcpy(arr, tmp, sizeof(_tuple) * n);
    free(tmp);
}