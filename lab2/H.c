//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

typedef unsigned int uint;
typedef long long int ll;

uint cur = 0, a, b;
uint next_rand() {
    cur = cur * a + b;
    return cur >> 8;
}

int* merge(int *first, int sz1, int *second, int sz2) {
    int p1 = 0, p2 = 0;
    int *tmp = malloc((sz1 + sz2) * sizeof(int));
    while (p1 < sz1 && p2 < sz2) {
        if (first[p1] <= second[p2]) {
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

ll solve(int *arr, int n) {
    if (n <= 1) return 0;
    ll result =
            solve(arr, n / 2) +
            solve(arr + n / 2, n - n / 2);

    for (int p = 0, i = n / 2; i < n; i++) {
        while (p < n / 2 && arr[p] <= arr[i]) {
            p++;
        }
        result += (ll)(n / 2 - p);
    }

    int *tmp = merge(arr, n / 2, arr + n / 2, n - n / 2);
    memcpy(arr, tmp, sizeof(int) * n);
    free(tmp);
    return result;
}

signed main() {
    int n, m;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = next_rand() % m;
    printf("%lld", solve(arr, n));
}