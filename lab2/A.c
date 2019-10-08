#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

void sort(int *a, int l, int r) {
    if (l >= r) return;
    int rnd = (rand()) % (r - l + 1);
    int x = a[l + rnd];
    int i = l, j = r;
    while (i < j) {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i < j) {
            a[i] ^= a[j];
            a[j] ^= a[i];
            a[i] ^= a[j];
            i++;
            j--;
        }
    }
    sort(a, l, j);
    sort(a, i, r);
}

signed main() {
    int n; scanf("%d", &n);
    int *a = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}