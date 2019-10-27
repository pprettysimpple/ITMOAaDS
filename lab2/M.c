//
// Created by kirill on 23.10.2019.
//

#include <stdio.h>
#include <stdlib.h>

int n, k, m;
int **cmp_first;
int **cmp_second;
int *cnt;

int get(int x, int pos) {
    return ((x >> pos) & 1);
}

int swap_bit(int x, int pos1, int pos2) {
    if (get(x, pos1) != get(x, pos2)) {
        return (x ^ (1 << pos1) ^ (1 << pos2));
    }
    return x;
}

int check(int x) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            if (get(x, cmp_first[i][j]) > get(x, cmp_second[i][j])) {
                x = swap_bit(x, cmp_first[i][j], cmp_second[i][j]);
            }
        }
    }
    for (int i = 0; i + 1 < n; i++) {
        if (get(x, i) > get(x, i + 1)) return 0;
    }
    return 1;
}

signed main() {
    scanf("%d%d%d", &n, &m, &k);

    cmp_first = malloc(k * sizeof(int*));
    cmp_second = malloc(k * sizeof(int*));
    cnt = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        scanf("%d", cnt + i);
        cmp_first[i] = malloc(cnt[i] * sizeof(int));
        cmp_second[i] = malloc(cnt[i] * sizeof(int));
        for (int j = 0; j < cnt[i]; j++) {
            int l, r; scanf("%d%d", &l, &r);
            if (l > r) {
                l ^= r;
                r ^= l;
                l ^= r;
            }
            cmp_first[i][j] = --l;
            cmp_second[i][j] = --r;
        }
    }

    for (int x = 0; x < (1 << n); x++) {
        if (!check(x)) {
            printf("No");
            return 0;
        }
    }
    printf("Yes");
}