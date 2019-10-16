//
// Created by kirill on 13.10.2019.
//

#include <stdlib.h>
#include <stdio.h>

void sort(int *a, int l, int r) {
    if (l >= r) return;
    int i = l, j = r;
    while (i < j) {

    }
}

signed main() {
    int n; scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    sort(a, 0, n - 1);
}