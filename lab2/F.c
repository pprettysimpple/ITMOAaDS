//
// Created by kirill on 20.10.2019.
//

#include "stdio.h"
#include "stdlib.h"

void do_bad_thing(int *a, int n) {
    for (int i = 1; i < n; i++) {
        a[i] ^= a[i / 2];
        a[i / 2] ^= a[i];
        a[i] ^= a[i / 2];
    }
    int p1 = 0, p2 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) p1 = i;
        if (a[i] == 2) p2 = i;
    }
    a[p1] ^= a[p2];
    a[p2] ^= a[p1];
    a[p1] ^= a[p2];
}

signed main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * (sizeof(int)));
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    do_bad_thing(a, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
}