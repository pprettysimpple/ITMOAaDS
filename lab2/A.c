//
// Created by kirill on 13.10.2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void sort(int i, int i1, int *pInt);

signed main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(0, n - 1, a);
    for (int i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }
}

void sort(int l, int r, int *a) {
    if (l >= r) {
        return;
    }
    int m = (l + r) / 2;
    sort(l, m, a);
    sort(m + 1, r, a);
    int *cur = malloc((r - l + 1) * sizeof(int));
    int p1 = l, p2 = m + 1;
    while (p1 <= m && p2 <= r) {
        if (a[p1] <= a[p2]) {
            *cur = a[p1++];
        } else {
            *cur = a[p2++];
        }
        cur++;
    }
    while (p1 <= m) {
        *cur = a[p1++];
        cur++;
    }
    while (p2 <= r) {
        *cur = a[p2++];
        cur++;
    }
    cur -= (r - l + 1);
    memcpy(a + l, cur, sizeof(int) * (r - l + 1));
    free(cur);
}
