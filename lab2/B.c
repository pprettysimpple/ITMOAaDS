//
// Created by kirill on 13.10.2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int search_left(int *a, int size, int x) {
    int l = 0, r = size - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] >= x) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int search_right(int *a, int size, int x) {
    int l = 0, r = size - 1;
    while (l < r) {
        int m = r - (r - l) / 2;
        if (a[m] <= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return l;
}

signed main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int x;
        scanf("%d", &x);
        int l = search_left(a, n, x);
        int r = search_right(a, n, x);
        if (a[l] != x) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", l + 1, r + 1);
        }
    }
}

