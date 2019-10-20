//
// Created by kirill on 20.10.2019.
//

#include <stdbool.h>
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

typedef double ld;

typedef struct pair {
    ld first, second;
    int idx;
} _pair;


#pragma GCC optimize("-Ofast")

ld eps = 1e-18;
void slow_sort(_pair *a, int size) {
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; ++j) {
            if (a[j].first > a[j + 1].first) {
                _pair tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

_pair kth_element(_pair *a, int size, int k) {
    if (size == 1) {
        return a[0];
    }
    for (int i = 0; i < size; i += 5) {
        slow_sort(a + i, (int) (min(5, size - i)));
    }
    _pair *cur = malloc(((size + 4) / 5) * sizeof(_pair));
    for (int i = 0; i < size; i += 5) {
        cur[i / 5] = a[i + min(size - i, 5) / 2];
    }
    _pair x = kth_element(cur, (size + 4) / 5, (size + 4) / 10);
    free(cur);
    _pair *less = malloc(size * sizeof(_pair));
    _pair *equal = malloc(size * sizeof(_pair));
    _pair *more = malloc(size * sizeof(_pair));
    int cnt_equal = 0, cnt_less = 0, cnt_more = 0;
    for (int i = 0; i < size; i++) {
        if (a[i].first < x.first - eps) {
            less[cnt_less++] = a[i];
        } else if (a[i].first > x.first + eps) {
            more[cnt_more++] = a[i];
        } else {
            equal[cnt_equal++] = a[i];
        }
    }
    for (int i = 0; i < cnt_less; i++) {
        a[i] = less[i];
    }
    for (int i = 0; i < cnt_equal; i++) {
        a[i + cnt_less] = equal[i];
    }
    for (int i = 0; i < cnt_more; i++) {
        a[i + cnt_equal + cnt_less] = more[i];
    }
    free(less);
    free(equal);
    free(more);
    if (k < cnt_less) {
        return kth_element(a, cnt_less, k);
    }
    if (k >= cnt_less + cnt_equal) {
        return kth_element(a + cnt_equal + cnt_less, cnt_more, k - cnt_equal - cnt_less);
    }
    return x;
}

_pair* check_check(_pair *arr, int size, ld c, int k) {
    _pair *tmp = malloc(size * sizeof(_pair));
    for (int i = 0; i < size; i++) {
        tmp[i].first = arr[i].first - arr[i].second * c;
        tmp[i].idx = i;
    }
    kth_element(tmp, size, size - k);
    return tmp;
}

bool check(_pair *arr, int size, ld c, int k) {
    _pair *tmp = check_check(arr, size, c, k);
    ld sum = 0;
    for (int i = size - k; i < size; i++) {
        sum += tmp[i].first;
    }
    free(tmp);
    return sum > -eps;
}

void sort(int *arr, int n);
signed main() {
    int n, k;
    scanf("%d%d", &n, &k);
    _pair *arr = malloc(n * sizeof(_pair));
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &arr[i].first, &arr[i].second);
    }

    ld l = -1e8, r = 1e8;
    for (int i = 0; i < 60; i++) {
        ld m = (l + r) / 2.;
        if (check(arr, n, m, k)) {
            l = m;
        } else {
            r = m;
        }
    }
    _pair *tmp = check_check(arr, n, l, k);
    int *ans = malloc(k * sizeof(int));
    for (int i = n - k; i < n; i++) {
        ans[i - n + k] = tmp[i].idx + 1;
    }
    sort(ans, k);
    for (int i = 0; i < k; i++) {
        printf("%d ", ans[i]);
    }
}

void sort(int *arr, int n) {
    if (n <= 1) return;
    sort(arr, n / 2);
    sort(arr + n / 2, n - n / 2);
    int *cur = malloc(n * sizeof(int));
    int p1 = 0, p2 = n / 2;
    while (p1 < n / 2 && p2 < n) {
        if (arr[p1] <= arr[p2]) {
            *cur = arr[p1++];
        } else {
            *cur = arr[p2++];
        }
        cur++;
    }
    while (p1 < n / 2) {
        *cur = arr[p1++];
        cur++;
    }
    while (p2 < n) {
        *cur = arr[p2++];
        cur++;
    }
    cur -= n;
    memcpy(arr, cur, sizeof(int) * n);
    free(cur);
}